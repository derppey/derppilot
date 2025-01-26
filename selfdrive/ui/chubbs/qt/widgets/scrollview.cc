/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/chubbs/qt/widgets/scrollview.h"

#include <QScrollBar>

void ScrollViewSP::setLastScrollPosition() {
  lastScrollPosition = verticalScrollBar()->value();
}

void ScrollViewSP::restoreScrollPosition() {
  verticalScrollBar()->setValue(lastScrollPosition);
}
