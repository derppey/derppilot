/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/chubbs/qt/home.h"

#include "selfdrive/ui/chubbs/qt/widgets/drive_stats.h"

HomeWindowSP::HomeWindowSP(QWidget *parent) : HomeWindow(parent) {
}

void HomeWindowSP::updateState(const UIState &s) {
  HomeWindow::updateState(s);
}

void HomeWindowSP::mousePressEvent(QMouseEvent *e) {
  HomeWindow::mousePressEvent(e);
}
