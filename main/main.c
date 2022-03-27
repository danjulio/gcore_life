/* gCore runs "Life"
 * 
 * A tribute to John Conway (1938-2020) who gave us "Life" and who passed away
 * while I was writing the documentation for gCore.
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
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

// Application specific
#include "gcore_task.h"
#include "gui_task.h"
#include "i2c.h"



//
// Variables
//
TaskHandle_t task_handle_gcore;
TaskHandle_t task_handle_gui;


//
// Application entry point
//
void app_main() {

	// Initialize the shared I2C interface
	if (i2c_master_init() == ESP_OK) {
		// Start the tasks
		xTaskCreatePinnedToCore(&gcore_task, "gcore_task", 2048, NULL, 1, &task_handle_gcore, 0);
		xTaskCreatePinnedToCore(&gui_task,   "gui_task",   3072, NULL, 2, &task_handle_gui,   1);
	}
}
