#include "lvgl/lvgl.h"
#include "hal/hal.h"
#include "screen_analysis.h"
#include "screen_blank.h"
#include "screen_dashboard.h"
#include "screen_bio.h"
#include "screen_sample.h"
#include <stdio.h>


#ifdef _WIN32 
    #include <Windows.h>
#else
    #include <unistd.h>
#endif



int main(void)
{
    lv_init();

    uint32_t hor_res = 1000;
    uint32_t ver_res = 720;
    sdl_hal_init(hor_res, ver_res);

    
    screen_analysis_create();
    // screen_blank_create();
    // screen_dashboard_create();
    // screen_bio_create();
    // screen_sample_create();

    lv_screen_load(scr);


    while (1) {
        lv_timer_handler();

    #ifdef _WIN32
        Sleep(5);
    #else
        usleep(5000);
    #endif
    }

    return 0;
}


