/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/chubbs/qt/offroad/settings/vehicle_panel.h"

#include "selfdrive/ui/chubbs/qt/widgets/scrollview.h"

VehiclePanel::VehiclePanel(QWidget *parent) : QFrame(parent) {
  this->offroad = !uiState()->scene.started;
  main_layout = new QStackedLayout(this);
  ListWidget *list = new ListWidget(this);

  vehicleScreen = new QWidget(this);
  QVBoxLayout *vlayout = new QVBoxLayout(vehicleScreen);
  vlayout->setContentsMargins(50, 20, 50, 20);

  platformSelector = new PlatformSelector();
  list->addItem(platformSelector);

  QObject::connect(uiState(), &UIState::offroadTransition, this, &VehiclePanel::updateToggles);

  ScrollViewSP *scroller = new ScrollViewSP(list, this);
  vlayout->addWidget(scroller);

  QObject::connect(platformSelector, &PlatformSelector::clicked, [=]() {
    updatePlatformCache();
    QTimer::singleShot(100, this, &VehiclePanel::updateCarToggles);
  });

  hkgtuningToggle = new ParamControlSP("HKGtuning",
                               tr("Chubbs Tune"),
                               tr("Enable to experience enhanced vehicle performance tuning"),
                               "../assets/offroad/icon_shell.png",
                               this);
  list->addItem(hkgtuningToggle);
  connect(hkgtuningToggle, &ToggleControlSP::toggleFlipped, this, [=](bool checked) {
    handleToggleAction(hkgtuningToggle, checked);
  });

  main_layout->addWidget(vehicleScreen);
  main_layout->setCurrentWidget(vehicleScreen);
}

void VehiclePanel::updatePlatformCache() {
  cachedPlatformData["brand"] = platformSelector->getPlatformBundle("brand").toString();
  cachedPlatformData["make"] = platformSelector->getPlatformBundle("make").toString();
  cachedPlatformData["model"] = platformSelector->getPlatformBundle("model").toString();
}

void VehiclePanel::updateToggles(bool offroad_transition) {
  this->offroad = offroad_transition;
  platformSelector->refresh(offroad_transition);
  updatePlatformCache();
  updateCarToggles();
}

VehiclePanel::ToggleState VehiclePanel::getToggleState(bool hasOpenpilotLong) const {
  if (!hasOpenpilotLong) {
    return ToggleState::DISABLED_LONGITUDINAL;
  }
  if (uiState()->scene.started) {
    return ToggleState::DISABLED_DRIVING;
  }
  return ToggleState::ENABLED;
}

void VehiclePanel::updateToggleState(ParamControlSP* toggle, bool hasOpenpilotLong) {
  static const QString LONGITUDINAL_MSG = tr("Enable openpilot longitudinal control first.");
  static const QString DRIVING_MSG = tr("Cannot modify while driving. Please go offroad mode first.");

  ToggleState state = getToggleState(hasOpenpilotLong);

  switch (state) {
    case ToggleState::ENABLED:
      toggle->setDescription("");
      break;
    case ToggleState::DISABLED_LONGITUDINAL: {
      QString msg = "<font color='orange'>" + tr("Enable openpilot longitudinal control first to modify this setting.") + "</font>";
      toggle->setDescription(msg);
      toggle->showDescription();
      QTimer::singleShot(5000, toggle, &ParamControl::hideDescription);
      break;
    }
    case ToggleState::DISABLED_DRIVING: {
      QString msg = "<font color='orange'>" + tr("Cannot modify while driving. Please go offroad mode first.") + "</font>";
      toggle->setDescription(msg);
      toggle->showDescription();
      QTimer::singleShot(5000, toggle, &ParamControl::hideDescription);
      break;
    }
  }
}

void VehiclePanel::handleToggleAction(ParamControlSP* toggle, bool checked) {
  bool hasOpenpilotLong = params.getBool("ExperimentalLongitudinalEnabled");
  bool isOffroad = !uiState()->scene.started;
  if (!isOffroad || !hasOpenpilotLong) {
    // Revert the toggle state
    toggle->setEnabled(false);
    toggle->setValue(QString::number(params.getBool(toggle->key)));
    
    if (!isOffroad) {
      QString msg = "<font color='orange'>" + tr("Cannot modify while driving. Please go offroad first.") + "</font>";
      toggle->setDescription(msg);
    } else if (!hasOpenpilotLong) {
      QString msg = "<font color='orange'>" + tr("Enable openpilot longitudinal control first.") + "</font>";
      toggle->setDescription(msg);
    }
    
    toggle->showDescription();
    QTimer::singleShot(5000, toggle, &ParamControlSP::hideDescription);
    return;
  }
  
  // Enable toggle and apply changes when in offroad mode with longitudinal enabled
  toggle->setEnabled(true);
  params.putBool(toggle->key, checked);
  updateToggleState(toggle, hasOpenpilotLong);
}

void VehiclePanel::updateCarToggles() {
  bool hasOpenpilotLong = params.getBool("ExperimentalLongitudinalEnabled");

  // Default state - no car selected
  hkgtuningToggle->setVisible(false);
  
  if (!cachedPlatformData["brand"].toString().isEmpty() && cachedPlatformData["brand"].toString() == "hyundai") {
    hkgtuningToggle->setVisible(true);
    hkgtuningToggle->setEnabled(offroad && hasOpenpilotLong);
    updateToggleState(hkgtuningToggle, hasOpenpilotLong);
  } else if (params.getBool(hkgtuningToggle->key)) {
    params.putBool(hkgtuningToggle->key, false);
  }
}

