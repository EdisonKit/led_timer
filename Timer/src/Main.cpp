/*
 * Timer.h
 *
 *  Created on: 2016年7月31日
 *      Author: shanhui
 */
#include "Timer.h"
#include "Log.h"


int main(int argc, char **argv)
{
    open_log();

    Timer timer;
    if (timer.initPin() != mraa::SUCCESS) {
        return 1;
    }

    while (true) {
        timer.run();
    }

    close_log();
    return 0;
}
