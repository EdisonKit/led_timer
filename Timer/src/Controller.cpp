/*
 * Controller.cpp
 *
 *  Created on: 2016年8月4日
 *      Author: shanhui
 */
#include "Log.h"
#include "Controller.h"


enum CODEC
{
    CODEC_0     = 0x807FE817,
    CODEC_1     = 0x807FA05F,
    CODEC_2     = 0x807F906F,
    CODEC_3     = 0x807FB04F,
    CODEC_4     = 0x807F20DF,
    CODEC_5     = 0x807F10EF,
    CODEC_6     = 0x807F30CF,
    CODEC_7     = 0x807F0AF5,
    CODEC_8     = 0x807F08F7,
    CODEC_9     = 0x807F8877,
    CODEC_START = 0x807F42BD,
    CODEC_PAUSE = 0x807F629D,
    CODEC_STOP  = 0x807F52AD,
    CODEC_RESET = 0x807F728D,
};


Controller::Controller()
{
}


Controller::~Controller()
{
}

