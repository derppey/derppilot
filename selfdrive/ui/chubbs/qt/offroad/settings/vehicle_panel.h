/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include "selfdrive/ui/chubbs/qt/offroad/settings/settings.h"

#include "selfdrive/ui/chubbs/qt/offroad/settings/vehicle/platform_selector.h"

class VehiclePanel : public QFrame {
  Q_OBJECT

public:
  enum class ToggleState {
    ENABLED,
    DISABLED_LONGITUDINAL,
    DISABLED_DRIVING
  };

  explicit VehiclePanel(QWidget *parent = nullptr);

private:
  QStackedLayout* main_layout = nullptr;
  QWidget* vehicleScreen = nullptr;
  PlatformSelector *platformSelector = nullptr;
  ParamControl *hkgtuningToggle = nullptr;
  Params params;
  bool isOnroad = false;
  bool reboot_confirmed = false;
  bool reboot_completed = false;

  void updateToggleState(ParamControl* toggle, bool hasOpenpilotLong);
  ToggleState getToggleState(bool hasOpenpilotLong) const;
  void showRebootPrompt();

private slots:
  void updateCarToggles();
};
