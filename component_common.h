#ifndef COMPONENT_COMMON_H
#define COMPONENT_COMMON_H

#define MAX_SCREEN_TRACKS 256
#define MAX_SCREEN_SIGNALS 64
#define MAX_SCREEN_PLATFORMS 28
#define MAX_SCREEN_LABELS 20
#define MAX_TRACK_POINTS 16
#define MAX_NUMBER_ROUTES 16

#define POST_WIDTH 2
#define SHUNT_POST_WIDTH 2
#define POST_HEIGHT 15
#define SIG_LG_SPCR_W 3
#define SIG_LG_SPCR_H 6
#define SIG_SM_SPCR_W 3
#define SIG_SM_SPCR_H 4
#define SIGNAL_SPCR_LGTH 3
#define ASPECT_SIG_DEFAULT_RADIUS 10
#define SHUNT_SIG_DEFAULT_RADIUS 10
#define ROUTE_SIG_HALO_RADIUS 14
#define DEFAULT_SIG_RADIUS 10
#define TRACK_LABEL_SPCR 5
#define MAIN_TRACK_WIDTH 10
#define MAX_SCREEN_WIDTH 5760
#define TRACK_BUFFER 4

#define CLRD_BULB_RADIUS 5
#define CLRD_BULB_IDNT 3
#define COLOURED_SIG_HEIGHT 16
#define COLOURED_SIG_BODY_WIDTH 28
#define SMALL_COLOURED_SIG_BODY_WIDTH 23
#define CLRD_SPCR_LGTH 3

#define TRAIN_HEIGHT 20
#define TRAIN_WIDTH 60

#define INITIAL_STATE 0xff

enum
{
    OFF = 1,
    ON,
    COMPONENT_DEFINED,
    INVALID_COMPONENT_STATE
} Component_States;

#define UNOCCUPIED OFF
#define OCCUPIED ON

#define ASPECT_YELLOW_STATE COMPONENT_DEFINED

enum
{
    SIGNALLING_TRACK,
    END_TRACK,
    NON_SIGNALLING_TRACK,
    DYNAMIC_SIGNALLING_TRACK,
    OTHER_LINE_TRACK,
    INVALID_TRACK_TYPE
} TrackTypes;

enum
{
    COLOURED_SIGNAL = 1,
    SHUNT_SIGNAL,
    UKE_SIGNAL,
    ASPECT_SIGNAL,
    DYNAMIC_ASPECT_SIGNAL,
    YELLOW_COLOURED_SIGNAL,
    FIXED_RED_SIGNAL,
    SPEED_CONTROL_SIGNAL,
    ROUTE_SIGNAL,
    ROUTE_SHUNT_SIGNAL,
    SMALL_COLOURED_SIGNAL,
    INVALID_SIGNAL_TYPE
} SignalTypes;

enum
{
    INVALID_SITE,
    HEATHROW_T123,
    TURNHAM_GREEN,
    OAKWOOD,
    OXFORD_CIRCUS,
    PICCADILLY_CIRCUS,
    MAX_SITES
} Sites;

enum
{
    DONT_DISPLAY,
    ABOVE,
    BELOW,
    LEFT,
    RIGHT,
    INVALID_POSITION
} Signalling_Positions;

enum
{
    NO_IO_TYPE,
    IO_TYPE_RGKE,
    IO_TYPE_DGKE,
    INVALID_IO_TYPE
} IO_Types;

enum
{
    PLATFORM_TYPE,
    IMR_TYPE,
    SPINDLE_TYPE,
    UNKNOWN_PLATFORM_TYPE
} PLATFORM_TYPES;

enum
{
    TOP_PLATFORM,
    BOTTOM_PLATFORM,
    MAX_PLATFORM_INDEX
} PLATFORM_INDEX;

enum
{
    FONT_SIZE_SMALL,
    FONT_SIZE_MEDIUM,
    FONT_SIZE_LARGE,
    FONT_SIZE_TRACK
} LABEL_SIZES;

enum
{
    EASTBOUND,
    WESTBOUND,
    BI_DIRECTIONAL
} Directions;

//!
//! Dynamic data structure for the train
//!
typedef struct
{
    int tn;
    int trn;
    int td;
    int direction;
} BAKU_Train;


#endif // COMPONENT_COMMON_H
