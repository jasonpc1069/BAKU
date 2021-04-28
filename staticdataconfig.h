#ifndef STATICDATACONFIG_H
#define STATICDATACONFIG_H

#include "component_common.h"

//!
//! Static data structure for the track component.
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
}PICU_Static_Track;

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
    int number_routes;
    int route_id[MAX_NUMBER_ROUTES];
    int conflicting_x;
    int conflicting_y;
    bool display_signal;
    int io_type;
}PICU_Static_Signal;

//!
//! Static data structure for the platform component.
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
      unsigned short rotate_direction;
      unsigned short type;
      unsigned short top_cp_id;
      unsigned short bottom_cp_id;
      unsigned short site_id;
      int site_secure_update_flag;
      unsigned short track_id[MAX_PLATFORM_INDEX];
}PICU_Static_Platform;

//!
//! Static data structure for the screen label component.
//!
typedef struct
{
    int label_id;
    int x_pos;
    int y_pos;
    int label_font_id;
    char label_name [32];
    unsigned short label_group_index;
    unsigned short site_id;
    int site_secure_update_flag;
    unsigned short main_cabin_flag;
    unsigned short tel_data_id;
    unsigned short station_id;
    unsigned short station_dir;
}PICU_Static_Label;

typedef struct
{
    int num_signals;
    PICU_Static_Signal signal[MAX_SCREEN_SIGNALS];
    int num_tracks;
    PICU_Static_Track track[MAX_SCREEN_TRACKS];
    int num_platforms;
    PICU_Static_Platform platform[MAX_SCREEN_PLATFORMS];
    int num_labels;
    PICU_Static_Label label[MAX_SCREEN_LABELS];
} PICU_Static_Site_Cfg;

extern PICU_Static_Site_Cfg g_picu_static_data;

#endif // STATICDATACONFIG_H
