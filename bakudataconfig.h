#ifndef BAKUDATACONFIG_H
#define BAKUDATACONFIG_H

#include "SignalIndicator.h"
#include "track.h"
#include "platform.h"

#include "component_common.h"

//!
//! Data structure for the track component.
//!
typedef struct
{
      int track_id;
      char track_label[32];
      char track_name[32];
      int track_type;
      int track_points[MAX_TRACK_POINTS * 2];
      int label_pos;
      int number_points;
      int display_train;
      int direction;
}BAKU_Track;

typedef struct
{
    int signal_id;
    char signal_label[32];
    char signal_name [32];
    int signal_type;
    int post_x;
    int post_y;
    int label_pos;
    int post_pos;
    int signal_dir;
    bool draw_post;
    bool display_signal;
    int io_type;
}BAKU_Signal;

//!
//! Data structure for the platform component.
//!
typedef struct
{
      int top_platform_id;
      int bottom_platform_id;
      int x_pos;
      int y_pos;
      int length;
      int height;
      char top_plat_label[8];
      char bottom_plat_label[8];
      bool display_border;
      bool disused_state;
      unsigned short type;
}BAKU_Platform;

//!
//! Data structure for the screen label component.
//!
typedef struct
{
    int label_id;
    int x_pos;
    int y_pos;
    int label_font_id;
    char label_name [32];
}BAKU_Screen_Label;

typedef struct
{
    int num_signals;
    BAKU_Signal signal[MAX_SCREEN_SIGNALS];
    int num_tracks;
    BAKU_Track track[MAX_SCREEN_TRACKS];
    int num_platforms;
    BAKU_Platform platform[MAX_SCREEN_PLATFORMS];
    int num_labels;
    BAKU_Screen_Label label[MAX_SCREEN_LABELS];
} BAKU_Site_Cfg;

extern BAKU_Site_Cfg g_baku_data;

#endif // BAKUDATACONFIG_H
