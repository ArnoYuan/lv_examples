/**
 * @file lv_test_theme_2.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_theme_2.h"

#if USE_LV_TESTS
#include "lvgl/lv_misc/lv_math.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void header_create(void);
static void sb_create(void);
static void content_create(void);
static lv_res_t theme_select_action(lv_obj_t * roller);
static lv_res_t hue_select_action(lv_obj_t * roller);
static void init_all_themes(uint16_t hue);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * header;
static lv_obj_t * sb;
static lv_obj_t * content;
static lv_theme_t * th_act;

static const char * th_options =
{

#if USE_LV_THEME_NIGHT
        "Night"
#endif

#if USE_LV_THEME_MATERIAL
        "\nMaterial"
#endif

#if USE_LV_THEME_ALIEN
        "\nAlien"
#endif

#if USE_LV_THEME_ZEN
        "\nZen"
#endif

#if USE_LV_THEME_NEMO
        "\nNemo"
#endif

#if USE_LV_THEME_MONO
        "\nMono"
#endif

#if USE_LV_THEME_DEFAULT
        "\nDefault"
#endif
        ""
};

static lv_theme_t * themes[8];

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Test run time theme change
 */
void lv_test_theme_2(void)
{
    init_all_themes(0);
    th_act = themes[0];
    if(th_act == NULL) {
    	LV_LOG_WARN("lv_test_theme_2: no theme is enabled. Check lv_conf.h");
    	return;
    }


    lv_theme_set_current(th_act);

    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    header_create();
    sb_create();
    content_create();


}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void header_create(void)
{
    header = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_set_width(header, LV_HOR_RES);

    lv_obj_t * sym = lv_label_create(header, NULL);
    lv_label_set_text(sym, SYMBOL_GPS SYMBOL_WIFI SYMBOL_BLUETOOTH SYMBOL_VOLUME_MAX);
    lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI/10, 0);

    lv_obj_t * clock = lv_label_create(header, NULL);
    lv_label_set_text(clock, "14:21");
    lv_obj_align(clock, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI/10, 0);

    lv_cont_set_fit(header, false, true);   /*Let the height set automatically*/
    lv_obj_set_pos(header, 0, 0);

}

static void sb_create(void)
{
    sb = lv_page_create(lv_scr_act(), NULL);
    lv_page_set_scrl_layout(sb, LV_LAYOUT_COL_M);
    lv_page_set_style(sb, LV_PAGE_STYLE_BG, &lv_style_transp_tight);
    lv_page_set_style(sb, LV_PAGE_STYLE_SCRL, &lv_style_transp);

    lv_obj_t * th_label = lv_label_create(sb, NULL);
    lv_label_set_text(th_label, "Theme");

    lv_obj_t * th_roller = lv_roller_create(sb, NULL);
    lv_roller_set_options(th_roller, th_options);
    lv_roller_set_action(th_roller, theme_select_action);

    lv_obj_t * hue_label = lv_label_create(sb, NULL);
    lv_label_set_text(hue_label, "\nColor");

    lv_obj_t * hue_roller = lv_roller_create(sb, NULL);
    lv_roller_set_options(hue_roller, "0\n30\n60\n90\n120\n150\n180\n210\n240\n270\n300\n330");
    lv_roller_set_action(hue_roller, hue_select_action);

#if LV_HOR_RES > LV_VER_RES
    lv_obj_set_height(sb, LV_VER_RES - lv_obj_get_height(header));
    lv_cont_set_fit(sb, true, false);
    lv_page_set_scrl_fit(sb, true, false);
    lv_obj_align(sb, header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_page_set_sb_mode(sb, LV_SB_MODE_DRAG);
#else
    lv_obj_set_size(sb, LV_HOR_RES, LV_VER_RES / 2 - lv_obj_get_height(header));
    lv_obj_align(sb, header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_page_set_sb_mode(sb, LV_SB_MODE_AUTO);
#endif
}

static void content_create(void)
{
    content = lv_page_create(lv_scr_act(), NULL);

#if LV_HOR_RES > LV_VER_RES
    lv_obj_set_size(content, LV_HOR_RES - lv_obj_get_width(sb), LV_VER_RES - lv_obj_get_height(header));
    lv_obj_set_pos(content,  lv_obj_get_width(sb), lv_obj_get_height(header));
#else
    lv_obj_set_size(content, LV_HOR_RES , LV_VER_RES / 2);
    lv_obj_set_pos(content,  0, LV_VER_RES / 2);
#endif

    lv_page_set_scrl_layout(content, LV_LAYOUT_PRETTY);

    lv_coord_t max_w = lv_page_get_fit_width(content);


    /*Button*/
    lv_obj_t * btn = lv_btn_create(content, NULL);
    lv_btn_set_ink_in_time(btn, 200);
    lv_btn_set_ink_wait_time(btn, 100);
    lv_btn_set_ink_out_time(btn, 500);
    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Button");

    /*Switch*/
    lv_sw_create(content, NULL);

    /*Check box*/
    lv_cb_create(content, NULL);

    /*Bar*/
    lv_obj_t * bar = lv_bar_create(content, NULL);
    lv_obj_set_width(bar, LV_MATH_MIN(max_w, 3 * LV_DPI / 2));
    lv_anim_t a;
    a.var = bar;
    a.start = 0;
    a.end = 100;
    a.fp = (lv_anim_fp_t)lv_bar_set_value;
    a.path = lv_anim_path_linear;
    a.end_cb = NULL;
    a.act_time = 0;
    a.time = 1000;
    a.playback = 1;
    a.playback_pause = 100;
    a.repeat = 1;
    a.repeat_pause = 100;
    lv_anim_create(&a);

    /*Slider*/
    lv_obj_t * slider = lv_slider_create(content, NULL);
    lv_obj_set_width(slider, LV_MATH_MIN(max_w, 3 * LV_DPI / 2));
    lv_slider_set_value(slider, 30);

    /*Roller*/
    static const char * days = "Monday\nTuesday\nWednesday\nThursday\nFriday\nSaturday\nSunday";
    lv_obj_t * roller = lv_roller_create(content, NULL);
    lv_roller_set_options(roller, days);

    /*Drop down list*/
    static const char * nums = "One\nTwo\nThree\nFour";
    lv_obj_t * ddlist = lv_ddlist_create(content, NULL);
    lv_ddlist_set_options(ddlist, nums);

    /*Line meter*/
    lv_obj_t * lmeter = lv_lmeter_create(content, NULL);

    a.var = lmeter;
    a.start = 0;
    a.end = 100;
    a.fp = (lv_anim_fp_t)lv_lmeter_set_value;
    a.path = lv_anim_path_linear;
    a.end_cb = NULL;
    a.act_time = 0;
    a.time = 1000;
    a.playback = 1;
    a.playback_pause = 100;
    a.repeat = 1;
    a.repeat_pause = 100;
    lv_anim_create(&a);

    /*Gauge*/
    lv_obj_t * gauge = lv_gauge_create(content, NULL);
    lv_gauge_set_value(gauge, 0, 47);
    lv_obj_set_size(gauge, LV_MATH_MIN(max_w, LV_DPI * 3 / 2), LV_MATH_MIN(max_w, LV_DPI * 3 / 2));

    /*Test area*/
    lv_obj_t * ta = lv_ta_create(content, NULL);
    lv_obj_set_width(ta, LV_MATH_MIN(max_w, LV_DPI * 3 / 2));
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "Type...");

    /*Keyboard*/
    lv_obj_t * kb = lv_kb_create(content, NULL);
    lv_obj_set_width(kb, LV_MATH_MIN(max_w, LV_DPI * 3));
    lv_kb_set_ta(kb, ta);

    lv_obj_t * mbox = lv_mbox_create(lv_scr_act(), NULL);
    lv_obj_set_drag(mbox, true);
    lv_mbox_set_text(mbox, "Choose a theme and a color on the left!");

    static const char * mbox_btns[] = {"Ok", ""};
    lv_mbox_add_btns(mbox, mbox_btns, NULL);

    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

}

static lv_res_t theme_select_action(lv_obj_t * roller)
{
    uint16_t opt = lv_roller_get_selected(roller);
    th_act = themes[opt];
    lv_theme_set_current(th_act);

    lv_obj_align(header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_align(sb, header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

#if LV_HOR_RES > LV_VER_RES
    lv_obj_set_size(content, LV_HOR_RES - lv_obj_get_width(sb), LV_VER_RES - lv_obj_get_height(header));
    lv_obj_set_pos(content,  lv_obj_get_width(sb), lv_obj_get_height(header));
#else
    lv_obj_set_size(content, LV_HOR_RES , LV_VER_RES / 2);
    lv_obj_set_pos(content,  0, LV_VER_RES / 2);
#endif

    lv_page_focus(sb, roller, 200);

    return LV_RES_OK;
}


static lv_res_t hue_select_action(lv_obj_t * roller)
{
    uint16_t hue = lv_roller_get_selected(roller) * 30;

    init_all_themes(hue);

    lv_theme_set_current(th_act);

    lv_page_focus(sb, roller, 200);

    return LV_RES_OK;
}


static void init_all_themes(uint16_t hue)
{
#if USE_LV_THEME_NIGHT
    themes[0] = lv_theme_night_init(hue, NULL);
#endif

#if USE_LV_THEME_MATERIAL
    themes[1] = lv_theme_material_init(hue, NULL);
#endif

#if USE_LV_THEME_ALIEN
    themes[2] = lv_theme_alien_init(hue, NULL);
#endif

#if USE_LV_THEME_ZEN
    themes[3] = lv_theme_zen_init(hue, NULL);
#endif

#if USE_LV_THEME_NEMO
    themes[4] = lv_theme_nemo_init(hue, NULL);
#endif

#if USE_LV_THEME_MONO
    themes[5] = lv_theme_mono_init(hue, NULL);
#endif

#if USE_LV_THEME_DEFAULT
    themes[6] = lv_theme_default_init(hue, NULL);
#endif
}

#endif /*USE_LV_TESTS*/
