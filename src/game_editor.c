#include <pebble.h>
#include "game_editor.h"
#include "utils.h"
  
static int s_current_pin = 0;
static PropertyAnimation *s_property_animation;
  
static GBitmap *s_indicator_bitmap;
static GBitmap *s_background_bitmap;
#ifdef PBL_PLATFORM_APLITE
static GBitmap *s_pin_enabled_bitmap_black, *s_pin_enabled_bitmap_white;
static GBitmap *s_pin_disabled_bitmap_black, *s_pin_disabled_bitmap_white;
#elif PBL_PLATFORM_BASALT
static GBitmap *s_pin_enabled, *s_pin_disabled;
#endif

// game values
static char* bowler_name;
static char* league_name;
static char* series_name;
static char* game_title;
static int s_current_game = 0;
static int s_current_frame = 0;
static int s_current_ball = 0;
static bool s_pin_state[150];
static int s_game_score[10];

static char* frame_number;
static char* ball_number;
static char* frame_score_1;
static char* frame_score_2;
static char* frame_score_3;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_14;
static TextLayer *s_textlayer_gamenum;
static TextLayer *s_textlayer_league;
static Layer *s_layer_frame_bg;
static TextLayer *s_textlayer_f1_score;
static TextLayer *s_textlayer_f2_score;
static TextLayer *s_textlayer_f3_score;
static TextLayer *s_textlayer_f1_b1;
static TextLayer *s_textlayer_f1_b2;
static TextLayer *s_textlayer_f1_b3;
static TextLayer *s_textlayer_f2_b1;
static TextLayer *s_textlayer_f2_b2;
static TextLayer *s_textlayer_f2_b3;
static TextLayer *s_textlayer_f3_b1;
static TextLayer *s_textlayer_f3_b2;
static TextLayer *s_textlayer_f3_b3;
static TextLayer *s_textlayer_frame_label;
static TextLayer *s_textlayer_frame;
static TextLayer *s_textlayer_ball_label;
static TextLayer *s_textlayer_ball;
static BitmapLayer *s_bitmap_pin_0;
static BitmapLayer *s_bitmap_pin_1;
static BitmapLayer *s_bitmap_pin_2;
static BitmapLayer *s_bitmap_pin_3;
static BitmapLayer *s_bitmap_pin_4;
static BitmapLayer *s_bitmap_indicator;
static BitmapLayer *s_bitmap_background;

static GPath *s_text_background_path_1 = NULL;
static GPath *s_text_background_path_2 = NULL;
static GPath *s_text_background_path_3 = NULL;
static GPath *s_text_background_path_4 = NULL;

static const GPathInfo BOLT_PATH_INFO_1 = {
  .num_points = 26,
  .points = (GPoint []) {{0, 63},{16, 63},{16, 45},{16, 63},{32, 63},{32, 45},{32, 63},{47, 63},{47, 45},{47, 63},{64, 63},
                        {64, 45},{64, 63},{80, 63},{80, 45},{80, 63},{96, 63},{96, 45},{96, 63},{112, 63},{112, 45},{112, 63},
                        {128, 63},{128, 45},{128, 63},{143, 63}}
};

static const GPathInfo BOLT_PATH_INFO_2 = {
  .num_points = 2,
  .points = (GPoint []) {{47, 45},{47,78}}
};

static const GPathInfo BOLT_PATH_INFO_3 = {
  .num_points = 2,
  .points = (GPoint []) {{96, 45},{96,78}}
};

static const GPathInfo BOLT_PATH_INFO_4 = {
  .num_points = 5,
  .points = (GPoint []) {{0, 45},{0,78},{143,78},{143,45},{0,45}}
};

void setup_paths(void) {
  s_text_background_path_1 = gpath_create(&BOLT_PATH_INFO_1);
  s_text_background_path_2 = gpath_create(&BOLT_PATH_INFO_2);
  s_text_background_path_3 = gpath_create(&BOLT_PATH_INFO_3);
  s_text_background_path_4 = gpath_create(&BOLT_PATH_INFO_4);
}

static void text_bg_draw(Layer *my_layer, GContext* ctx) {
  // Stroke the path:
  graphics_context_set_stroke_color(ctx, GColorBlack);
  gpath_draw_outline(ctx, s_text_background_path_1);
  gpath_draw_outline(ctx, s_text_background_path_2);
  gpath_draw_outline(ctx, s_text_background_path_3);
  gpath_draw_outline(ctx, s_text_background_path_4);
}

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
    
  setup_paths();
    
  s_indicator_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_INDICATOR);
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
  #ifdef PBL_PLATFORM_APLITE
    s_pin_enabled_bitmap_black = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PIN_ENABLED);
    s_pin_enabled_bitmap_white = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PIN_ENABLED);
    s_pin_disabled_bitmap_black = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PIN_DISABLED);
    s_pin_disabled_bitmap_white = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PIN_DISABLED);
  #elif PBL_PLATFORM_BASALT
    s_pin_enabled = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PIN_ENABLED);
    s_pin_disabled = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PIN_DISABLED);
  #endif
    
  s_bitmap_background = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmap_background, s_background_bitmap);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_background);
  
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_textlayer_gamenum
  s_textlayer_gamenum = text_layer_create(GRect(5, 5, 100, 20));
  text_layer_set_text(s_textlayer_gamenum, "Game #");
  text_layer_set_font(s_textlayer_gamenum, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_gamenum);
  
  // s_textlayer_league
  s_textlayer_league = text_layer_create(GRect(5, 25, 100, 20));
  text_layer_set_text(s_textlayer_league, league_name);
  text_layer_set_font(s_textlayer_league, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_league);
  
  // s_textlayer_f1_score
  s_textlayer_f1_score = text_layer_create(GRect(0, 63, 47, 15));
  text_layer_set_text(s_textlayer_f1_score, "0");
  text_layer_set_text_alignment(s_textlayer_f1_score, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f1_score, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f1_score);
  
  // s_textlayer_f2_score
  s_textlayer_f2_score = text_layer_create(GRect(48, 63, 48, 15));
  text_layer_set_text(s_textlayer_f2_score, "0");
  text_layer_set_text_alignment(s_textlayer_f2_score, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f2_score, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f2_score);
  
  // s_textlayer_f3_score
  s_textlayer_f3_score = text_layer_create(GRect(97, 63, 47, 15));
  text_layer_set_text(s_textlayer_f3_score, "0");
  text_layer_set_text_alignment(s_textlayer_f3_score, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f3_score, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f3_score);
  
  // s_textlayer_f1_b1
  s_textlayer_f1_b1 = text_layer_create(GRect(0, 45, 15, 15));
  text_layer_set_text(s_textlayer_f1_b1, "-");
  text_layer_set_text_alignment(s_textlayer_f1_b1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f1_b1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f1_b1);
  
  // s_textlayer_f1_b2
  s_textlayer_f1_b2 = text_layer_create(GRect(16, 45, 15, 15));
  text_layer_set_text(s_textlayer_f1_b2, "-");
  text_layer_set_text_alignment(s_textlayer_f1_b2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f1_b2, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f1_b2);
  
  // s_textlayer_f1_b3
  s_textlayer_f1_b3 = text_layer_create(GRect(32, 45, 15, 15));
  text_layer_set_text(s_textlayer_f1_b3, "-");
  text_layer_set_text_alignment(s_textlayer_f1_b3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f1_b3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f1_b3);
  
  // s_textlayer_f2_b1
  s_textlayer_f2_b1 = text_layer_create(GRect(48, 45, 15, 15));
  text_layer_set_text(s_textlayer_f2_b1, "-");
  text_layer_set_text_alignment(s_textlayer_f2_b1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f2_b1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f2_b1);
  
  // s_textlayer_f2_b2
  s_textlayer_f2_b2 = text_layer_create(GRect(64, 45, 15, 15));
  text_layer_set_text(s_textlayer_f2_b2, "-");
  text_layer_set_text_alignment(s_textlayer_f2_b2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f2_b2, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f2_b2);
  
  // s_textlayer_f2_b3
  s_textlayer_f2_b3 = text_layer_create(GRect(80, 45, 15, 15));
  text_layer_set_text(s_textlayer_f2_b3, "-");
  text_layer_set_text_alignment(s_textlayer_f2_b3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f2_b3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f2_b3);
  
  // s_textlayer_f3_b1
  s_textlayer_f3_b1 = text_layer_create(GRect(96, 45, 15, 15));
  text_layer_set_text(s_textlayer_f3_b1, "-");
  text_layer_set_text_alignment(s_textlayer_f3_b1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f3_b1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f3_b1);
  
  // s_textlayer_f3_b2
  s_textlayer_f3_b2 = text_layer_create(GRect(112, 45, 15, 15));
  text_layer_set_text(s_textlayer_f3_b2, "-");
  text_layer_set_text_alignment(s_textlayer_f3_b2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f3_b2, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f3_b2);
  
  // s_textlayer_f3_b3
  s_textlayer_f3_b3 = text_layer_create(GRect(128, 45, 15, 15));
  text_layer_set_text(s_textlayer_f3_b3, "-");
  text_layer_set_text_alignment(s_textlayer_f3_b3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_f3_b3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_f3_b3);
  
  s_textlayer_frame_label = text_layer_create(GRect(79, 5, 30, 15));
  text_layer_set_text(s_textlayer_frame_label, "F:");
  text_layer_set_text_alignment(s_textlayer_frame_label, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_frame_label, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_frame_label);
  
  s_textlayer_frame = text_layer_create(GRect(109, 5, 30, 15));
  text_layer_set_text(s_textlayer_frame, "1");
  text_layer_set_text_alignment(s_textlayer_frame, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_frame, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_frame);
  
  s_textlayer_ball_label = text_layer_create(GRect(79, 20, 30, 15));
  text_layer_set_text(s_textlayer_ball_label, "B:");
  text_layer_set_text_alignment(s_textlayer_ball_label, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_ball_label, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_ball_label);
  
  s_textlayer_ball = text_layer_create(GRect(109, 20, 30, 15));
  text_layer_set_text(s_textlayer_ball, "1");
  text_layer_set_text_alignment(s_textlayer_ball, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_ball, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_ball);
  
  // s_bitmap_pin_0
  s_bitmap_pin_0 = bitmap_layer_create(GRect(0, 92, 28, 60));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_pin_0);
  
  // s_bitmap_pin_1
  s_bitmap_pin_1 = bitmap_layer_create(GRect(29, 92, 28, 60));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_pin_1);
  
  // s_bitmap_pin_2
  s_bitmap_pin_2 = bitmap_layer_create(GRect(58, 92, 28, 60));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_pin_2);
  
  // s_bitmap_pin_3
  s_bitmap_pin_3 = bitmap_layer_create(GRect(87, 92, 28, 60));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_pin_3);
  
  // s_bitmap_pin_4
  s_bitmap_pin_4 = bitmap_layer_create(GRect(116, 92, 28, 60));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_pin_4);
  
  // s_bitmap_indicator
  s_bitmap_indicator = bitmap_layer_create(GRect(0, 153, 28, 15));
  bitmap_layer_set_bitmap(s_bitmap_indicator, s_indicator_bitmap);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_indicator);
  
  // s_layer_frame_bg
  s_layer_frame_bg = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_layer_frame_bg, text_bg_draw);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_layer_frame_bg);
  
  #ifdef PBL_PLATFORM_APLITE
    bitmap_layer_set_bitmap(s_bitmap_pin_0, s_pin_enabled_bitmap_white);
    bitmap_layer_set_bitmap(s_bitmap_pin_1, s_pin_enabled_bitmap_white);
    bitmap_layer_set_bitmap(s_bitmap_pin_2, s_pin_enabled_bitmap_white);
    bitmap_layer_set_bitmap(s_bitmap_pin_3, s_pin_enabled_bitmap_white);
    bitmap_layer_set_bitmap(s_bitmap_pin_4, s_pin_enabled_bitmap_white);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_0, GCompOpAnd);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_1, GCompOpAnd);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_2, GCompOpAnd);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_3, GCompOpAnd);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_4, GCompOpAnd);
    bitmap_layer_set_compositing_mode(s_bitmap_indicator, GCompOpAnd);
  #elif PBL_PLATFORM_BASALT
    bitmap_layer_set_bitmap(s_bitmap_pin_0, s_pin_enabled);
    bitmap_layer_set_bitmap(s_bitmap_pin_1, s_pin_enabled);
    bitmap_layer_set_bitmap(s_bitmap_pin_2, s_pin_enabled);
    bitmap_layer_set_bitmap(s_bitmap_pin_3, s_pin_enabled);
    bitmap_layer_set_bitmap(s_bitmap_pin_4, s_pin_enabled);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_0, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_1, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_2, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_3, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_bitmap_pin_4, GCompOpSet);
    bitmap_layer_set_compositing_mode(s_bitmap_indicator, GCompOpSet);
  #endif
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_gamenum);
  text_layer_destroy(s_textlayer_league);
  layer_destroy(s_layer_frame_bg);
  text_layer_destroy(s_textlayer_f1_score);
  text_layer_destroy(s_textlayer_f2_score);
  text_layer_destroy(s_textlayer_f3_score);
  text_layer_destroy(s_textlayer_f1_b1);
  text_layer_destroy(s_textlayer_f1_b2);
  text_layer_destroy(s_textlayer_f1_b3);
  text_layer_destroy(s_textlayer_f2_b1);
  text_layer_destroy(s_textlayer_f2_b2);
  text_layer_destroy(s_textlayer_f2_b3);
  text_layer_destroy(s_textlayer_f3_b1);
  text_layer_destroy(s_textlayer_f3_b2);
  text_layer_destroy(s_textlayer_f3_b3);
  text_layer_destroy(s_textlayer_frame);
  text_layer_destroy(s_textlayer_frame_label);
  text_layer_destroy(s_textlayer_ball);
  text_layer_destroy(s_textlayer_ball_label);
  bitmap_layer_destroy(s_bitmap_pin_0);
  bitmap_layer_destroy(s_bitmap_pin_1);
  bitmap_layer_destroy(s_bitmap_pin_2);
  bitmap_layer_destroy(s_bitmap_pin_3);
  bitmap_layer_destroy(s_bitmap_pin_4);
  bitmap_layer_destroy(s_bitmap_indicator);
  bitmap_layer_destroy(s_bitmap_background);
  
  gbitmap_destroy(s_indicator_bitmap);
  gbitmap_destroy(s_background_bitmap);
  #ifdef PBL_PLATFORM_APLITE
    gbitmap_destroy(s_pin_enabled_bitmap_black);
    gbitmap_destroy(s_pin_enabled_bitmap_white);
    gbitmap_destroy(s_pin_disabled_bitmap_black);
    gbitmap_destroy(s_pin_disabled_bitmap_white);
  #elif PBL_PLATFORM_BASALT
    gbitmap_destroy(s_pin_enabled);
    gbitmap_destroy(s_pin_disabled);
  #endif
}
// END AUTO-GENERATED UI CODE

static bool is_pin_knocked(int frame, int ball, int pin) {
  return s_pin_state[frame * 15 + ball * 5 + pin];
}

static void set_pin_knocked(int frame, int ball, int pin, bool knocked) {
  s_pin_state[frame * 15 + ball * 5 + pin] = knocked;
}

static void calculate_score() {
  //Calculates and keeps running total of scores of each frame
  int frame_score[10] = {0};
  for (int f = 9; f >= 0; f--) {
    bool is_valid = true;
    if (f == 9) {
      for (int b = 2; b >= 0; b--) {
        switch (b) {
          case 2:
            frame_score[f] += get_value_of_frame(f, b, s_pin_state);
            break;
          case 1:
          case 0:
            if (is_frame_strike(f, b, s_pin_state)) {
              frame_score[f] += get_value_of_frame(f, b, s_pin_state);
            }
            break;
        }
      }
    } else {
      for (int b = 0; b < 3 && is_valid; b++) {
        if (b < 2 && is_frame_strike(f, b, s_pin_state)) {
          frame_score[f] += get_value_of_frame(f, b, s_pin_state);
          frame_score[f] += get_value_of_frame(f + 1, 0, s_pin_state);
          if (b == 0) {
            if (f == 8) {
              if (frame_score[f] == 30) {
                frame_score[f] += get_value_of_frame(f + 1, 1, s_pin_state);
              } else {
                frame_score[f] += get_value_of_frame_diff(f + 1, 0, f + 1, 1, s_pin_state);
              }
            } else if (frame_score[f] < 30) {
              frame_score[f] += get_value_of_frame_diff(f + 1, 0, f + 1, 1, s_pin_state);
            } else {
              frame_score[f] += get_value_of_frame(f + 2, 0, s_pin_state);
            }
          }
          is_valid = false;
        } else if (b == 2) {
          frame_score[f] += get_value_of_frame(f, b, s_pin_state);
        }
      }
    }
  }
  
  for (int i = 0; i < 10; i++) {
    if (i > 0) {
      s_game_score[i] = s_game_score[i - 1] + frame_score[i];
    } else {
      s_game_score[i] = frame_score[i];
    }
  }
}

static void update_all_textboxes() {
  int first_frame, second_frame, third_frame;
  calculate_score();
  
  if (s_current_frame < 3) {
    first_frame = 0;
    second_frame = 1;
    third_frame = 2;
  } else {
    first_frame = s_current_frame - 2;
    second_frame = s_current_frame - 1;
    third_frame = s_current_frame;
  }
  
  if (ball_number) {
    free(ball_number);
    ball_number = NULL;
  }
  if (frame_number) {
    free(frame_number);
    frame_number = NULL;
  }
  if (frame_score_1) {
    free(frame_score_1);
    frame_score_1 = NULL;
  }
  if (frame_score_2) {
    free(frame_score_2);
    frame_score_2 = NULL;
  }
  if (frame_score_3) {
    free(frame_score_3);
    frame_score_3 = NULL;
  }
  ball_number = (char*) malloc(2);
  frame_number = (char*) malloc(3);
  frame_score_1 = (char*) malloc(4);
  frame_score_2 = (char*) malloc(4);
  frame_score_3 = (char*) malloc(4);
  snprintf(ball_number, sizeof(ball_number), "%d", (s_current_ball + 1));
  snprintf(frame_number, sizeof(frame_number), "%d", (s_current_frame + 1));
  snprintf(frame_score_1, sizeof(frame_score_1), "%d", s_game_score[first_frame]);
  snprintf(frame_score_2, sizeof(frame_score_2), "%d", s_game_score[second_frame]);
  snprintf(frame_score_3, sizeof(frame_score_3), "%d", s_game_score[third_frame]);
  text_layer_set_text(s_textlayer_f1_score, frame_score_1);
  text_layer_set_text(s_textlayer_f2_score, frame_score_2);
  text_layer_set_text(s_textlayer_f3_score, frame_score_3);
  text_layer_set_text(s_textlayer_frame, frame_number);
  text_layer_set_text(s_textlayer_ball, ball_number);
}

static void on_animation_stopped(Animation *anim, bool finished, void *context){
  //Free the memory used by the Animation
  property_animation_destroy((PropertyAnimation*) anim);
}

static void set_game(int new_game) {
  s_current_game = new_game + 1;

  if (game_title) {
    free(game_title);
    game_title = NULL;
  }
  game_title = (char*) malloc(sizeof(char) * 8 + 1);
  snprintf(game_title, 9, "%s%d", "Game #", s_current_game);
  text_layer_set_text(s_textlayer_gamenum, game_title);
  s_current_game--;
}

static void update_pin_status(BitmapLayer *pin_bitmap, int frame, int ball, int pin, bool knocked) {
  /*if (!is_pin_knocked(frame, ball, pin)) {
    for (int i = s_current_ball; i < 3; i++) {
      set_pin_knocked(frame, i, pin, true);
    }
  } else {
    for (int i = s_current_ball; i < 3; i++) {
      set_pin_knocked(frame, i, pin, false);
    }
  }*/
  /*
  final boolean isPinKnockedOver = mPinState[mCurrentFrame][mCurrentBall][pinToSet];
                final boolean allPinsKnockedOver;
                if (!isPinKnockedOver)
                {
                    for (int i = mCurrentBall; i < 3; i++)
                        mPinState[mCurrentFrame][i][pinToSet] = true;

                    if (Arrays.equals(mPinState[mCurrentFrame][mCurrentBall],
                            Constants.FRAME_PINS_DOWN))
                    {
                        for (int i = mCurrentBall + 1; i < 3; i++)
                            mFouls[mCurrentFrame][i] = false;

                        if (mCurrentFrame == Constants.LAST_FRAME)
                        {
                            if (mCurrentBall < 2)
                            {
                                for (int j = mCurrentBall + 1; j < 3; j++)
                                {
                                    for (int i = 0; i < 5; i++)
                                        mPinState[mCurrentFrame][j][i] = false;
                                }
                            }
                        }
                        allPinsKnockedOver = true;
                    }
                    else
                        allPinsKnockedOver = false;
                }
                else
                {
                    allPinsKnockedOver = false;
                    for (int i = mCurrentBall; i < 3; i++)
                        mPinState[mCurrentFrame][i][pinToSet] = false;

                    if (mCurrentFrame == Constants.LAST_FRAME && mCurrentBall == 1)
                        System.arraycopy(
                                mPinState[mCurrentFrame][1],
                                0,
                                mPinState[mCurrentFrame][2],
                                0,
                                mPinState[mCurrentFrame][1].length);
                }
  */
  set_pin_knocked(frame, ball, pin, knocked);
  if (knocked) {
    #ifdef PBL_PLATFORM_APLITE
      bitmap_layer_set_bitmap(pin_bitmap, s_pin_disabled_bitmap_white);
    #elif PBL_PLATFORM_BASALT
      bitmap_layer_set_bitmap(pin_bitmap, s_pin_disabled);
    #endif
  } else {
    #ifdef PBL_PLATFORM_APLITE
      bitmap_layer_set_bitmap(pin_bitmap, s_pin_enabled_bitmap_white);
    #elif PBL_PLATFORM_BASALT
      bitmap_layer_set_bitmap(pin_bitmap, s_pin_enabled);
    #endif
  }
}

static void update_indicator_position(void) {
  Layer *root_indicator_layer = bitmap_layer_get_layer(s_bitmap_indicator);
  GRect to_frame = GRect(0, 0, 0, 0);
  GRect from_frame = layer_get_frame(root_indicator_layer);
  switch (s_current_pin) {
    case 0:
      to_frame = GRect(0, 153, 28, 15);
      break;
    case 1:
      to_frame = GRect(29, 153, 28, 15);
      break;
    case 2:
      to_frame = GRect(58, 153, 28, 15);
      break;
    case 3:
      to_frame = GRect(87, 153, 28, 15);
      break;
    case 4:
      to_frame = GRect(116, 153, 28, 15);
      break;
  }
  
  AnimationHandlers handlers = {
    //The reference to the stopped handler is the only one in the array
    .stopped = (AnimationStoppedHandler) on_animation_stopped
  };
  
  s_property_animation = property_animation_create_layer_frame(root_indicator_layer, &from_frame, &to_frame);
  animation_set_duration((Animation*) s_property_animation, 400);
  animation_set_handlers((Animation*) s_property_animation, handlers, NULL);
  animation_schedule((Animation*) s_property_animation);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (s_current_pin == 0)
    s_current_pin = 4;
  else
    s_current_pin--;
  update_indicator_position();
}

static void up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  // does nothing
}

static void up_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  if (s_current_ball == 0) {
    if (s_current_frame == 0)
      return;
    else {
      s_current_frame--;
      s_current_ball = 2;
    }
  } else {
    s_current_ball--;
  }
  
  s_current_pin = 0;
  update_indicator_position();
  update_pin_status(s_bitmap_pin_0, s_current_frame, s_current_ball, 0, is_pin_knocked(s_current_frame, s_current_ball, 0));
  update_pin_status(s_bitmap_pin_1, s_current_frame, s_current_ball, 1, is_pin_knocked(s_current_frame, s_current_ball, 1));
  update_pin_status(s_bitmap_pin_2, s_current_frame, s_current_ball, 2, is_pin_knocked(s_current_frame, s_current_ball, 2));
  update_pin_status(s_bitmap_pin_3, s_current_frame, s_current_ball, 3, is_pin_knocked(s_current_frame, s_current_ball, 3));
  update_pin_status(s_bitmap_pin_4, s_current_frame, s_current_ball, 4, is_pin_knocked(s_current_frame, s_current_ball, 4));
  update_all_textboxes();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_current_pin++;
  if (s_current_pin == 5)
    s_current_pin = 0;
  update_indicator_position();
}

static void down_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  // does nothing
}

static void down_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  if (s_current_ball == 2) {
    if (s_current_frame == 9)
      return;
    else {
      s_current_frame++;
      s_current_ball = 0;
    }
  } else {
    s_current_ball++;
  }
  
  s_current_pin = 0;
  update_indicator_position();
  update_pin_status(s_bitmap_pin_0, s_current_frame, s_current_ball, 0, is_pin_knocked(s_current_frame, s_current_ball, 0));
  update_pin_status(s_bitmap_pin_1, s_current_frame, s_current_ball, 1, is_pin_knocked(s_current_frame, s_current_ball, 1));
  update_pin_status(s_bitmap_pin_2, s_current_frame, s_current_ball, 2, is_pin_knocked(s_current_frame, s_current_ball, 2));
  update_pin_status(s_bitmap_pin_3, s_current_frame, s_current_ball, 3, is_pin_knocked(s_current_frame, s_current_ball, 3));
  update_pin_status(s_bitmap_pin_4, s_current_frame, s_current_ball, 4, is_pin_knocked(s_current_frame, s_current_ball, 4));
  update_all_textboxes();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  BitmapLayer *active_pin = NULL;
  
  switch (s_current_pin) {
    case 0:
      active_pin = s_bitmap_pin_0;
      break;
    case 1:
      active_pin = s_bitmap_pin_1;
      break;
    case 2:
      active_pin = s_bitmap_pin_2;
      break;
    case 3:
      active_pin = s_bitmap_pin_3;
      break;
    case 4:
      active_pin = s_bitmap_pin_4;
      break;
  }

  update_pin_status(active_pin, s_current_frame, s_current_ball, s_current_pin, !is_pin_knocked(s_current_frame, s_current_ball, s_current_pin));
  update_all_textboxes();
}

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  // does nothing
}

static void select_long_click_release_handler(ClickRecognizerRef recognizer, void *context) {
  update_pin_status(s_bitmap_pin_0, s_current_frame, s_current_ball, 0x0, true);
  update_pin_status(s_bitmap_pin_1, s_current_frame, s_current_ball, 0x1, true);
  update_pin_status(s_bitmap_pin_2, s_current_frame, s_current_ball, 0x2, true);
  update_pin_status(s_bitmap_pin_3, s_current_frame, s_current_ball, 0x3, true);
  update_pin_status(s_bitmap_pin_4, s_current_frame, s_current_ball, 0x4, true);
  update_all_textboxes();
  
  // TODO: go to next frame
}

static void click_config_provider(void *context) {
  // Register click handlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 700, up_long_click_handler, up_long_click_release_handler);
  window_long_click_subscribe(BUTTON_ID_DOWN, 700, down_long_click_handler, down_long_click_release_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, select_long_click_release_handler);
}

static void handle_window_load(Window* window) {
  set_game(0);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
  
  if (game_title) {
    free(game_title);
    game_title = NULL;
  }
  if (ball_number) {
    free(ball_number);
    ball_number = NULL;
  }
  if (frame_number) {
    free(frame_number);
    frame_number = NULL;
  }
  if (frame_score_1) {
    free(frame_score_1);
    frame_score_1 = NULL;
  }
  if (frame_score_2) {
    free(frame_score_2);
    frame_score_2 = NULL;
  }
  if (frame_score_3) {
    free(frame_score_3);
    frame_score_3 = NULL;
  }
}

void show_game_editor(char* new_bowler_name, char* new_league_name, char* new_series_name) {
  if (strcmp(new_bowler_name, NEW_BOWLER) == 0)
    bowler_name = DEFAULT_BOWLER_NAME;
  else
    bowler_name = new_bowler_name;
  
  if (strcmp(new_league_name, NEW_EVENT) == 0)
    league_name = DEFAULT_EVENT_NAME;
  else
    league_name = new_league_name;
  
  if (strcmp(new_series_name, NEW_SERIES) == 0)
    series_name = DEFAULT_SERIES_NAME;
  else
    series_name = new_series_name;
  
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  update_indicator_position();
  window_set_click_config_provider(s_window, click_config_provider);
  window_stack_push(s_window, true);
}

void hide_game_editor(void) {
  window_stack_remove(s_window, true);
}
