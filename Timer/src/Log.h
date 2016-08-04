/*
 * Log.h
 *
 *  Created on: 2016年7月31日
 *      Author: shanhui
 */

#pragma once


#include <stdarg.h>
#include <syslog.h>


enum log_levels
{
    DEBUG_LOG   = LOG_DEBUG,    /* 7 debug-level messages */
    INFO_LOG    = LOG_INFO,     /* 6 informational */
    NOTICE_LOG  = LOG_NOTICE,   /* 5 normal but significant condition */
    WARN_LOG    = LOG_WARNING,  /* 4 warning conditions */
    ERROR_LOG   = LOG_ERR,      /* 3 error conditions */
    FATAL_LOG   = LOG_CRIT,     /* 2 critical conditions */
};


inline void open_log()
{
    ::openlog(nullptr, LOG_PID|LOG_NDELAY, LOG_USER|LOG_DAEMON);
}


inline void log(log_levels level, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    ::vsyslog(level, format, args);
    va_end(args);
}


inline void close_log()
{
    ::closelog();
}


#define LOG(level, fmt, ...) log(level##_LOG, "%s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

