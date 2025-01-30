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
  explicit VehiclePanel(QWidget *parent = nullptr);

  // Toggle states
  enum class ToggleState {
    ENABLED,
    DISABLED_LONGITUDINAL,
    DISABLED_DRIVING
  };

private:
  // UI elements
  QStackedLayout* main_layout = nullptr;
  QWidget* vehicleScreen = nullptr;
  PlatformSelector* platformSelector = nullptr;
  ParamControlSP* hkgtuningToggle = nullptr;

  // State tracking
  Params params;
  bool offroad;
  QVariantMap cachedPlatformData;

  // Helper methods
  ToggleState getToggleState(bool hasOpenpilotLong) const;
  void updateToggleState(ParamControlSP* toggle, bool hasOpenpilotLong);
  void updatePlatformCache();

private slots:
  void updateCarToggles();
  void updateToggles(bool offroad_transition);
  void handleToggleAction(ParamControlSP* toggle, bool checked);
};
