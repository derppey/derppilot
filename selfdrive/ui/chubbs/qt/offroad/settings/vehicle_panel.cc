/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/chubbs/qt/offroad/settings/vehicle_panel.h"

#include "selfdrive/ui/chubbs/qt/widgets/scrollview.h"

VehiclePanel::VehiclePanel(QWidget *parent) : QFrame(parent) {
  main_layout = new QStackedLayout(this);
  ListWidget *list = new ListWidget(this);

  vehicleScreen = new QWidget(this);
  QVBoxLayout *vlayout = new QVBoxLayout(vehicleScreen);
  vlayout->setContentsMargins(50, 20, 50, 20);

  platformSelector = new PlatformSelector();
  list->addItem(platformSelector);

  hkgtuningToggle = new ParamControl("HKGtuning",
                               tr("Chubbs Tune"),
                               tr("Enable to experience enhanced vehicle performance tuning"),
                               "../assets/offroad/icon_shell.png",
                               this);
  list->addItem(hkgtuningToggle);
  hkgtuningToggle->setVisible(false);

  QObject::connect(hkgtuningToggle, &ParamControl::toggleFlipped, [=](bool enabled) {
    params.putBool("HKGtuning", enabled);
    if (isOnroad && enabled != params.getBool("HKGtuning")) {
      showRebootPrompt();
    }
  });

  QObject::connect(uiState(), &UIState::offroadTransition, [=](bool offroad) {
    isOnroad = !offroad;
    updateCarToggles();
  });

  ScrollViewSP *scroller = new ScrollViewSP(list, this);
  vlayout->addWidget(scroller);

  QObject::connect(uiState(), &UIState::offroadTransition, platformSelector, &PlatformSelector::refresh);

  QObject::connect(platformSelector, &PlatformSelector::clicked, [=]() {
    QTimer::singleShot(100, this, &VehiclePanel::updateCarToggles);
  });

  QTimer *timer = new QTimer(this);
  QObject::connect(timer, &QTimer::timeout, this, &VehiclePanel::updateCarToggles);
  timer->start(1000);

  main_layout->addWidget(vehicleScreen);
  main_layout->setCurrentWidget(vehicleScreen);
}

void VehiclePanel::showRebootPrompt() {
  QString question = tr("Changing this setting requires a reboot to take effect.\n\n"
                       "Reboot now or later?");

  reboot_confirmed = ConfirmationDialog::confirm(question, tr("Reboot Now"), this);
  if (reboot_confirmed && !reboot_completed) {
    params.putBool("DoReboot", true);
    reboot_completed = true;
  }
}

VehiclePanel::ToggleState VehiclePanel::getToggleState(bool hasOpenpilotLong) const {
  if (!hasOpenpilotLong) {
    return ToggleState::DISABLED_LONGITUDINAL;
  }
  if (isOnroad) {
    return ToggleState::DISABLED_DRIVING;
  }
  return ToggleState::ENABLED;
}

void VehiclePanel::updateToggleState(ParamControl* toggle, bool hasOpenpilotLong) {
  static const QString LONGITUDINAL_MSG = tr("Enable openpilot longitudinal control first.");
  static const QString DRIVING_MSG = tr("Cannot modify while driving. Please go offroad first.");
  
  ToggleState state = getToggleState(hasOpenpilotLong);
  
  switch (state) {
    case ToggleState::ENABLED:
      toggle->setEnabled(true);
      toggle->setToolTip("");
      break;
    case ToggleState::DISABLED_LONGITUDINAL:
      toggle->setEnabled(false);
      toggle->setToolTip(LONGITUDINAL_MSG);
      break;
    case ToggleState::DISABLED_DRIVING:
      toggle->setEnabled(false);
      toggle->setToolTip(DRIVING_MSG);
      break;
  }
}

void VehiclePanel::updateCarToggles() {
  QString platform_name = QString::fromStdString(params.get("CarPlatformName"));
  bool hasOpenpilotLong = params.getBool("ExperimentalLongitudinalEnabled");

  if (platform_name.isEmpty()) {
    hkgtuningToggle->setVisible(false);
    return;
  }

  QVariantMap platform_data = platformSelector->loadPlatformList()[platform_name];
  if (platform_data.isEmpty()) {
    hkgtuningToggle->setVisible(false);
    return;
  }

  QString make = platform_data["make"].toString().toLower();
  
  bool isHKG = (make == "hyundai" || make == "kia" || make == "genesis");
  hkgtuningToggle->setVisible(isHKG);
  
  if (isHKG) {
    updateToggleState(hkgtuningToggle, hasOpenpilotLong);
  }

  // Future make-specific toggles can be added here
}
