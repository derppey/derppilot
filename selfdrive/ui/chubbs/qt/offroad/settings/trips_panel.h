/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include "selfdrive/ui/chubbs/qt/widgets/controls.h"

#include "selfdrive/ui/chubbs/qt/widgets/drive_stats.h"

class TripsPanel : public QFrame {
  Q_OBJECT

public:
  explicit TripsPanel(QWidget* parent = 0);

private:
  Params params;

  QStackedLayout* center_layout;
  DriveStats *driveStatsWidget;
};
