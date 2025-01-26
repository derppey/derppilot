/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/chubbs/qt/offroad/offroad_home.h"

#include <QStackedWidget>

#include "selfdrive/ui/chubbs/qt/widgets/drive_stats.h"

OffroadHomeSP::OffroadHomeSP(QWidget *parent) : OffroadHome(parent) {
  QStackedWidget *left_widget = new QStackedWidget(this);
  left_widget->addWidget(new DriveStats(this));
  left_widget->setStyleSheet("border-radius: 10px;");

  home_layout->insertWidget(0, left_widget);
}
