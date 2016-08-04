/*
 * Timer.h
 *
 *  Created on: 2016年7月31日
 *      Author: shanhui
 */
#include <unistd.h>
#include <chrono>
#include "Log.h"
#include "Timer.h"

//      0
//      --
//   5 |  | 1
//      --  6
//   4 |  | 2
//      --  .
//      3   7
static const uint8_t LED[] =
{
    // 0     1     2     3     4
	0xC0, 0xF9, 0xA4, 0xB0, 0x99,
	// 5     6     7     8     9
	0x92, 0x82, 0xF8, 0x80, 0x90,
};


static const uint8_t LED_WITH_POINT[] =
{
    // 0     1     2     3     4
    0x40, 0x79, 0x24, 0x30, 0x19,
    // 5     6     7     8     9
    0x12, 0x02, 0x78, 0x00, 0x10,
};


static const int PIN_DIO = 8;
static const int PIN_RCLK = 9;
static const int PIN_SCLK = 10;

static const uint8_t NULL_DATA = 0xFF;


// 999999 => 999.9|99|
static const uint32_t TIMER_MAX = 1000000;


Timer::Timer()
    : m_preDelta(0)
{
    m_now = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
}


Timer::~Timer()
{
}


int Timer::initPin()
{
    if (!initOnePin(m_dioPin, PIN_DIO)) {
        return mraa::ERROR_NO_RESOURCES;
    }

    if (!initOnePin(m_rclkPin, PIN_RCLK)) {
        return mraa::ERROR_NO_RESOURCES;
    }

    if (!initOnePin(m_sclkPin, PIN_SCLK)) {
        return mraa::ERROR_NO_RESOURCES;
    }

    return mraa::SUCCESS;
}


void Timer::run()
{
    nowTime();
    display();
}


bool Timer::initOnePin(std::shared_ptr<mraa::Gpio> &pin, uint32_t pinNum)
{
    try {
        pin = std::shared_ptr<mraa::Gpio>(new mraa::Gpio(pinNum));
    } catch (std::invalid_argument e) {
        LOG(ERROR, "Exception: %s PIN %d", e.what(), pinNum);
        return false;
    }

    if (pin->dir(mraa::DIR_OUT) != mraa::SUCCESS) {
        LOG(ERROR, "Can't set digital pin %d as output, exiting", pinNum);
        return false;
    }

    return true;
}


bool Timer::nowTime()
{
    uint64_t nowms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    uint32_t delta = static_cast<uint32_t>(nowms - m_now);

    if (delta > TIMER_MAX) {
        delta %= TIMER_MAX;
        delta /= 100;
    } else {
        delta /= 100;
    }

    if (m_preDelta == delta) {
        return false;
    } else {
        m_preDelta = delta;
    }

    return true;
}


void Timer::display()
{
    uint8_t ledData;

    LOG(INFO, "display %d", m_preDelta);

    //显示第1位
    ledData = *(LED + m_preDelta % 10);
    ledOut(ledData, 0x01);
    m_rclkPin->write(0);
    m_rclkPin->write(1);

    if (m_preDelta < 10) {
        ledOut(NULL_DATA, 0x02);
        m_rclkPin->write(0);
        m_rclkPin->write(1);

        ledOut(NULL_DATA, 0x04);
        m_rclkPin->write(0);
        m_rclkPin->write(1);

        ledOut(NULL_DATA, 0x08);
        m_rclkPin->write(0);
        m_rclkPin->write(1);
        return;
    }

    //显示第2位
    ledData = *(LED_WITH_POINT + (m_preDelta / 10) % 10);
    ledOut(ledData, 0x02);
    m_rclkPin->write(0);
    m_rclkPin->write(1);

    if (m_preDelta < 100) {
        ledOut(NULL_DATA, 0x04);
        m_rclkPin->write(0);
        m_rclkPin->write(1);

        ledOut(NULL_DATA, 0x08);
        m_rclkPin->write(0);
        m_rclkPin->write(1);
        return;
    }

    //显示第3位
    ledData = *(LED + (m_preDelta / 100) % 10);
    ledOut(ledData, 0x04);
    m_rclkPin->write(0);
    m_rclkPin->write(1);

    if (m_preDelta < 1000) {
        ledOut(NULL_DATA, 0x08);
        m_rclkPin->write(0);
        m_rclkPin->write(1);
        return;
    }

    //显示第4位
    ledData = *(LED + (m_preDelta / 1000) % 10);
    ledOut(ledData, 0x08);
    m_rclkPin->write(0);
    m_rclkPin->write(1);
}


void Timer::clear()
{
    ledOut(NULL_DATA, 0x01);
    ledOut(NULL_DATA, 0x02);
    ledOut(NULL_DATA, 0x04);
    ledOut(NULL_DATA, 0x08);
}


void Timer::ledOut(uint8_t data, uint8_t pos)
{
    for (uint8_t i = 8; i >= 1; --i) {
        m_dioPin->write(static_cast<int>(data&0x80) ? 1 : 0);
        m_sclkPin->write(0);
        m_sclkPin->write(1);
        data <<= 1;
    }

    for (uint8_t i = 8; i >= 1; --i) {
        m_dioPin->write(static_cast<int>(pos&0x80) ? 1 : 0);
        m_sclkPin->write(0);
        m_sclkPin->write(1);
        pos <<= 1;
    }
}


