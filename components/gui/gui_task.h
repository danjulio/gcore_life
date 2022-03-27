/*
 * GUI Task - Initializes LVGL and evaluates it
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
#ifndef GUI_TASK_H
#define GUI_TASK_H

#include <stdbool.h>
#include <stdint.h>


//
// GUI Task Constants
//
#define GUI_TASK_EVAL_MSEC 20



//
// GUI Task API
//
void gui_task();

 

#endif /* GUI_TASK_H */
