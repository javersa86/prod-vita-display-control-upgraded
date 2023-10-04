#include <fcntl.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <poll.h>
#include <QDebug>

#include "gpio.h"

/**
 * @addtogroup gpioMainModule
 * @{
 */

/**
 * @brief MAX Buffer size for pin update.
 */
#define MAX_BUF 64

/**
 * @brief Constant string for file path for gpio.
 */
#define SYSFS_GPIO_DIR "/sys/class/gpio"

/** @} */

GPIO::GPIO(uint pinNumber, char* edge, bool isOut, QObject *parent) : QObject(parent){
    _currentValue = 2;	// Make it out of range to force write if out pin
    _ioFd = -1;					// Make it invalid to force initial open
    _pinNumber = pinNumber;

    exportPin();
    setDirection(isOut);
    setEdge(edge);
}

GPIO::~GPIO(){
    if( 0 <= _ioFd ) close(_ioFd);
}

unsigned char GPIO::getValue(){

    //If the pin has direction "in,"
    if( !_isOut ){
        if( 0 > _ioFd ) openFd();
        if( 0 > _ioFd ) return _ioFd;

        char ch;

        read(_ioFd, &ch, 1);
        //since GPIO value is saved in file, it will be returned as a char
        if( ch != '0' ){
            return 1;
        }else{
            return 0;
        }
    }

    return 0;
}

int GPIO::exportPin(){
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if( fd < 0 ){
        //TODO: log error
        return fd;
    }

    len = qsnprintf(buf, sizeof(buf), "%d", _pinNumber);
    write(fd, buf, len);
    close(fd);

    return 0;
}

void GPIO::openFd(){
    int len;
    char buf[MAX_BUF];

    len = qsnprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", _pinNumber);

    if( 0 <= _ioFd ) close(_ioFd );

    if( _isOut )
        _ioFd = open(buf, O_RDWR);
    else
        _ioFd = open(buf, O_RDONLY);

    if( 0 > _ioFd ){
        //TODO: log error
    }
}

int GPIO::getFD()
{
    return _ioFd;
}

int GPIO::setDirection(bool out){
    int fd, len;
    char buf[MAX_BUF];

    len = qsnprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", _pinNumber);

    fd = open(buf, O_WRONLY);
    if( fd < 0 ){
        //TODO: log error
        return fd;
    }

    if( out ){
        write(fd, "out", 4);
    }else{
        write(fd, "in", 3);
    }

    close(fd);

    _isOut = out;

    return 0;
}

int GPIO::setEdge(char *edge){
    int fd, len;
    char buf[MAX_BUF];

    len = qsnprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", _pinNumber);

    fd = open(buf, O_WRONLY);
    if( fd < 0 ){
        //TODO: log error
        return fd;
    }

    write(fd, edge, strlen(edge) + 1);

    close(fd);

    return 0;
}
