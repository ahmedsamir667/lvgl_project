#include "screen_analysis.h"
#include <stdio.h>
#include <math.h>
#include "lvgl.h"
#include "assets/fonts/fa_24.h"
// #include "assets/fonts/fa_24.c"


/*----------- ICONS------------*/
#define FA_ANALYSIS   "\uf201"
#define FA_WORKLIST   "\uf0ae"
#define FA_REPORTS    "\uf15c"
#define FA_CALIB      "\uf1de" // SLIDERS
#define FA_SETTINGS   "\uf013"
#define FA_EXIT       "\uf08b"
#define FA_MAINT      "\uf0ad" // WRENCH
#define FA_FLASK      "\uf0c3"
#define FA_QC         "\ue596"
#define FA_METHODS    "\uf610" // VIALS
#define FA_CLOCK      "\uf017"
#define FA_DOT       "\uf192"
#define FA_MICROCHIP  "\uf252"

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

    /* left container: title + badge */
    lv_obj_t *left = lv_obj_create(bar);
    lv_obj_remove_style_all(left);
    lv_obj_set_flex_flow(left, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(left, 10, 0);
    lv_obj_set_size(left, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(left, LV_ALIGN_LEFT_MID, 12, 0);


    lv_obj_t *title = lv_label_create(left);
    lv_label_set_text(title, "Sample Analysis");
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
    lv_obj_set_size(right, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(right, LV_ALIGN_RIGHT_MID, -12, 0);

    lv_obj_t *time_icon = lv_label_create(bar);
    lv_label_set_text(time_icon, FA_CLOCK );
    lv_obj_set_style_text_font(time_icon, &fa_24, 0);
    lv_obj_set_style_text_color(time_icon, COLOR_GRAY, 0);
    lv_obj_align(time_icon, LV_ALIGN_TOP_MID, 180, 7);

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

lv_obj_t *scr = NULL;

/* ---------- CREATE SCREEN ---------- */
void screen_analysis_create(void)
{
    /* Root screen */
    scr = lv_obj_create(NULL);
    // lv_scr_load(scr);
    lv_obj_set_style_bg_color(scr, COLOR_BG, 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    

    /* ----------------- LEFT SIDEBAR ----------------- */
    lv_obj_t *sidebar = lv_obj_create(scr);
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


        // lv_obj_t *lbl = lv_label_create(btn);
        // lv_label_set_text(lbl, menu_items[i]);
        // lv_obj_set_style_text_color(lbl, COLOR_TEXT, 0);
        // lv_obj_set_style_text_align(lbl, LV_ALIGN_LEFT_MID, 0);


        
    }

    /* ----------- TOP BAR  ---------- */
    lv_obj_t *content = lv_obj_create(scr);
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
    lv_obj_t *line2 = lv_line_create(scr);
    lv_line_set_points(line2, line_points2, 2);
    lv_obj_set_style_line_width(line2, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line2, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line2, LV_ALIGN_TOP_LEFT, 220 , 56);


    /* ----------------- TOP INFO CARDS ----------------- */
    /* Left info card: Method / Sample / Sample ID */
    lv_obj_t *card_method = create_card(scr, 350, 175);
    lv_obj_align(card_method, LV_ALIGN_TOP_LEFT, 250, 80);

    lv_obj_t *m_title = lv_label_create(card_method);
    lv_label_set_text(m_title, "Method Name");
    lv_obj_set_style_text_color(m_title, COLOR_GRAY, 0); //<=
    lv_obj_set_style_text_font(m_title, &lv_font_montserrat_12, 0);
    lv_obj_align(m_title, LV_ALIGN_TOP_LEFT, 6, 6);

    lv_obj_t *m_val = lv_label_create(card_method);
    lv_label_set_text(m_val, "Glucose Oxidase");
    lv_obj_set_style_text_color(m_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(m_val, &lv_font_montserrat_16, 0);
    lv_obj_align(m_val, LV_ALIGN_TOP_LEFT, 6, 26);

    lv_obj_t *samp_lbl = lv_label_create(card_method);
    lv_label_set_text(samp_lbl, "Sample Name");
    lv_obj_set_style_text_color(samp_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(samp_lbl, &lv_font_montserrat_12, 0);
    lv_obj_align(samp_lbl, LV_ALIGN_TOP_LEFT, 6, 55);

    lv_obj_t *samp_val = lv_label_create(card_method);
    lv_label_set_text(samp_val, "Patient-001");
    lv_obj_set_style_text_color(samp_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(samp_val, &lv_font_montserrat_14, 0);
    lv_obj_align(samp_val, LV_ALIGN_TOP_LEFT, 6, 75);

    lv_obj_t *id_lbl = lv_label_create(card_method);
    lv_label_set_text(id_lbl, "Sample ID");
    lv_obj_set_style_text_color(id_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(id_lbl, &lv_font_montserrat_12, 0);
    lv_obj_align(id_lbl, LV_ALIGN_TOP_LEFT, 6, 100);

    lv_obj_t *id_val = lv_label_create(card_method);
    lv_label_set_text(id_val, "SMP-4521");
    lv_obj_set_style_text_color(id_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(id_val, &lv_font_montserrat_14, 0);
    lv_obj_align(id_val, LV_ALIGN_TOP_LEFT, 6, 120);

    /* Right info card: Blank/Absorbance */
    lv_obj_t *card_read = create_card(scr, 350, 175);
    lv_obj_align(card_read, LV_ALIGN_TOP_LEFT, 630, 80);

    lv_obj_t *br_lbl = lv_label_create(card_read);
    lv_label_set_text(br_lbl, "Blank Reading");
    lv_obj_set_style_text_color(br_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(br_lbl, &lv_font_montserrat_12, 0);
    lv_obj_align(br_lbl, LV_ALIGN_TOP_LEFT, 6, 6);

    lv_obj_t *br_val = lv_label_create(card_read);
    lv_label_set_text(br_val, "0.023");
    lv_obj_set_style_text_color(br_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(br_val, &lv_font_montserrat_16, 0);
    lv_obj_align(br_val, LV_ALIGN_TOP_LEFT, 6, 24);

    lv_obj_t *abs_lbl = lv_label_create(card_read);
    lv_label_set_text(abs_lbl, "Absorbance Reading");
    lv_obj_set_style_text_color(abs_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(abs_lbl, &lv_font_montserrat_12, 0);
    lv_obj_align(abs_lbl, LV_ALIGN_TOP_LEFT, 6, 52);

    lv_obj_t *abs_val = lv_label_create(card_read);
    lv_label_set_text(abs_val, "0.847");
    lv_obj_set_style_text_color(abs_val, COLOR_NUM, 0);
    lv_obj_set_style_text_font(abs_val, &lv_font_montserrat_18, 0);
    lv_obj_align(abs_val, LV_ALIGN_TOP_LEFT, 6, 70);

    /*  active indicator */
    lv_obj_t *ra = lv_label_create(card_read);
    lv_label_set_text(ra, LV_SYMBOL_PLAY " Reading Active");
    lv_obj_set_style_text_color(ra, COLOR_GREEN, 0);
    lv_obj_set_style_text_font(ra, &lv_font_montserrat_12, 0);
    lv_obj_align(ra, LV_ALIGN_TOP_LEFT, 6, 120);
    

    /* Trend results card (left) */
    lv_obj_t *card_trend = create_card(scr, 500, 300);
    lv_obj_align(card_trend, LV_ALIGN_LEFT_MID, 250, 80);

    lv_obj_t *trend_title = lv_label_create(card_trend);
    lv_label_set_text(trend_title, "Trend Results");
    lv_obj_set_style_text_color(trend_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(trend_title, &lv_font_montserrat_14, 0);
    lv_obj_align(trend_title, LV_ALIGN_TOP_LEFT, 6, 6);

    /* Chart */
    lv_obj_t *chart = lv_chart_create(card_trend);
    lv_obj_set_size(chart, 400, 180);
    lv_obj_align(chart, LV_ALIGN_BOTTOM_LEFT, 30, -20);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    
    /* Use 51 points to match the original code */
    const int POINT_COUNT = 51;
    lv_chart_set_point_count(chart, POINT_COUNT);

    /* Axis ranges (Y normalized 0..100 for visual) */
    lv_chart_set_axis_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_axis_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, POINT_COUNT - 1);

    lv_obj_set_style_bg_color(chart, lv_color_hex(0x15232F), 0);

    /* Series (v8 requires axis parameter) */
    lv_chart_series_t *ser = lv_chart_add_series(chart, COLOR_ACCENT, LV_CHART_AXIS_PRIMARY_Y);

    /* Example points that match rising curve -> scaled to 0..100 */
    for(int i = 0; i < POINT_COUNT; i++) {
        float t = (float)i / (POINT_COUNT - 1);
        float v = 1.0f - expf(-3.5f * t); /* curve */
        int val = (int)(v * 100.0f);
        /* Use lv_chart_set_next_value to append values into the series */
        lv_chart_set_next_value(chart, ser, val);
    }
    lv_chart_refresh(chart);

    /* Analysis Result card (right) */
    lv_obj_t *card_result = create_card(scr, 200, 300);
    lv_obj_align(card_result, LV_ALIGN_LEFT_MID, 780, 80);

    lv_obj_t *res_title = lv_label_create(card_result);
    lv_label_set_text(res_title, "Analysis Result");
    lv_obj_set_style_text_color(res_title, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(res_title, &lv_font_montserrat_14, 0);
    lv_obj_align(res_title, LV_ALIGN_TOP_LEFT, 6, 6);

    lv_obj_t *res_r = lv_label_create(card_result);
    lv_label_set_text(res_r,"Result");
    lv_obj_set_style_text_color(res_r, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(res_r, &lv_font_montserrat_14, 0);
    lv_obj_align(res_r, LV_ALIGN_TOP_LEFT, 6, 40);

    lv_obj_t *res_val = lv_label_create(card_result);
    lv_label_set_text(res_val, "142.8");
    lv_obj_set_style_text_color(res_val, COLOR_NUM, 0);
    lv_obj_set_style_text_font(res_val, &lv_font_montserrat_32, 0);
    lv_obj_align(res_val, LV_ALIGN_TOP_LEFT, 6, 65);

    lv_obj_t *res_unit = lv_label_create(card_result);
    lv_label_set_text(res_unit, "mg/dl");
    lv_obj_set_style_text_color(res_unit, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(res_unit, &lv_font_montserrat_16, 0);
    lv_obj_align(res_unit, LV_ALIGN_TOP_LEFT, 6, 110);

    lv_obj_t *ref_lbl = lv_label_create(card_result);
    lv_label_set_text(ref_lbl, "Reference Range");
    lv_obj_set_style_text_color(ref_lbl, COLOR_GRAY, 0);
    lv_obj_set_style_text_font(ref_lbl, &lv_font_montserrat_12, 0);
    lv_obj_align(ref_lbl, LV_ALIGN_TOP_LEFT, 6, 160);

    lv_obj_t *ref_val = lv_label_create(card_result);
    lv_label_set_text(ref_val, "70-110 mg/dl");
    lv_obj_set_style_text_color(ref_val, COLOR_TEXT, 0);
    lv_obj_set_style_text_font(ref_val, &lv_font_montserrat_16, 0);
    lv_obj_align(ref_val, LV_ALIGN_TOP_LEFT, 6, 190);
    


    /* Above range indicator */
    lv_obj_t *range_badge = create_badge(card_result, LV_SYMBOL_PLAY" Above Range", COLOR_ORANGE);
    lv_obj_set_style_text_color(range_badge, COLOR_ORANGE,0);
    lv_obj_align(range_badge, LV_ALIGN_BOTTOM_LEFT, 6, -12);

    /* ------------- BOTTOM ACTION BUTTONS ------------ */
    lv_obj_t *btn_exit = lv_btn_create(scr);
    lv_obj_set_size(btn_exit, 120, 44);
    lv_obj_set_style_radius(btn_exit, 8, 0);
    lv_obj_set_style_bg_color(btn_exit, COLOR_BUTTON_RED, LV_STATE_DEFAULT);
    lv_obj_align(btn_exit, LV_ALIGN_BOTTOM_MID, -50, -60);

    lv_obj_t *lbl_exit = lv_label_create(btn_exit);
    lv_label_set_text(lbl_exit,LV_SYMBOL_CLOSE " Exit");
    lv_obj_set_style_text_color(lbl_exit, lv_color_white(), 0);
    lv_obj_center(lbl_exit);

    lv_obj_t *btn_back = lv_btn_create(scr);
    lv_obj_set_size(btn_back, 120, 44);
    lv_obj_set_style_radius(btn_back, 8, 0);
    lv_obj_set_style_bg_color(btn_back, COLOR_BUTTON_GRAY, LV_STATE_DEFAULT);
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_MID, 90, -60);
    
    lv_obj_t *lbl_back = lv_label_create(btn_back);
    lv_label_set_text(lbl_back, LV_SYMBOL_PREV " Back");
    lv_obj_set_style_text_color(lbl_back, COLOR_TEXT, 0);
    lv_obj_center(lbl_back);

    lv_obj_t *btn_print = lv_btn_create(scr);
    lv_obj_set_size(btn_print, 120, 44);
    lv_obj_set_style_radius(btn_print, 8, 0);
    lv_obj_set_style_bg_color(btn_print, COLOR_BUTTON_BLUE, LV_STATE_DEFAULT);
    lv_obj_align(btn_print, LV_ALIGN_BOTTOM_MID, 230, -60);

    
    lv_obj_t *icon = lv_label_create(btn_print);
    lv_label_set_text(icon, "\uf02f");
    lv_obj_set_style_text_font(icon, &fa_24, 0);
    lv_obj_align(icon, LV_ALIGN_LEFT_MID, -2, 0);

    lv_obj_t *lbl_print = lv_label_create(btn_print);
    lv_label_set_text(lbl_print, " Print");
    lv_obj_set_style_text_color(lbl_print, lv_color_white(), 0);
    lv_obj_center(lbl_print);


    lv_obj_t *bottom_bar = create_bottom_bar(scr);

    lv_obj_t *footer_label = lv_label_create(bottom_bar);
    lv_label_set_text(footer_label,
        LV_SYMBOL_PLAY" System Ready     "
        "Temp: 37.2°C      "
        LV_SYMBOL_WIFI" Connected         "
        "Last Cal: 2h ago     "
        "User: Dr. Smith     "
        "Session: 3h 24m"
    );

    lv_obj_set_style_text_color(footer_label, lv_color_hex(0x9CA3AF), 0);
    lv_obj_set_style_text_font(footer_label, &lv_font_montserrat_12, 0);
    lv_obj_align(footer_label, LV_ALIGN_TOP_MID, 0, 0);

        /* sharp line*/
    static lv_point_precise_t line_points3[] = {
        {0,0},
        {780,0}
    };
    lv_obj_t *line3 = lv_line_create(scr);
    lv_line_set_points(line3, line_points3, 2);
    lv_obj_set_style_line_width(line3, 1, LV_PART_MAIN);
    lv_obj_set_style_line_color(line3, lv_color_hex(0x324556), LV_PART_MAIN);
    /* Position */
    lv_obj_align(line3, LV_ALIGN_BOTTOM_MID, 110 , -40);


}
