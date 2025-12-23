#include "hal.h"

lv_display_t * sdl_hal_init(int32_t w, int32_t h)
{
    lv_display_t * disp = lv_sdl_window_create(w, h);
    lv_display_set_default(disp);

    /* Create input group AFTER display */
    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);

    /* Mouse */
    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_set_display(mouse, disp);
    lv_indev_set_group(mouse, g);

    /* Cursor */
    LV_IMAGE_DECLARE(mouse_cursor_icon);
    lv_obj_t * cursor_obj = lv_image_create(lv_scr_act());
    lv_image_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse, cursor_obj);

    /* Mouse wheel */
    lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mousewheel, disp);
    lv_indev_set_group(mousewheel, g);

    /* Keyboard */
    lv_indev_t * kb = lv_sdl_keyboard_create();
    lv_indev_set_display(kb, disp);
    lv_indev_set_group(kb, g);

    return disp;
}
