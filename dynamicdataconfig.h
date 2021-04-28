#ifndef DYNAMICDATACONFIG_H
#define DYNAMICDATACONFIG_H

#include "component_common.h"
#include "bakudataconfig.h"
#include "track.h"
#include "SignalIndicator.h"
#include "platform.h"

//!
//! Dynamic data structure for the track component.
//!
typedef struct
{
      BAKU_Track data;
      Track *track;
      int state;
      int has_train;
      BAKU_Train train;
} BAKU_Dynamic_Track;

typedef struct
{
    BAKU_Signal data;
    SignalIndicator *signal;
    int state;
}BAKU_Dynamic_Signal;

//!
//! Dynamic data structure for the platform component.
//!
typedef struct
{
    BAKU_Platform data;
    Platform *platform;
}BAKU_Dynamic_Platform;

//!
//! Dynamic data structure for the screen label component.
//!
typedef struct
{
    BAKU_Screen_Label data;
}BAKU_Dynamic_Label;

typedef struct
{
    int num_signals;
    BAKU_Dynamic_Signal signal[MAX_SCREEN_SIGNALS];
    int num_tracks;
    BAKU_Dynamic_Track track[MAX_SCREEN_TRACKS];
    int num_platforms;
    BAKU_Dynamic_Platform platform[MAX_SCREEN_PLATFORMS];
    int num_labels;
    BAKU_Dynamic_Label label[MAX_SCREEN_LABELS];
} BAKU_Dynamic_Data_Cfg;

extern BAKU_Dynamic_Data_Cfg g_baku_dynamic_data;

#endif // DYNAMICDATACONFIG_H
