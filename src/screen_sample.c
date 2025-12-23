#include "screen_bio.h"
#include <stdio.h>
#include "lvgl.h"
#include "assets/fonts/fa_24.h"


/*----------- ICONS------------*/
#define FA_ANALYSIS   "\uf201"
#define FA_WORKLIST   "\uf0ae"
#define FA_REPORTS    "\uf15c"
// #define FA_CALIB      "\uf1de" // SLIDERS
#define FA_SETTINGS   "\uf013"
// #define FA_EXIT       "\uf08b"
// #define FA_MAINT      "\uf0ad" // WRENCH
#define FA_FLASK      "\uf0c3"
// #define FA_QC         "\ue596"
#define FA_METHODS    "\uf492" // VIALS
#define FA_CLOCK      "\uf017"
// #define FA_DOT       "\uf192"



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
#define FA_MICROSCOPE  "\uf610"
#define FA_Patient    "\uf236"
#define FA_HOS       "\uf0f8"
#define FA_user       "\uf007"
#define FA_TEMP         "\uf2c9"
#define FA_lungs        "\uf82f"
#define FA_DOC        "\uf0f0"
#define FA_TRUNK      "\uf0f9"


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
    lv_obj_set_style_border_width(bar, 0, 0);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);


    lv_obj_t *title = lv_label_create(bar);
    lv_label_set_text(title, "Analysis");
    lv_obj_set_size(title, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_center(title);


    return bar;
}

static lv_obj_t * create_bottom_bar(lv_obj_t *parent)
{
    lv_obj_t *bm_bar = lv_obj_create(parent);
    lv_obj_set_size(bm_bar, LV_PCT(78), 40);
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

lv_obj_t *scr_4 = NULL;

/* ---------- CREATE SCREEN ---------- */
void screen_sample_create(void)
{
    /* Root screen */
    scr_4 = lv_obj_create(NULL);
    // lv_scr_load(scr);
    lv_obj_set_style_bg_color(scr_4, COLOR_BG, 0);
    lv_obj_set_style_bg_opa(scr_4, LV_OPA_COVER, 0);
    lv_obj_clear_flag(scr_4, LV_OBJ_FLAG_SCROLLABLE);
    

    /* ----------------- LEFT SIDEBAR ----------------- */
    lv_obj_t *sidebar = lv_obj_create(scr_4);
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
    lv_label_set_text(title, "BioAnalyzer");
    lv_obj_set_style_text_color(title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 50, 15);



    // lv_obj_t *icon1_bg =lv_obj_create(sidebar);
    // lv_obj_set_size(icon1_bg, 40, 40);
    // lv_obj_set_style_bg_color(icon1_bg, lv_color_hex(0x1670fb), 0);
    // lv_obj_set_style_bg_opa(icon1_bg, LV_OPA_COVER, 0);
    // lv_obj_set_style_radius(icon1_bg, 8, 0);
    // lv_obj_set_style_border_width(icon1_bg,0,0);
    // lv_obj_align(icon1_bg, LV_ALIGN_TOP_LEFT, 0, 6);
    // lv_obj_clear_flag(icon1_bg, LV_OBJ_FLAG_SCROLLABLE);
    

    // lv_obj_t *icon1 =lv_label_create(icon1_bg);
    // lv_label_set_text(icon1, "\uf0c3");
    // lv_obj_set_style_text_font(icon1, &fa_24, 0);
    // lv_obj_set_style_text_color(icon1, lv_color_hex(0xf9f9f9) , 0);
    // lv_obj_center(icon1);
    
    


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
        "Dashboard", " Samples",  " Analysis"," Reports",
        " Settings"
    };

    
    const char *menu_icons[] = {
        FA_ANALYSIS,
        FA_METHODS,
        FA_MICROSCOPE,
        FA_REPORTS,
        FA_SETTINGS
        
    };

    int y_offset = 80; //gap between items

    for(int i = 0; i < 5; i++) {

  
        
        lv_obj_t *btn = lv_btn_create(sidebar);
        lv_obj_set_size(btn, 190, 40);
        lv_obj_set_style_radius(btn, 10, 0);
        lv_obj_set_style_bg_color(btn, (i == 2) ? COLOR_ACCENT : lv_color_hex(0x1D2E40), LV_STATE_DEFAULT);
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

    /* -------------- TOP BAR: (content) ------------ */
    lv_obj_t *content = lv_obj_create(scr_4);
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
    lv_obj_t *line2 = lv_line_create(scr_4);
    lv_line_set_points(line2, line_points2, 2);
    lv_obj_set_style_line_width(line2, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line2, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line2, LV_ALIGN_TOP_LEFT, 220 , 56);


    /* ----------------- TOP INFO CARDS ----------------- */
    lv_obj_t *search_content = lv_obj_create(scr_4);
    lv_obj_set_size(search_content, LV_PCT(75), LV_PCT(80));
    lv_obj_align(search_content, LV_ALIGN_TOP_MID, 100, 70);
    lv_obj_set_style_bg_opa(search_content, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(search_content, 0, 0);

    /* Scan Method */
    lv_obj_t *scan_lbl = lv_label_create(search_content);
    lv_label_set_text(scan_lbl, "Scan Sample");
    lv_obj_set_style_text_color(scan_lbl, lv_color_white(), 0);
    lv_obj_align(scan_lbl, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *search = lv_textarea_create(search_content);
    lv_obj_set_size(search, LV_PCT(100), 40);
    lv_textarea_set_placeholder_text(search, "Enter or select scan sample ID");
    lv_obj_set_style_text_color(search, lv_color_white(), 0);
    lv_obj_set_style_bg_color(search, lv_color_hex(0x1E293B), 0);
    lv_obj_set_style_bg_opa(search, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(search, lv_color_hex(0x8A97A7), 0);
    lv_obj_set_style_border_width(search, 1, 0);
    lv_obj_set_style_border_opa(search, LV_OPA_40, 0);
    lv_obj_align(search, LV_ALIGN_TOP_LEFT, 0, 30);
    lv_obj_clear_flag(search, LV_OBJ_FLAG_SCROLLABLE);

                /* 8 cards for search */
    /* Top info cards */
    lv_obj_t *card_scan = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan, LV_ALIGN_TOP_LEFT, 250, 200);

    lv_obj_t *icon_lb = lv_label_create(card_scan);
    lv_label_set_text(icon_lb, FA_user );
    lv_obj_set_style_text_font(icon_lb, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb, lv_color_hex(0x60A3FF) , 0);
    lv_obj_align(icon_lb, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb = lv_label_create(card_scan);
    lv_label_set_text(lb, "Patient-001");
    lv_obj_set_style_text_color(lb, lv_color_white(), 0);
    lv_obj_align(lb, LV_ALIGN_BOTTOM_MID, 0, -5);

    // ------
    lv_obj_t *card_scan1 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan1, LV_ALIGN_TOP_LEFT, 430, 200);

    lv_obj_t *icon_lb1 = lv_label_create(card_scan1);
    lv_label_set_text(icon_lb1, "\uf0f0" );
    lv_obj_set_style_text_font(icon_lb1, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb1, lv_color_hex(0xEA7775) , 0);
    lv_obj_align(icon_lb1, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb1 = lv_label_create(card_scan1);
    lv_label_set_text(lb1, "Patient-002");
    lv_obj_set_style_text_color(lb1, lv_color_white(), 0);
    lv_obj_align(lb1, LV_ALIGN_BOTTOM_MID, 0, -5);

    //  -----------
    lv_obj_t *card_scan2 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan2, LV_ALIGN_TOP_LEFT, 610, 200);

    lv_obj_t *icon_lb2 = lv_label_create(card_scan2);
    lv_label_set_text(icon_lb2, FA_Patient );
    lv_obj_set_style_text_font(icon_lb2, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb2, lv_color_hex(0xC285F8) , 0);
    lv_obj_align(icon_lb2, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb2 = lv_label_create(card_scan2);
    lv_label_set_text(lb2, "Patient-003");
    lv_obj_set_style_text_color(lb2, lv_color_white(), 0);
    lv_obj_align(lb2, LV_ALIGN_BOTTOM_MID, 0, -5);
    
    // ----------
    lv_obj_t *card_scan3 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan3, LV_ALIGN_TOP_LEFT, 790, 200);

    lv_obj_t *icon_lb3 = lv_label_create(card_scan3);
    lv_label_set_text(icon_lb3, FA_lungs );
    lv_obj_set_style_text_font(icon_lb3, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb3, lv_color_hex(0x6AD795) , 0);
    lv_obj_align(icon_lb3, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb3 = lv_label_create(card_scan3);
    lv_label_set_text(lb3, "Patient-004");
    lv_obj_set_style_text_color(lb3, lv_color_white(), 0);
    lv_obj_align(lb3, LV_ALIGN_BOTTOM_MID, 0, -5);

    // ----------
    lv_obj_t *card_scan4 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan4, LV_ALIGN_LEFT_MID, 250, 50);

    lv_obj_t *icon_lb4 = lv_label_create(card_scan4);
    lv_label_set_text(icon_lb4, FA_TRUNK);
    lv_obj_set_style_text_font(icon_lb4, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb4, lv_color_hex(0xF8CC09) , 0);
    lv_obj_align(icon_lb4, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb4 = lv_label_create(card_scan4);
    lv_label_set_text(lb4, "Emergency-01");
    lv_obj_set_style_text_color(lb4, lv_color_white(), 0);
    lv_obj_align(lb4, LV_ALIGN_BOTTOM_MID, 0, -5);

    // ---------
    lv_obj_t *card_scan5 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan5, LV_ALIGN_LEFT_MID, 430, 50);

    lv_obj_t *icon_lb5 = lv_label_create(card_scan5);
    lv_label_set_text(icon_lb5, FA_HOS );
    lv_obj_set_style_text_font(icon_lb5, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb5, lv_color_hex(0x60A3FF) , 0);
    lv_obj_align(icon_lb5, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb5 = lv_label_create(card_scan5);
    lv_label_set_text(lb5, "Control-Sample");
    lv_obj_set_style_text_color(lb5, lv_color_white(), 0);
    lv_obj_align(lb5, LV_ALIGN_BOTTOM_MID, 0, -5);

    // -----------
    lv_obj_t *card_scan6 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan6, LV_ALIGN_LEFT_MID, 610, 50);

    lv_obj_t *icon_lb6 = lv_label_create(card_scan6);
    lv_label_set_text(icon_lb6, FA_METHODS );
    lv_obj_set_style_text_font(icon_lb6, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb6, lv_color_hex(0xFC9338) , 0);
    lv_obj_align(icon_lb6, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb6 = lv_label_create(card_scan6);
    lv_label_set_text(lb6, "Blank-Sample");
    lv_obj_set_style_text_color(lb6, lv_color_white(), 0);
    lv_obj_align(lb6, LV_ALIGN_BOTTOM_MID, 0, -5);

    //  ----------
    lv_obj_t *card_scan7 = create_card(scr_4, 150, 120);
    lv_obj_align(card_scan7, LV_ALIGN_LEFT_MID, 790, 50);

    lv_obj_t *icon_lb7 = lv_label_create(card_scan7);
    lv_label_set_text(icon_lb7, "\uf0c3");
    lv_obj_set_style_text_font(icon_lb7, &fa_24, 0);
    lv_obj_set_style_text_color(icon_lb7, lv_color_hex(0x60A3FF) , 0);
    lv_obj_align(icon_lb7, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *lb7 = lv_label_create(card_scan7);
    lv_label_set_text(lb7, "QC-Standard");
    lv_obj_set_style_text_color(lb7, lv_color_white(), 0);
    lv_obj_align(lb7, LV_ALIGN_BOTTOM_MID, 0, -5);

    /* Bottom info card */
    lv_obj_t *card_bottom = create_card(search_content, 700, 80);
    lv_obj_align(card_bottom, LV_ALIGN_BOTTOM_MID, 0, -40);

    lv_obj_t *lb_bottom = lv_label_create(card_bottom);
    lv_label_set_text(lb_bottom,  "System Status");
    lv_obj_set_style_text_color(lb_bottom, COLOR_GRAY, 0);
    lv_obj_align(lb_bottom, LV_ALIGN_TOP_LEFT, 30, 0);

    lv_obj_t *re = lv_label_create(card_bottom);
    lv_label_set_text(re, LV_SYMBOL_PLAY "  Ready" );
    lv_obj_set_style_text_color(re, COLOR_GREEN, 0);
    lv_obj_align(re, LV_ALIGN_BOTTOM_LEFT, 45, 2);

    lv_obj_t *lb1_bottom = lv_label_create(card_bottom);
    lv_label_set_text(lb1_bottom, "Temperature");
    lv_obj_set_style_text_color(lb1_bottom, COLOR_GRAY, 0);
    lv_obj_align(lb1_bottom, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *icon_bot = lv_label_create(card_bottom);
    lv_label_set_text(icon_bot, "\uf2c9");
    lv_obj_set_style_text_font(icon_bot, &fa_24, 0);
    lv_obj_set_style_text_color(icon_bot, lv_color_hex(0x71A2E8) , 0);
    lv_obj_align(icon_bot, LV_ALIGN_BOTTOM_MID, -35, 10);

    lv_obj_t *lb_text = lv_label_create(card_bottom);
    lv_label_set_text(lb_text, "37.0 C");
    lv_obj_set_style_text_color(lb_text, lv_color_white(), 0);
    lv_obj_align(lb_text, LV_ALIGN_BOTTOM_MID, 0, 10);

    lv_obj_t *lb2_bottom = lv_label_create(card_bottom);
    lv_label_set_text(lb2_bottom, "Active Tests");
    lv_obj_set_style_text_color(lb2_bottom, COLOR_GRAY, 0);
    lv_obj_align(lb2_bottom, LV_ALIGN_TOP_RIGHT, -30, 0);

    lv_obj_t *lb1_text = lv_label_create(card_bottom);
    lv_label_set_text(lb1_text, "3 Running");
    lv_obj_set_style_text_color(lb1_text, lv_color_white(), 0);
    lv_obj_align(lb1_text, LV_ALIGN_BOTTOM_RIGHT, -20, 8);


    lv_obj_t *icon_bot1 = lv_label_create(card_bottom);
    lv_label_set_text(icon_bot1, "\uf0c3");
    lv_obj_set_style_text_font(icon_bot1, &fa_24, 0);
    lv_obj_set_style_text_color(icon_bot1, lv_color_hex(0xF0CC3A) , 0);
    lv_obj_align(icon_bot1, LV_ALIGN_BOTTOM_RIGHT, -100, 8);

}
