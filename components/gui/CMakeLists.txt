file(GLOB SOURCES *.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS . ../lvgl ../gcore ../lvgl_esp32_drivers/lvgl_tft ../lvgl_esp32_drivers/lvgl_touch)
