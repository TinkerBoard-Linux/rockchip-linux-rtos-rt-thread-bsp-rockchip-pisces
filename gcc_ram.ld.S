/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  */

#include "rtconfig.h"

#ifdef OLPC_OVERLAY_ENABLE
#include "gcc_ram_overlay.ld.S"
#else
#include "gcc_ram_raw.ld.S"
#endif
