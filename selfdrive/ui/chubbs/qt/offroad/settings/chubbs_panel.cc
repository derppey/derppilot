/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/chubbs/qt/offroad/settings/chubbs_panel.h"

#include "common/util.h"
#include "selfdrive/ui/chubbs/qt/widgets/controls.h"

ChubbsPanel::ChubbsPanel(SettingsWindowSP *parent) : QFrame(parent) {
  main_layout = new QStackedLayout(this);
  ListWidget *list = new ListWidget(this, false);

  chubbsScreen = new QWidget(this);
  QVBoxLayout* vlayout = new QVBoxLayout(chubbsScreen);
  vlayout->setContentsMargins(50, 20, 50, 20);

  // MADS
  madsToggle = new ParamControl(
    "Mads",
    tr("Modular Assistive Driving System (MADS)"),
    tr("Enable the beloved MADS feature. Disable toggle to revert back to stock openpilot engagement/disengagement."),
    "");
  madsToggle->setConfirmation(true, false);
  list->addItem(madsToggle);

  madsSettingsButton = new PushButtonSP(tr("Customize MADS"));
  madsSettingsButton->setObjectName("mads_btn");
  connect(madsSettingsButton, &QPushButton::clicked, [=]() {
    chubbsScroller->setLastScrollPosition();
    main_layout->setCurrentWidget(madsWidget);
  });
  QObject::connect(madsToggle, &ToggleControl::toggleFlipped, madsSettingsButton, &PushButtonSP::setEnabled);

  madsWidget = new MadsSettings(this);
  connect(madsWidget, &MadsSettings::backPress, [=]() {
    chubbsScroller->restoreScrollPosition();
    main_layout->setCurrentWidget(chubbsScreen);
  });
  list->addItem(madsSettingsButton);

  toggleOffroadOnly = {
    madsToggle,
  };
  QObject::connect(uiState(), &UIState::offroadTransition, this, &ChubbsPanel::updateToggles);

  chubbsScroller = new ScrollViewSP(list, this);
  vlayout->addWidget(chubbsScroller);

  main_layout->addWidget(chubbsScreen);
  main_layout->addWidget(madsWidget);

  setStyleSheet(R"(
    #back_btn {
      font-size: 50px;
      margin: 0px;
      padding: 15px;
      border-width: 0;
      border-radius: 30px;
      color: #dddddd;
      background-color: #393939;
    }
    #back_btn:pressed {
      background-color:  #4a4a4a;
    }
  )");

  main_layout->setCurrentWidget(chubbsScreen);
}

void ChubbsPanel::showEvent(QShowEvent *event) {
  updateToggles(offroad);
}

void ChubbsPanel::hideEvent(QHideEvent *event) {
  main_layout->setCurrentWidget(chubbsScreen);
}

void ChubbsPanel::updateToggles(bool _offroad) {
  for (auto *toggle : toggleOffroadOnly) {
    toggle->setEnabled(_offroad);
  }

  madsSettingsButton->setEnabled(madsToggle->isToggled());

  offroad = _offroad;
}
