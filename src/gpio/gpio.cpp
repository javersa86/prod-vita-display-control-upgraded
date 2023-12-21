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

unsigned char GPIO::getValue()
{
    //If the pin has direction "in,"
    if( !_is_out )
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

int GPIO::exportPin() const
{
    int fileDescriptor = -1;
    int len = -1;
    std::array<char,ENCODER_MAX_BUF> buf{};

    fileDescriptor = open((std::string(SYSFS_GPIO_DIR) + "/export").c_str(), O_WRONLY);

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

    qsnprintf(buf.data(), sizeof(buf), (std::string(SYSFS_GPIO_DIR) + "/gpio%d/value").c_str(), _pinNumber);

    if( 0 <= _ioFd )
    {
        close(_ioFd );
    }

    if( _is_out )
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

int GPIO::getFD() const
{
    return _ioFd;
}

int GPIO::setDirection(bool out)
{
    int fileDescriptor = -1;
    std::array<char,ENCODER_MAX_BUF> buf{};

    qsnprintf(buf.data(), sizeof(buf), (std::string(SYSFS_GPIO_DIR) + "/gpio%d/direction").c_str(), _pinNumber);
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

    _is_out = out;

    return 0;
}

int GPIO::setEdge(char *edge) const
{
    int fileDescriptor = -1;
    std::array<char,ENCODER_MAX_BUF> buf{};

    qsnprintf(buf.data(), sizeof(buf), (std::string(SYSFS_GPIO_DIR) + "/gpio%d/edge").c_str(), _pinNumber);

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
