#include "screen_dashboard.h"
#include <stdio.h>
#include <math.h>
#include "lvgl.h"
#include "assets/fonts/fa_24.h"



/*----------- ICONS------------*/
#define FA_ANALYSIS   "\uf201"
#define FA_WORKLIST   "\uf0ae"
#define FA_REPORTS    "\uf15c"
#define FA_CALIB      "\uf1de" // SLIDERS
#define FA_SETTINGS   "\uf013"
#define FA_EXIT       "\uf08b"
#define FA_MAINT      "\uf0ad" // WRENCH
#define FA_FLASK      "\uf0c3"
#define FA_METHODS    "\ue596"
#define FA_QC         "\uf610" // VIALS 

#define FA_BELL      "\uf0f3"
#define FA_CLOCK     "\uf017"
#define FA_VIAL     "\uf492"
#define FA_CHECK     "\uf058"
#define FA_WARNING   "\uf071"
#define FA_WATER     "\uf043"
#define FA_HEART     "\uf21e"
#define FA_NOTES     "\uf48e"
#define FA_VIRUS     "\uf6ff"
#define FA_DOT       "\uf192"


/* ---------- COLORS ---------- */
#define COLOR_BG         lv_color_hex(0x0E1A2B)
#define COLOR_SIDEBAR    lv_color_hex(0x1E293B)
#define COLOR_CARD       lv_color_hex(0x162433)
#define COLOR_ACCENT     lv_color_hex(0x1670fb)
#define COLOR_NUM        lv_color_hex(0x00ccff)
#define COLOR_TEXT       lv_color_hex(0xE6EEF5)
#define COLOR_GREEN      lv_color_hex(0x3cb371)
#define COLOR_SHADOW     lv_color_hex(0x1A4E5F)
#define COLOR_ORANGE     lv_color_hex(0xf19600)
#define COLOR_RED        lv_color_hex(0xF03A47)
#define COLOR_GRAY       lv_color_hex(0x8A97A7)
#define COLOR_BUTTON_RED lv_color_hex(0xF30000)
#define COLOR_BUTTON_BLUE lv_color_hex(0x3a74db)
#define COLOR_BUTTON_GRAY lv_color_hex(0x2F3E4A)


/* ---------- create card ---------- */
static lv_obj_t * create_card(lv_obj_t *parent, lv_coord_t w, lv_coord_t h)
{
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, w, h);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x1E293B), 0);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);

    lv_obj_set_style_radius(card, 10, 0);
    lv_obj_set_style_pad_all(card, 20, 0);

    lv_obj_set_style_border_color(card, lv_color_hex(0x8A97A7), 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_opa(card, LV_OPA_40, 0);

    lv_obj_set_style_shadow_width(card, 25, 0);
    lv_obj_set_style_shadow_color(card, lv_color_hex(0x8A97A7), 0);
    lv_obj_set_style_shadow_opa(card, LV_OPA_60, 0);
    lv_obj_set_style_shadow_spread(card, -8, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);

    return card;
}


/* ---------- small badge ---------- */
static lv_obj_t * create_badge(lv_obj_t *parent, const char *text, lv_color_t bg)
{
    lv_obj_t *badge = lv_label_create(parent);
    lv_label_set_text(badge, text);
    lv_obj_set_style_text_color(badge, lv_color_white(), 0);
    lv_obj_set_style_bg_color(badge, bg, 0);
    lv_obj_set_style_radius(badge, 10, 0);
    lv_obj_set_style_pad_hor(badge, 8, 0);
    lv_obj_set_style_pad_ver(badge, 3, 0);
    
    return badge;
}

/* ----------- Top Bar ------------*/
static lv_obj_t * create_top_bar(lv_obj_t *parent)
{
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, LV_PCT(97), 56);
    lv_obj_align(bar, LV_ALIGN_TOP_MID, 8, 0);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0x1E293B), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(bar, 0, 0);
    lv_obj_set_style_pad_left(bar, 18, 0);
    lv_obj_set_style_pad_right(bar, 18, 0);
    lv_obj_set_style_pad_top(bar, 10, 0);
    lv_obj_set_style_pad_bottom(bar, 10, 0);
    lv_obj_set_style_border_width(bar, 0, 0);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);

    /* left container: title + badge */
    lv_obj_t *left = lv_obj_create(bar);
    lv_obj_remove_style_all(left);
    lv_obj_set_flex_flow(left, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(left, 10, 0);
    lv_obj_set_size(left, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(left, LV_ALIGN_LEFT_MID, 12, 0);

    lv_obj_t *title = lv_label_create(left);
    lv_label_set_text(title, "Analysis Dashboard");
    lv_obj_set_style_text_color(title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);

    lv_obj_t *active_badge = create_badge(left, "Active", COLOR_SHADOW);
    lv_obj_set_style_text_color(active_badge, lv_color_hex(0x43A5BD) ,0);
    lv_obj_set_style_bg_color(active_badge, COLOR_SHADOW, 0);
    lv_obj_set_style_bg_opa(active_badge, LV_OPA_40, 0);
    
    

    /* right container: time + date */
    lv_obj_t *right = lv_obj_create(bar);
    lv_obj_remove_style_all(right);
    lv_obj_set_flex_flow(right, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(right, 12, 0);
    lv_obj_set_size(right, 250, 60);
    lv_obj_align(right, LV_ALIGN_RIGHT_MID, 12, 20);
    
    lv_obj_t *time_icon = lv_label_create(bar);
    lv_label_set_text(time_icon, FA_CLOCK );
    lv_obj_set_style_text_font(time_icon, &fa_24, 0);
    lv_obj_set_style_text_color(time_icon, COLOR_GRAY, 0);
    lv_obj_align(time_icon, LV_ALIGN_TOP_MID, 115, 5);
   

    lv_obj_t *time_lbl = lv_label_create(right);
    lv_label_set_text(time_lbl, " 06:52:27");
    lv_obj_set_style_text_color(time_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(time_lbl, &lv_font_montserrat_12, 0);

    lv_obj_t *cal_icon = lv_label_create(right);
    lv_label_set_text(cal_icon, LV_SYMBOL_FILE);
    lv_obj_set_style_text_color(cal_icon, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(cal_icon, &lv_font_montserrat_12, 0);

    lv_obj_t *date_lbl = lv_label_create(right);
    lv_label_set_text(date_lbl, "Dec 03, 2025");
    lv_obj_set_style_text_color(date_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(date_lbl, &lv_font_montserrat_12, 0);

    lv_obj_t *icon10_bg =lv_obj_create(bar);
    lv_obj_set_size(icon10_bg, 40, 40);
    lv_obj_set_style_bg_color(icon10_bg, lv_color_hex(0x314055), 0);
    lv_obj_set_style_bg_opa(icon10_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(icon10_bg, 8, 0);
    lv_obj_set_style_border_width(icon10_bg,0,0);
    lv_obj_clear_flag(icon10_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(icon10_bg, LV_ALIGN_RIGHT_MID, 0,0);

    lv_obj_t *icon10 =lv_label_create(icon10_bg);
    lv_label_set_text(icon10, "\uf0f3");
    lv_obj_set_style_text_font(icon10, &fa_24, 0);
    lv_obj_set_style_text_color(icon10, lv_color_hex(0xCDD9E5) , 0);
    lv_obj_center(icon10);

    return bar;
}

static lv_obj_t * create_bottom_bar(lv_obj_t *parent)
{
    lv_obj_t *bm_bar = lv_obj_create(parent);
    lv_obj_set_size(bm_bar, LV_PCT(78), 60);
    lv_obj_align(bm_bar, LV_ALIGN_BOTTOM_MID, 110, 0);

    lv_obj_set_style_bg_color(bm_bar, lv_color_hex(0x1E293B), 0);
    lv_obj_set_style_bg_opa(bm_bar, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(bm_bar, 0, 0);
    lv_obj_set_style_border_width(bm_bar, 0, 0);

    lv_obj_set_style_pad_left(bm_bar, 20, 0);
    lv_obj_set_style_pad_right(bm_bar, 20, 0);
    lv_obj_set_style_pad_top(bm_bar, 10, 0);
    lv_obj_set_style_pad_bottom(bm_bar, 10, 0);

    return bm_bar;
}

lv_obj_t *scr_2 = NULL;

/* ---------- CREATE SCREEN ---------- */
void screen_dashboard_create(void)
{
    /* Root screen */
    scr_2 = lv_obj_create(NULL);
    // lv_scr_load(scr);
    lv_obj_set_style_bg_color(scr_2, COLOR_BG, 0);
    lv_obj_set_style_bg_opa(scr_2, LV_OPA_COVER, 0);
    lv_obj_clear_flag(scr_2, LV_OBJ_FLAG_SCROLLABLE);

    /* ----------------- LEFT SIDEBAR ----------------- */
    lv_obj_t *sidebar = lv_obj_create(scr_2);
    lv_obj_set_size(sidebar, 220, LV_PCT(100));
    lv_obj_set_style_bg_color(sidebar, COLOR_SIDEBAR, 0);
    lv_obj_set_style_radius(sidebar, 0, 0);
    lv_obj_set_style_pad_all(sidebar, 8, 0);
    lv_obj_set_style_border_width(sidebar, 0, 0);
    lv_obj_align(sidebar, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_clear_flag(sidebar, LV_OBJ_FLAG_SCROLLABLE);

    static lv_point_precise_t line_points1[] = {
        {0,0},
        {0,702}
    };

    lv_obj_t *line1 = lv_line_create(sidebar);
    lv_line_set_points(line1, line_points1, 2);
    lv_obj_set_style_line_width(line1, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line1, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line1, LV_ALIGN_TOP_RIGHT, 6 , 0);
    

    /* Sidebar Title */
    lv_obj_t *title = lv_label_create(sidebar);
    lv_label_set_text(title, "BioChem Pro");
    lv_obj_set_style_text_color(title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 50, 6);

    lv_obj_t *shadow_t = lv_label_create(sidebar);
    lv_label_set_text(shadow_t, "Analyzer v4.2");
    lv_obj_set_style_text_color(shadow_t, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(shadow_t, &lv_font_montserrat_14, 0);
    lv_obj_align(shadow_t,LV_ALIGN_TOP_LEFT, 50, 30);


    lv_obj_t *icon1_bg =lv_obj_create(sidebar);
    lv_obj_set_size(icon1_bg, 40, 40);
    lv_obj_set_style_bg_color(icon1_bg, lv_color_hex(0x1670fb), 0);
    lv_obj_set_style_bg_opa(icon1_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(icon1_bg, 8, 0);
    lv_obj_set_style_border_width(icon1_bg,0,0);
    lv_obj_align(icon1_bg, LV_ALIGN_TOP_LEFT, 0, 6);
    lv_obj_clear_flag(icon1_bg, LV_OBJ_FLAG_SCROLLABLE);
    

    lv_obj_t *icon1 =lv_label_create(icon1_bg);
    lv_label_set_text(icon1, "\uf0c3");
    lv_obj_set_style_text_font(icon1, &fa_24, 0);
    lv_obj_set_style_text_color(icon1, lv_color_hex(0xf9f9f9) , 0);
    lv_obj_center(icon1);
    


    static lv_point_precise_t line_points[] = {
            {0,0},
            {213,0}
    };


    lv_obj_t *line = lv_line_create(sidebar);
    lv_line_set_points(line, line_points, 2);
    lv_obj_set_style_line_width(line, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line, LV_ALIGN_TOP_LEFT, -5 , 60);


    /* Sidebar menu (text only) */
    const char *menu_items[] = {
        "Analysis", " Work List",  " Reports"," Calibrations",
        "QC", "Methods", " Settings", " Maintenance",  " Exit"
    };


    const char *menu_icons[] = {
        FA_ANALYSIS,
        FA_WORKLIST,
        FA_REPORTS,
        FA_CALIB,
        FA_QC,
        FA_METHODS,
        FA_SETTINGS,
        FA_MAINT,
        FA_EXIT
    };

    int y_offset = 80; //gap between items

    for(int i = 0; i < 9; i++) {

        if(i == 6){
            y_offset += 170; //Extra gap after item 6 to split 
        }

        static lv_point_precise_t line_points[] = {
            {0,0},
            {213,0}
        };
        
        lv_obj_t *line = lv_line_create(sidebar);
        lv_line_set_points(line, line_points, 2);
        lv_obj_set_style_line_width(line, 1, LV_PART_MAIN);
        lv_obj_set_style_line_color(line, lv_color_hex(0x324556), LV_PART_MAIN);
        /* Position */
        lv_obj_align(line, LV_ALIGN_TOP_LEFT, -5 , 535);   // Y=280 → position between menu items
        
        
        lv_obj_t *btn = lv_btn_create(sidebar);
        lv_obj_set_size(btn, 190, 40);
        lv_obj_set_style_radius(btn, 10, 0);
        lv_obj_set_style_bg_color(btn, (i == 0) ? COLOR_ACCENT : lv_color_hex(0x1D2E40), LV_STATE_DEFAULT);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 8, y_offset);
        
        y_offset += 50; //gap between items
        
        if(menu_icons[i]) {
            lv_obj_t *icon = lv_label_create(btn);
            lv_label_set_text(icon, menu_icons[i]);
            lv_obj_set_style_text_font(icon, &fa_24, 0);
            lv_obj_set_style_text_color(icon, COLOR_TEXT, 0);
            lv_obj_align(icon, LV_ALIGN_LEFT_MID, 10, 0);
        }

        lv_obj_t *txt = lv_label_create(btn);
        lv_label_set_text(txt, menu_items[i]);
        lv_obj_set_style_text_font(txt, &lv_font_montserrat_16, 0);
        lv_obj_set_style_text_color(txt, COLOR_TEXT, 0);
        lv_obj_align(txt, LV_ALIGN_LEFT_MID, 40, 0);





        
    }

    /* ----------------- TOP BAR (inside content) ----------------- */
    lv_obj_t *content = lv_obj_create(scr_2);
    lv_obj_set_size(content, LV_PCT(84), LV_PCT(70));
    lv_obj_align(content, LV_ALIGN_TOP_MID,100 , -18);
    lv_obj_set_style_bg_opa(content, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(content, 0, LV_PART_MAIN);


    lv_obj_t *top_bar = create_top_bar(content);
    
    /* sharp line*/
    static lv_point_precise_t line_points2[] = {
        {0,0},
        {780,0}
    };
    lv_obj_t *line2 = lv_line_create(scr_2);
    lv_line_set_points(line2, line_points2, 2);
    lv_obj_set_style_line_width(line2, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line2, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line2, LV_ALIGN_TOP_LEFT, 220 , 56);


    /* Top 4 cards */
    lv_obj_t *card_method = create_card(scr_2, 140, 150);
    lv_obj_align(card_method, LV_ALIGN_TOP_LEFT, 250, 80);

    lv_obj_t *icon2 =lv_label_create(card_method);
    lv_label_set_text(icon2, "\uf492");
    lv_obj_set_style_text_font(icon2, &fa_24, 0);
    lv_obj_set_style_text_color(icon2, lv_color_hex(0x11AAC5) , 0);
    lv_obj_align(icon2, LV_IMAGE_ALIGN_TOP_RIGHT, 8,0);

    lv_obj_t *t_title = lv_label_create(card_method);
    lv_label_set_text(t_title, "Total Tests");
    lv_obj_set_style_text_color(t_title, COLOR_GRAY, 0); 
    lv_obj_set_style_text_font(t_title, &lv_font_montserrat_14, 0);
    lv_obj_align(t_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *t_val = lv_label_create(card_method);
    lv_label_set_text(t_val, "1.247");
    lv_obj_set_style_text_color(t_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(t_val, &lv_font_montserrat_26, 0);
    lv_obj_align(t_val, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_t *t_percent = lv_label_create(card_method);
    lv_label_set_text(t_percent, "+12% today");
    lv_obj_set_style_text_color(t_percent, COLOR_GREEN, 0);
    lv_obj_set_style_text_font(t_percent, &lv_font_montserrat_14, 0);
    lv_obj_align(t_percent, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    
    /* secound card*/
    lv_obj_t *card_method1 = create_card(scr_2, 140, 150);
    lv_obj_align(card_method1, LV_ALIGN_TOP_LEFT, 410, 80);

    lv_obj_t *icon3 =lv_label_create(card_method1);
    lv_label_set_text(icon3, "\uf017");
    lv_obj_set_style_text_font(icon3, &fa_24, 0);
    lv_obj_set_style_text_color(icon3, lv_color_hex(0XF4A432) , 0);
    lv_obj_align(icon3, LV_IMAGE_ALIGN_TOP_RIGHT, 8,0);

    lv_obj_t *p_title = lv_label_create(card_method1);
    lv_label_set_text(p_title, "Pending");
    lv_obj_set_style_text_color(p_title, COLOR_GRAY, 0); 
    lv_obj_set_style_text_font(p_title, &lv_font_montserrat_14, 0);
    lv_obj_align(p_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *p_val = lv_label_create(card_method1);
    lv_label_set_text(p_val, "23");
    lv_obj_set_style_text_color(p_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(p_val, &lv_font_montserrat_26, 0);
    lv_obj_align(p_val, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_t *p_text = lv_label_create(card_method1);
    lv_label_set_text(p_text, "In queue");
    lv_obj_set_style_text_color(p_text, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(p_text, &lv_font_montserrat_14, 0);
    lv_obj_align(p_text, LV_ALIGN_BOTTOM_LEFT, 0, 0);


    /* third card*/
    lv_obj_t *card_method2 = create_card(scr_2, 140, 150);
    lv_obj_align(card_method2, LV_ALIGN_TOP_LEFT, 570, 80);

    lv_obj_t *icon4 =lv_label_create(card_method2);
    lv_label_set_text(icon4, "\uf058");
    lv_obj_set_style_text_font(icon4, &fa_24, 0);
    lv_obj_set_style_text_color(icon4, lv_color_hex(0X28C85E) , 0);
    lv_obj_align(icon4, LV_IMAGE_ALIGN_TOP_RIGHT, 12,0);

    lv_obj_t *c_title = lv_label_create(card_method2);
    lv_label_set_text(c_title, "Completed");
    lv_obj_set_style_text_color(c_title, COLOR_GRAY, 0); 
    lv_obj_set_style_text_font(c_title, &lv_font_montserrat_14, 0);
    lv_obj_align(c_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *c_val = lv_label_create(card_method2);
    lv_label_set_text(c_val, "1.224");
    lv_obj_set_style_text_color(c_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(c_val, &lv_font_montserrat_26, 0);
    lv_obj_align(c_val, LV_ALIGN_LEFT_MID, 0, 0);

    lv_obj_t *c_text = lv_label_create(card_method2);
    lv_label_set_text(c_text, "98.2% success");
    lv_obj_set_style_text_color(c_text, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(c_text, &lv_font_montserrat_14, 0);
    lv_obj_align(c_text, LV_ALIGN_BOTTOM_LEFT, -5, 0);

    /* fourth card*/
    lv_obj_t *card_method3 = create_card(scr_2, 140, 150);
    lv_obj_align(card_method3, LV_ALIGN_TOP_LEFT, 730, 80);

    lv_obj_t *icon5 =lv_label_create(card_method3);
    lv_label_set_text(icon5, "\uf071");
    lv_obj_set_style_text_font(icon5, &fa_24, 0);
    lv_obj_set_style_text_color(icon5, lv_color_hex(0XEA474A) , 0);
    lv_obj_align(icon5, LV_IMAGE_ALIGN_TOP_RIGHT, 8,0);

    lv_obj_t *a_title = lv_label_create(card_method3);
    lv_label_set_text(a_title, "Alerts");
    lv_obj_set_style_text_color(a_title, COLOR_GRAY, 0); 
    lv_obj_set_style_text_font(a_title, &lv_font_montserrat_14, 0);
    lv_obj_align(a_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *a_val = lv_label_create(card_method3);
    lv_label_set_text(a_val, "2");
    lv_obj_set_style_text_color(a_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(a_val, &lv_font_montserrat_26, 0);
    lv_obj_align(a_val, LV_ALIGN_LEFT_MID, 0, -5);

    lv_obj_t *a_text = lv_label_create(card_method3);
    lv_label_set_text(a_text, "Requires \nattention");
    lv_obj_set_style_text_color(a_text, COLOR_RED, 0);
    lv_obj_set_style_text_font(a_text, &lv_font_montserrat_14, 0);
    lv_obj_align(a_text, LV_ALIGN_BOTTOM_LEFT, 0, 0);


    /* Recent Test Result card (left) */
    lv_obj_t *card_trend = create_card(scr_2, 300, 250);
    lv_obj_align(card_trend, LV_ALIGN_LEFT_MID, 250, 80);

    lv_obj_t *trend_title = lv_label_create(card_trend);
    lv_label_set_text(trend_title, "Recent Test Results");
    lv_obj_set_style_text_color(trend_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(trend_title, &lv_font_montserrat_14, 0);
    lv_obj_align(trend_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *card_0 = create_card(card_trend, 250, 50);
    lv_obj_align(card_0, LV_ALIGN_TOP_LEFT, 0, 30);
    lv_obj_set_style_bg_color(card_0, lv_color_hex(0x2A3549), 0);
    lv_obj_set_style_bg_opa(card_0, LV_OPA_COVER, 0);


    lv_obj_t *g_title = lv_label_create(card_0);
    lv_label_set_text(g_title, "Glucose");
    lv_obj_set_style_text_color(g_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(g_title, &lv_font_montserrat_12, 0);
    lv_obj_align(g_title, LV_ALIGN_TOP_LEFT, 40, -10);

    lv_obj_t *g_val = lv_label_create(card_0);
    lv_label_set_text(g_val, "Sample #4521");
    lv_obj_set_style_text_color(g_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(g_val, &lv_font_montserrat_12 ,0);
    lv_obj_align(g_val, LV_ALIGN_TOP_LEFT, 40, 5);

    lv_obj_t *g_mg = lv_label_create(card_0);
    lv_label_set_text(g_mg, "95 mg/dl");
    lv_obj_set_style_text_color(g_mg, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(g_mg, &lv_font_montserrat_12 ,0);
    lv_obj_align(g_mg, LV_ALIGN_RIGHT_MID, 0, 0);

    lv_obj_t *icon9_bg =lv_obj_create(card_0);
    lv_obj_set_size(icon9_bg, 35, 35);
    lv_obj_set_style_bg_color(icon9_bg, lv_color_hex(0x264C61), 0);
    lv_obj_set_style_bg_opa(icon9_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(icon9_bg, 8, 0);
    lv_obj_set_style_border_width(icon9_bg,0,0);
    lv_obj_clear_flag(icon9_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(icon9_bg, LV_ALIGN_TOP_LEFT, -12, -15);

    lv_obj_t *icon9 =lv_label_create(icon9_bg);
    lv_label_set_text(icon9, "\uf043");
    lv_obj_set_style_text_font(icon9, &fa_24, 0);
    lv_obj_set_style_text_color(icon9, lv_color_hex(0x21D6EA) , 0);
    lv_obj_center(icon9);

    lv_obj_t *card_1 = create_card(card_trend, 250, 50);
    lv_obj_align(card_1, LV_ALIGN_LEFT_MID, 0, 13);
    lv_obj_set_style_bg_color(card_1, lv_color_hex(0x2A3549), 0);
    lv_obj_set_style_bg_opa(card_1, LV_OPA_COVER, 0);

    lv_obj_t *ch_title = lv_label_create(card_1);
    lv_label_set_text(ch_title, "Cholesterol");
    lv_obj_set_style_text_color(ch_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(ch_title, &lv_font_montserrat_12, 0);
    lv_obj_align(ch_title, LV_ALIGN_TOP_LEFT, 40, -10);

    lv_obj_t *ch_val = lv_label_create(card_1);
    lv_label_set_text(ch_val, "Sample #4520");
    lv_obj_set_style_text_color(ch_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(ch_val, &lv_font_montserrat_12 ,0);
    lv_obj_align(ch_val, LV_ALIGN_TOP_LEFT, 40, 5);

    lv_obj_t *ch_mg = lv_label_create(card_1);
    lv_label_set_text(ch_mg, "180 mg/dl");
    lv_obj_set_style_text_color(ch_mg, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(ch_mg, &lv_font_montserrat_12 ,0);
    lv_obj_align(ch_mg, LV_ALIGN_RIGHT_MID, 0, 0);

    lv_obj_t *icon8_bg =lv_obj_create(card_1);
    lv_obj_set_size(icon8_bg, 35, 35);
    lv_obj_set_style_bg_color(icon8_bg, lv_color_hex(0x2B446B), 0);
    lv_obj_set_style_bg_opa(icon8_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(icon8_bg, 8, 0);
    lv_obj_set_style_border_width(icon8_bg,0,0);
    lv_obj_clear_flag(icon8_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(icon8_bg, LV_ALIGN_TOP_LEFT, -12, -15);

    lv_obj_t *icon8 =lv_label_create(icon8_bg);
    lv_label_set_text(icon8, "\uf21e");
    lv_obj_set_style_text_font(icon8, &fa_24, 0);
    lv_obj_set_style_text_color(icon8, lv_color_hex(0x82B2F1) , 0);
    lv_obj_center(icon8);

    
    lv_obj_t *card_2 = create_card(card_trend, 250, 50);
    lv_obj_align(card_2, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_style_bg_color(card_2, lv_color_hex(0x2A3549), 0);
    lv_obj_set_style_bg_opa(card_2, LV_OPA_COVER, 0);


    lv_obj_t *cr_title = lv_label_create(card_2);
    lv_label_set_text(cr_title, "Creatinine");
    lv_obj_set_style_text_color(cr_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(cr_title, &lv_font_montserrat_12, 0);
    lv_obj_align(cr_title, LV_ALIGN_TOP_LEFT, 40, -10);

    lv_obj_t *cr_val = lv_label_create(card_2);
    lv_label_set_text(cr_val, "Sample #4519");
    lv_obj_set_style_text_color(cr_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(cr_val, &lv_font_montserrat_12 ,0);
    lv_obj_align(cr_val, LV_ALIGN_TOP_LEFT, 40, 5);

    lv_obj_t *cr_mg = lv_label_create(card_2);
    lv_label_set_text(cr_mg, "1.1 mg/dl");
    lv_obj_set_style_text_color(cr_mg, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(cr_mg, &lv_font_montserrat_12 ,0);
    lv_obj_align(cr_mg, LV_ALIGN_RIGHT_MID, 0, 0);

    lv_obj_t *icon7_bg =lv_obj_create(card_2);
    lv_obj_set_size(icon7_bg, 35, 35);
    lv_obj_set_style_bg_color(icon7_bg, lv_color_hex(0x403A69), 0);
    lv_obj_set_style_bg_opa(icon7_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(icon7_bg, 8, 0);
    lv_obj_set_style_border_width(icon7_bg,0,0);
    lv_obj_clear_flag(icon7_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(icon7_bg, LV_ALIGN_TOP_LEFT, -12, -15);

    lv_obj_t *icon7 =lv_label_create(icon7_bg);
    lv_label_set_text(icon7, "\uf48e");
    lv_obj_set_style_text_font(icon7, &fa_24, 0);
    lv_obj_set_style_text_color(icon7, lv_color_hex(0xB793F6) , 0);
    lv_obj_center(icon7);

    /* System Status card (right) */
    lv_obj_t *card_result = create_card(scr_2, 300, 250);
    lv_obj_align(card_result, LV_ALIGN_LEFT_MID, 570, 80);

    lv_obj_t *res_title = lv_label_create(card_result);
    lv_label_set_text(res_title, "System Status");
    lv_obj_set_style_text_color(res_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(res_title, &lv_font_montserrat_14, 0);
    lv_obj_align(res_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *a_parent = lv_label_create(card_result);
    lv_obj_set_size(a_parent, 250, 28);
    lv_obj_align(a_parent, LV_ALIGN_TOP_LEFT, 0, 35);

    lv_obj_t *A_title = lv_label_create(a_parent);
    lv_label_set_text(A_title, "Reagent A");
    lv_obj_set_style_text_color(A_title, COLOR_GRAY,0);
    lv_obj_set_style_text_font(A_title, &lv_font_montserrat_12, 0);
    lv_obj_align(A_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *a_percent = lv_label_create(a_parent);
    lv_label_set_text(a_percent, "85%");
    lv_obj_set_style_text_color(a_percent, COLOR_GRAY,0);
    lv_obj_set_style_text_font(a_percent, &lv_font_montserrat_12, 0);
    lv_obj_align(a_percent, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_t *bar = lv_bar_create(a_parent);
    lv_obj_set_size(bar, 250, 8);
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_bar_set_range(bar, 0, 100);
    lv_bar_set_value(bar, 85, LV_ANIM_ON);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0x31C662), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0x324259), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);

    /* ------ */
    lv_obj_t *b_parent = lv_label_create(card_result);
    lv_obj_set_size(b_parent, 250, 28);
    lv_obj_align(b_parent, LV_ALIGN_LEFT_MID, 0, -7);

    lv_obj_t *b_title = lv_label_create(b_parent);
    lv_label_set_text(b_title, "Reagent B");
    lv_obj_set_style_text_color(b_title, COLOR_GRAY,0);
    lv_obj_set_style_text_font(b_title, &lv_font_montserrat_12, 0);
    lv_obj_align(b_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *b_percent = lv_label_create(b_parent);
    lv_label_set_text(b_percent, "62%");
    lv_obj_set_style_text_color(b_percent, COLOR_GRAY,0);
    lv_obj_set_style_text_font(b_percent, &lv_font_montserrat_12, 0);
    lv_obj_align(b_percent, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_t *bar1 = lv_bar_create(b_parent);
    lv_obj_set_size(bar1, 250, 8);
    lv_obj_align(bar1, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_bar_set_range(bar1, 0, 100);
    lv_bar_set_value(bar1, 62, LV_ANIM_ON);
    lv_obj_set_style_bg_color(bar1, lv_color_hex(0x31C662), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(bar1, LV_OPA_COVER, LV_PART_INDICATOR);

    lv_obj_set_style_bg_color(bar1, lv_color_hex(0x324259), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar1, LV_OPA_COVER, LV_PART_MAIN);

    /* ----------- */
    lv_obj_t *wash_parent = lv_label_create(card_result);
    lv_obj_set_size(wash_parent, 250, 28);
    lv_obj_align(wash_parent, LV_ALIGN_LEFT_MID, 0, 40);

    lv_obj_t *wash_title = lv_label_create(wash_parent);
    lv_label_set_text(wash_title, "Wash Solution");
    lv_obj_set_style_text_color(wash_title, COLOR_GRAY,0);
    lv_obj_set_style_text_font(wash_title, &lv_font_montserrat_12, 0);
    lv_obj_align(wash_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *wash_percent = lv_label_create(wash_parent);
    lv_label_set_text(wash_percent, "28%");
    lv_obj_set_style_text_color(wash_percent, COLOR_GRAY,0);
    lv_obj_set_style_text_font(wash_percent, &lv_font_montserrat_12, 0);
    lv_obj_align(wash_percent, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_t *bar2 = lv_bar_create(wash_parent);
    lv_obj_set_size(bar2, 250, 8);
    lv_obj_align(bar2, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_bar_set_range(bar2, 0, 100);
    lv_bar_set_value(bar2, 28, LV_ANIM_ON);
    lv_obj_set_style_bg_color(bar2, lv_color_hex(0xEDA222), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(bar2, LV_OPA_COVER, LV_PART_INDICATOR);

    lv_obj_set_style_bg_color(bar2, lv_color_hex(0x324259), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar2, LV_OPA_COVER, LV_PART_MAIN);

    /* -------- */
    lv_obj_t *waste_parent = lv_label_create(card_result);
    lv_obj_set_size(waste_parent, 250, 28);
    lv_obj_align(waste_parent, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    lv_obj_t *waste_title = lv_label_create(waste_parent);
    lv_label_set_text(waste_title, "Waste Container");
    lv_obj_set_style_text_color(waste_title, COLOR_GRAY,0);
    lv_obj_set_style_text_font(waste_title, &lv_font_montserrat_12, 0);
    lv_obj_align(waste_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *waste_percent = lv_label_create(waste_parent);
    lv_label_set_text(waste_percent, "72%");
    lv_obj_set_style_text_color(waste_percent, COLOR_GRAY,0);
    lv_obj_set_style_text_font(waste_percent, &lv_font_montserrat_12, 0);
    lv_obj_align(waste_percent, LV_ALIGN_TOP_RIGHT, 0, 0);


    lv_obj_t *bar3 = lv_bar_create(waste_parent);
    lv_obj_set_size(bar3, 250, 8);
    lv_obj_align(bar3, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_bar_set_range(bar3, 0, 100);
    lv_bar_set_value(bar3, 72, LV_ANIM_ON);
    lv_obj_set_style_bg_color(bar3, lv_color_hex(0xEF7930), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(bar3, LV_OPA_COVER, LV_PART_INDICATOR);

    lv_obj_set_style_bg_color(bar3, lv_color_hex(0x324259), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar3, LV_OPA_COVER, LV_PART_MAIN);


    lv_obj_t *bottom_bar = create_bottom_bar(scr_2);

    lv_obj_t *footer_label = lv_label_create(bottom_bar);
    lv_label_set_text(footer_label,
        LV_SYMBOL_PLAY" System Ready     "
        "Temp: 37.2°C   "
        LV_SYMBOL_WIFI" Connected         "
        "Last Cal: 2h ago     "
        "User: Dr. Smith     "
        "Session: 3h 24m"
    );
  
    lv_obj_set_style_text_color(footer_label, lv_color_hex(0x9CA3AF), 0);
    lv_obj_set_style_text_font(footer_label, &lv_font_montserrat_12, 0);
    lv_obj_align(footer_label, LV_ALIGN_TOP_MID, 0, 10);

    /* sharp line */
    static lv_point_precise_t line_points3[] = {
        {0,0},
        {780,0}
    };
    lv_obj_t *line3 = lv_line_create(scr_2);
    lv_line_set_points(line3, line_points3, 2);
    lv_obj_set_style_line_width(line3, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line3, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line3, LV_ALIGN_BOTTOM_MID, 110 , -60);


}






