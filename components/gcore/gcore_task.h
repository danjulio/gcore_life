/**
 *
 * gcore_task.h - Header file for gCore task
 *
 * This file is part of life.
 *
 * life is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * life is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with life.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef GCORE_TASK_H_
#define GCORE_TASK_H_

#include <stdint.h>


// ================================================================================
// Constants
// ================================================================================

//
// Task evaluation period (mSec)
//
#define GCORE_EVAL_MSEC 50


//
// Button press detection threshold
//
#define GCORE_BTN_THRESH_MSEC 500


//
// LCD Backlight Brightness % (0-100)
///
#define GCORE_BL_INIT   100



// ================================================================================
// API
// ================================================================================
void gcore_task();

#endif /* GCORE_TASK_H_ */
