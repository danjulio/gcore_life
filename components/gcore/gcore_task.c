/**
 *
 * gcore_task.c - gCore power monitor task
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
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "gcore_task.h"
#include "gcore.h"
#include "power_utilities.h"



// ================================================================================
// Variables
// ================================================================================

static const char* TAG = "gcore_task";



// ================================================================================
// API Routines
// ================================================================================

void gcore_task()
{
	batt_status_t batt_status;
	
	ESP_LOGI(TAG, "Start task");
	
	if (!power_init()) {
		ESP_LOGE(TAG, "Halting gcore_task");
		vTaskDelete(NULL);
	}
	
	// Set the initial screen brightness
	power_set_brightness(GCORE_BL_INIT);
	
	// Set the button detection threshold
	(void) gcore_set_reg8(GCORE_REG_PWR_TM, GCORE_BTN_THRESH_MSEC / 10);
  
	while (1) {
		vTaskDelay(pdMS_TO_TICKS(GCORE_EVAL_MSEC));
		
		// Update battery values
		power_batt_update();
			
		// Look for power-off button press
		if (power_button_pressed()) {
			ESP_LOGI(TAG, "Power button press detected");
			vTaskDelay(pdMS_TO_TICKS(10));
			power_off();
		}
		
		// Look for critical battery shutdown
		power_get_batt(&batt_status);
			
		if (batt_status.batt_state == BATT_CRIT) {
			ESP_LOGI(TAG, "Critical battery voltage detected");
			vTaskDelay(pdMS_TO_TICKS(10));
			power_off();
		}
	}
}
