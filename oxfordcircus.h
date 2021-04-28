#ifndef OXFORDCIRCUS_H
#define OXFORDCIRCUS_H

#include "bakudataconfig.h"
#include "component_common.h"

static BAKU_Site_Cfg oxfordcircus_data =
{
    // Signals
    16,
    {
        {1 ,"A4011"  ,""             ,ASPECT_SIGNAL  , 135,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {2 ,"A395"  ,""              ,ASPECT_SIGNAL  , 280,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {3 ,"A391"  ,""              ,ASPECT_SIGNAL  , 655,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {4 ,"A387"  ,""              ,ASPECT_SIGNAL  , 990,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {5 ,"A385"  ,""              ,ASPECT_SIGNAL  ,1135,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {6 ,"A383"  ,""              ,ASPECT_SIGNAL  ,1320,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {7 ,"A381"  ,""              ,ASPECT_SIGNAL  ,1550,249,ABOVE,ABOVE,RIGHT,true,0,NO_IO_TYPE},
        {8 ,"A374"  ,""              ,ASPECT_SIGNAL  ,1850,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {9 ,"A37B"  ,""              ,ASPECT_SIGNAL  ,1565,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {10,"A382"  ,""              ,ASPECT_SIGNAL  ,1335,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {11,"A3822" ,""              ,ASPECT_SIGNAL  ,1069,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {12,"A386"  ,""              ,ASPECT_SIGNAL  , 803,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {13,"A392"  ,""              ,ASPECT_SIGNAL  , 440,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {14,"A3921" ,""              ,ASPECT_SIGNAL  , 295,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {15,"A3821" ,""              ,ASPECT_SIGNAL  ,1202,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},
        {16,"A376"  ,""              ,ASPECT_SIGNAL  ,1660,351,BELOW,BELOW,LEFT ,true,0,NO_IO_TYPE},

    },

    // Tracks
    25,
    {
        { 1,"BM"       ,"I_BP_BM_TR"       ,SIGNALLING_TRACK,{   0 ,250, 140 ,250, 140 ,260,   0 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 2,"BP"       ,"I_BP_BP_TR"       ,SIGNALLING_TRACK,{ 145 ,250, 285 ,250, 285 ,260, 145 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 3,"BR"       ,"I_BP_BR_TR"       ,SIGNALLING_TRACK,{ 290 ,250, 430 ,250, 430 ,260, 290 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 4,"395A"     ,"I_BP_395A_TR"     ,SIGNALLING_TRACK,{ 435 ,250, 660 ,250, 660 ,260, 435 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 5,"395B"     ,"I_BP_395B_TR"     ,SIGNALLING_TRACK,{ 665 ,250, 835 ,250, 835 ,260, 665 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 6,"391A"     ,"I_BP_391A_TR"     ,SIGNALLING_TRACK,{ 840 ,250, 995 ,250, 995 ,260, 840 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 7,"391B"     ,"I_BP_391B_TR"     ,SIGNALLING_TRACK,{1000 ,250,1140 ,250,1140 ,260,1000 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 8,"391C"     ,"I_BP_391C_TR"     ,SIGNALLING_TRACK,{1145 ,250,1325 ,250,1325 ,260,1145 ,260},ABOVE,4  ,1  ,EASTBOUND},
        { 9,"385"      ,"I_BP_385_TR"      ,SIGNALLING_TRACK,{1330 ,250,1555 ,250,1555 ,260,1330 ,260},BELOW,4  ,1  ,EASTBOUND},
        {10,"383"      ,"I_BP_383_TR"      ,SIGNALLING_TRACK,{1560 ,250,1740 ,250,1740 ,260,1560 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {11,"381A"     ,"I_BP_381A_TR"     ,SIGNALLING_TRACK,{1745 ,250,1919 ,250,1919 ,260,1745 ,260},ABOVE,4  ,1  ,EASTBOUND},
        {12,"NE.ND"    ,"I_BP_NE_ND_TR"    ,SIGNALLING_TRACK,{1845 ,340,1919 ,340,1919 ,350,1845 ,350},BELOW,4  ,0  ,WESTBOUND},
        {13,"NF"       ,"I_BP_NF_TR"       ,SIGNALLING_TRACK,{1750 ,340,1840 ,340,1840 ,350,1750 ,350},BELOW,4  ,1  ,WESTBOUND},
        {14,"NH"       ,"I_BP_NH_TR"       ,SIGNALLING_TRACK,{1655 ,340,1745 ,340,1745 ,350,1655 ,350},BELOW,4  ,1  ,WESTBOUND},
        {15,"374"      ,"I_BP_374_TR"      ,SIGNALLING_TRACK,{1560 ,340,1650 ,340,1650 ,350,1560 ,350},BELOW,4  ,1  ,WESTBOUND},
        {16,"376"      ,"I_BP_376_TR"      ,SIGNALLING_TRACK,{1330 ,340,1555 ,340,1555 ,350,1330 ,350},ABOVE,4  ,1  ,WESTBOUND},
        {17,"378"      ,"I_BP_378_TR"      ,SIGNALLING_TRACK,{1197 ,340,1325 ,340,1325 ,350,1197 ,350},BELOW,4  ,1  ,WESTBOUND},
        {18,"382A"     ,"I_BP_382A_TR"     ,SIGNALLING_TRACK,{1064 ,340,1192 ,340,1192 ,350,1064 ,350},BELOW,4  ,1  ,WESTBOUND},
        {19,"382B"     ,"I_BP_382B_TR"     ,SIGNALLING_TRACK,{ 931 ,340,1059 ,340,1059 ,350, 931 ,350},BELOW,4  ,1  ,WESTBOUND},
        {20,"382C"     ,"I_BP_382C_TR"     ,SIGNALLING_TRACK,{ 798 ,340, 926 ,340, 926 ,350, 798 ,350},BELOW,4  ,1  ,WESTBOUND},
        {21,"382D"     ,"I_BP_382D_TR"     ,SIGNALLING_TRACK,{ 665 ,340, 793 ,340, 793 ,350, 665 ,350},BELOW,4  ,1  ,WESTBOUND},
        {22,"386A"     ,"I_BP_386A_TR"     ,SIGNALLING_TRACK,{ 435 ,340, 660 ,340, 660 ,350, 435 ,350},ABOVE,4  ,1  ,WESTBOUND},
        {23,"386B"     ,"I_BP_386B_TR"     ,SIGNALLING_TRACK,{ 290 ,340, 430 ,340, 430 ,350, 290 ,350},BELOW,4  ,1  ,WESTBOUND},
        {24,"386C"     ,"I_BP_386C_TR"     ,SIGNALLING_TRACK,{ 145 ,340, 285 ,340, 285 ,350, 145 ,350},BELOW,4  ,1  ,WESTBOUND},
        {25,"392A"     ,"I_BP_392A_TR"     ,SIGNALLING_TRACK,{   0 ,340, 140 ,340, 140 ,350,   0 ,350},BELOW,4  ,1  ,WESTBOUND},


    },

    // Platforms
    4,
    {
        {0,1,	 457, 270, 180, 50, "","",true,false, PLATFORM_TYPE},
        {0,2,	1352, 180, 180, 60, "","",true,false, PLATFORM_TYPE},
        {0,3,	1352, 360, 180, 60, "","",true,false, PLATFORM_TYPE},
        {0,4,	 457, 360, 180, 50, "","",true,false, PLATFORM_TYPE},

    },

    // Screen Labels
    3,
    {
        {1, 455,150, FONT_SIZE_LARGE, "REGENTS PARK"},
        {2,1335,150, FONT_SIZE_LARGE, "OXFORD CIRCUS"},

    }
};

#endif // OXFORDCIRCUS_H
