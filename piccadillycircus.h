#ifndef PICCADILLYCIRCUS_H
#define PICCADILLYCIRCUS_H

#include "bakudataconfig.h"
#include "component_common.h"

static BAKU_Site_Cfg piccadillycircus_data =
{
    // Signals
    16,
    {
        {1 ,"A367"  ,""             ,ASPECT_SIGNAL  ,  815,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {2 ,"A365"  ,""             ,ASPECT_SIGNAL   , 930,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {3 ,"A361"  ,""             ,ASPECT_SIGNAL   ,1300,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {4 ,"X355"  ,""             ,ASPECT_SIGNAL   ,1420,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {5 ,"A342"  ,""             ,ASPECT_SIGNAL   ,1555,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {6 ,"A346"  ,""             ,ASPECT_SIGNAL   ,1435,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {7 ,"A362"  ,""             ,ASPECT_SIGNAL   ,1060,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {8 ,"A3621" ,""             ,ASPECT_SIGNAL   , 945,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {9 ,"A1000" ,""             ,ASPECT_SIGNAL   , 230,339,ABOVE,ABOVE,LEFT ,true,0,NO_IO_TYPE},
        {10,"A9000" ,""             ,ASPECT_SIGNAL   , 165,339,ABOVE,ABOVE,LEFT ,true,0,NO_IO_TYPE},
        {11,"A9001" ,""             ,ASPECT_SIGNAL   , 100,339,ABOVE,ABOVE,LEFT ,true,0,NO_IO_TYPE},
        {12,"BP120" ,"I_BP_120_GR"  ,COLOURED_SIGNAL , 830,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {13,"BP12"  ,"I_BP_12_GR"   ,COLOURED_SIGNAL , 715,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {14,"BP11"  ,"I_BP_11_GR"   ,COLOURED_SIGNAL , 600,339,ABOVE,ABOVE,LEFT ,true,0,NO_IO_TYPE},
        {15,"BP9"   ,"I_BP_9_GR"    ,COLOURED_SIGNAL , 215,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {16,"BP1"   ,"I_BP_1_GR"    ,COLOURED_SIGNAL ,  75,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
    },

    // Tracks
    26,
    {
        { 1,"381B"       ,"I_BP_381B_TR"       ,SIGNALLING_TRACK,{   0 ,250,  90 ,250,  90 ,260,   0 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 2,"381C"       ,"I_BP_381C_TR"       ,SIGNALLING_TRACK,{  95 ,250, 205 ,250, 205 ,260,  95 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 3,"MB"         ,"I_BP_MB_TR"         ,SIGNALLING_TRACK,{ 210 ,250, 385 ,250, 385 ,260, 210 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 4,"MD"         ,"I_BP_MD_TR"         ,SIGNALLING_TRACK,{ 390 ,250, 590 ,250, 590 ,260, 390 ,260},BELOW,4  ,1  ,EASTBOUND},
        { 5,"MF"         ,"I_BP_MF_TR"         ,SIGNALLING_TRACK,{ 595 ,250, 705 ,250, 705 ,260, 595 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 6,"MH"         ,"I_BP_MH_TR"         ,SIGNALLING_TRACK,{ 710 ,250, 820 ,250, 820 ,260, 710 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 7,"MK"         ,"I_BP_MK_TR"         ,SIGNALLING_TRACK,{ 825 ,250, 935 ,250, 935 ,260, 825 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 8,"ML"         ,"I_BP_ML_TR"         ,SIGNALLING_TRACK,{ 940 ,250,1050 ,250,1050 ,260, 940 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 9,"367"        ,"I_BP_367_TR"        ,SIGNALLING_TRACK,{1055 ,250,1305 ,250,1305 ,260,1055 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {10,"365"        ,"I_BP_365_TR"        ,SIGNALLING_TRACK,{1310 ,250,1425 ,250,1425 ,260,1310 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {11,"361"        ,"I_BP_361_TR"        ,SIGNALLING_TRACK,{1430 ,250,1545 ,250,1545 ,260,1430 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {12,"355A"       ,"I_BP_355A_TR"       ,SIGNALLING_TRACK,{1550 ,250,1800 ,250,1800 ,260,1550 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {13,"355B"       ,"I_BP_355B_TR"       ,SIGNALLING_TRACK,{1805 ,250,1919 ,250,1919 ,260,1805 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {14,"332C"       ,"I_BP_332C_TR"       ,SIGNALLING_TRACK,{1805 ,340,1919 ,340,1919 ,350,1805 ,350},BELOW,4  ,1  ,WESTBOUND},
        {15,"336A"       ,"I_BP_336A_TR"       ,SIGNALLING_TRACK,{1550 ,340,1800 ,340,1800 ,350,1550 ,350},BELOW,4  ,1  ,WESTBOUND},
        {16,"336B"       ,"I_BP_336B_TR"       ,SIGNALLING_TRACK,{1430 ,340,1545 ,340,1545 ,350,1430 ,350},BELOW,4  ,1  ,WESTBOUND},
        {17,"342"        ,"I_BP_342_TR"        ,SIGNALLING_TRACK,{1310 ,340,1425 ,340,1425 ,350,1310 ,350},BELOW,4  ,1  ,WESTBOUND},
        {18,"346A"       ,"I_BP_346A_TR"       ,SIGNALLING_TRACK,{1055 ,340,1305 ,340,1305 ,350,1055 ,350},BELOW,4  ,1  ,WESTBOUND},
        {19,"346B"       ,"I_BP_346B_TR"       ,SIGNALLING_TRACK,{ 940 ,340,1050 ,340,1050 ,350, 940 ,350},BELOW,4  ,1  ,WESTBOUND},
        {20,"362A"       ,"I_BP_362A_TR"       ,SIGNALLING_TRACK,{ 825 ,340, 935 ,340, 935 ,350, 825 ,350},BELOW,4  ,1  ,WESTBOUND},
        {21,"362B"       ,"I_BP_362B_TR"       ,SIGNALLING_TRACK,{ 710 ,340, 820 ,340, 820 ,350, 710 ,350},BELOW,4  ,1  ,WESTBOUND},
        {22,"362C"       ,"I_BP_362C_TR"       ,SIGNALLING_TRACK,{ 595 ,340, 705 ,340, 705 ,350, 595 ,350},BELOW,4  ,1  ,WESTBOUND},
        {23,"NB"         ,"I_BP_NB_TR"         ,SIGNALLING_TRACK,{ 210 ,340, 590 ,340, 590 ,350, 210 ,350},ABOVE,4  ,1  ,WESTBOUND},
        {24,"NE.ND"      ,"I_BP_NE_ND_TR"      ,SIGNALLING_TRACK,{   0 ,340, 205 ,340, 205 ,350,   0 ,350},BELOW,4  ,1  ,WESTBOUND},
        {25,""           ,"I_BP_NB_TR"         ,SIGNALLING_TRACK,{ 235 ,331, 287 ,302, 297 ,309, 245 ,338},BELOW,4  ,0  ,BI_DIRECTIONAL},
        {26,""           ,"I_BP_MB_TR"         ,SIGNALLING_TRACK,{ 293 ,298, 353 ,265, 363 ,272, 303 ,305},BELOW,4  ,0  ,BI_DIRECTIONAL}

    },

    // Platforms
    4,
    {
        {0,1,	 400, 180, 180, 60, "","2",true,false, PLATFORM_TYPE},
        {0,2,	1090, 270, 180, 60, "","" ,true,false, PLATFORM_TYPE},
        {0,3,	1585, 270, 180, 60, "","" ,true,false, PLATFORM_TYPE},
        {4,0,	 400, 360, 180, 60, "1","" ,true,false,PLATFORM_TYPE},
    },

    // Screen Labels
    3,
    {
        {1, 365,150, FONT_SIZE_LARGE, "PICCADILLY CIRCUS"},
        {2,1075,150, FONT_SIZE_LARGE, "CHARING CROSS"},
        {3,1585,150, FONT_SIZE_LARGE, "EMBANKMENT"},
    }
};

#endif // PICCADILLYCIRCUS_H
