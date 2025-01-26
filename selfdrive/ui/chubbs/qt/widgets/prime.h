/**
 * Copyright (c) 2021-, Haibin Wen, chubbs, and a number of other contributors.
 *
 * This file is part of chubbs and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include "selfdrive/ui/qt/widgets/prime.h"

#include "selfdrive/ui/chubbs/ui.h"

class SetupWidgetSP : public SetupWidget {
  Q_OBJECT

public:
  explicit SetupWidgetSP(QWidget *parent = nullptr);
};
