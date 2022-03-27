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
#include "gui_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_freertos_hooks.h"
#include "disp_spi.h"
#include "disp_driver.h"
#include "touch_driver.h"
#include "gui.h"
#include "lv_conf.h"



//
// GUI Task variables
//

static const char* TAG = "gui_task";

// Dual display update buffers to allow DMA/SPI transfer of one while the other is updated
static lv_color_t lvgl_disp_buf1[LVGL_DISP_BUF_SIZE];
static lv_color_t lvgl_disp_buf2[LVGL_DISP_BUF_SIZE];
static lv_disp_buf_t lvgl_disp_buf;

// Display driver
static lv_disp_drv_t lvgl_disp_drv;

// Touchscreen driver
static lv_indev_drv_t lvgl_indev_drv;



//
// GUI Task Forward declarations for internal functions
//
static bool gui_lvgl_init();
static void IRAM_ATTR lv_tick_callback();



//
// GUI Task API
//

/**
 * GUI Task - Executes all GUI/display related activities via LittleVGL objects
 * and LittleVGL sub-tasks evaluated by lv_task_handler. 
 */
void gui_task()
{
	ESP_LOGI(TAG, "Start task");

	// Initialize
	if (!gui_lvgl_init()) {
		vTaskDelete(NULL);
	}
	gui_init();
	
	while (1) {
		// This task runs every LVGL_EVAL_MSEC mSec
		vTaskDelay(pdMS_TO_TICKS(GUI_TASK_EVAL_MSEC));
		lv_task_handler();
	}
}


//
// GUI Task Internal functions
//

/**
 * Initialize the LittleVGL system including initializing the LCD display and
 * Touchscreen controller.
 */
static bool gui_lvgl_init()
{
	// Initialize lvgl
	lv_init();
	
	//
	// Interface and driver initialization
	//
	disp_driver_init(true);
	touch_driver_init();
	
	// Install the display driver
	lv_disp_buf_init(&lvgl_disp_buf, lvgl_disp_buf1, lvgl_disp_buf2, LVGL_DISP_BUF_SIZE);
	lv_disp_drv_init(&lvgl_disp_drv);
	lvgl_disp_drv.flush_cb = disp_driver_flush;
	lvgl_disp_drv.buffer = &lvgl_disp_buf;
	lv_disp_drv_register(&lvgl_disp_drv);
	
	// Install the touchscreen driver
    lv_indev_drv_init(&lvgl_indev_drv);
    lvgl_indev_drv.read_cb = touch_driver_read;
    lvgl_indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&lvgl_indev_drv);
    
    // Hook LittleVGL's timebase to its CPU system tick so it can keep track of time
    esp_register_freertos_tick_hook(lv_tick_callback);
    
    return true;
}




/**
 * LittleVGL timekeeping callback - hooked to the system tick timer so LVGL
 * knows how much time has gone by (used for animations, etc).
 */
static void IRAM_ATTR lv_tick_callback()
{
	lv_tick_inc(portTICK_RATE_MS);
}
