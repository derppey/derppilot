#pragma once

#ifdef CHUBBS
#include "selfdrive/ui/chubbs/qt/offroad/settings/settings.h"
#else
#include "selfdrive/ui/qt/offroad/settings.h"
#endif

class DeveloperPanel : public ListWidget {
  Q_OBJECT
public:
  explicit DeveloperPanel(SettingsWindow *parent);
  void showEvent(QShowEvent *event) override;

private:
  Params params;
  ParamControl* adbToggle;
  ParamControl* joystickToggle;
  ParamControl* longManeuverToggle;
  ParamControl* experimentalLongitudinalToggle;
  ParamControl* hyundaiRadarTracksToggle;
  bool is_release;
  bool offroad;

private slots:
  void updateToggles(bool _offroad);
};
