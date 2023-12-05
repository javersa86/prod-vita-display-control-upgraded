#include "gpio.h"

/**
 * @addtogroup gpioMainModule
 * @{
 */

/** @} */

GPIO::GPIO(uint pinNumber, char* edge, bool isOut, QObject *parent) : QObject(parent), _pinNumber(pinNumber)
{
    exportPin();
    setDirection(isOut);
    setEdge(edge);
}

GPIO::~GPIO()
{
    if( 0 <= _ioFd )
    {
        close(_ioFd);
    }
}

auto GPIO::getValue() -> unsigned char
{
    //If the pin has direction "in,"
    if( !_isOut )
    {
        if(0 > _ioFd)
        {
            openFd();
        }
        if(0 > _ioFd)
        {
            return _ioFd;
        }

        char chRead = -1;

        read(_ioFd, &chRead, 1);

        //since GPIO value is saved in file, it will be returned as a char
        if(chRead != '0')
        {
            return 1;
        }
        return 0;
    }

    return 0;
}

auto GPIO::exportPin() const -> int
{
    int fileDescriptor = -1;
    int len = -1;
    std::array<char,ENCODER_MAX_BUF> buf{};

    fileDescriptor = open(SYSFS_GPIO_DIR "/export", O_WRONLY);

    if( fileDescriptor < 0 ){
        //TODO: log error
        return fileDescriptor;
    }

    len = qsnprintf(buf.data(), sizeof(buf), "%d", _pinNumber);
    write(fileDescriptor, buf.data(), len);
    close(fileDescriptor);

    return 0;
}

void GPIO::openFd()
{
    std::array<char,ENCODER_MAX_BUF> buf{};

    qsnprintf(buf.data(), sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", _pinNumber);

    if( 0 <= _ioFd )
    {
        close(_ioFd );
    }

    if( _isOut )
    {
        _ioFd = open(buf.data(), O_RDWR);
    }
    else
    {
        _ioFd = open(buf.data(), O_RDONLY);
    }

    if( 0 > _ioFd )
    {
        //TODO: log error
    }
}

auto GPIO::getFD() const -> int
{
    return _ioFd;
}

auto GPIO::setDirection(bool out) -> int
{
    int fileDescriptor = -1;
    std::array<char,ENCODER_MAX_BUF> buf{};

    qsnprintf(buf.data(), sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", _pinNumber);
    fileDescriptor = open(buf.data(), O_WRONLY);

    if( fileDescriptor < 0 )
    {
        //TODO: log error
        return fileDescriptor;
    }

    if( out )
    {
        write(fileDescriptor, "out", 4);
    }
    else
    {
        write(fileDescriptor, "in", 3);
    }

    close(fileDescriptor);

    _isOut = out;

    return 0;
}

auto GPIO::setEdge(char *edge) const -> int
{
    int fileDescriptor = -1;
    std::array<char,ENCODER_MAX_BUF> buf{};

    qsnprintf(buf.data(), sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", _pinNumber);

    fileDescriptor = open(buf.data(), O_WRONLY);

    if( fileDescriptor < 0 )
    {
        //TODO: log error
        return fileDescriptor;
    }

    write(fileDescriptor, edge, strlen(edge) + 1);

    close(fileDescriptor);

    return 0;
}
