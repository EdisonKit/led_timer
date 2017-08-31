/*
 * Timer.h
 *
 *  Created on: 2016年7月31日
 *      Author: shanhui
 */
#pragma once
#include <memory>
#include <vector>
#include "mraa.hpp"


static const uint32_t LED_SIZE = 4;


class Timer
{
public:
    Timer();


    ~Timer();


    int initPin();


    void run();


    void setPause();


    void setStop();


    void setStart();


    void setReset();


private:
    bool initOnePin(std::shared_ptr<mraa::Gpio> &pin, uint32_t pinNum);


    bool nowTime();


    void display();


    void clear();


    void ledOut(uint8_t data, uint8_t pos);


private:
    bool                            m_isPause;
    uint64_t                        m_now;
    uint32_t                        m_preDelta;
    std::shared_ptr<mraa::Gpio>     m_test;
    std::shared_ptr<mraa::Gpio>     m_dioPin;
    std::shared_ptr<mraa::Gpio>     m_rclkPin;
    std::shared_ptr<mraa::Gpio>     m_sclkPin;
};
