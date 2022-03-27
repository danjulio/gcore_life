# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/lvgl/lvgl $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_core $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_draw $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_objx $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_hal $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_misc $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_themes $(PROJECT_PATH)/components/lvgl/lvgl/src/lv_font $(PROJECT_PATH)/components/lvgl
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/lvgl -llvgl
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += lvgl
COMPONENT_LDFRAGMENTS += 
component-lvgl-build: 
