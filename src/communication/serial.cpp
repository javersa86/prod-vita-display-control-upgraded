#include "serial.h"


auto Comm::openPort() -> int
{
    QByteArray byte_array = _portname.toLocal8Bit();
    const char *c_str1 = byte_array.data();

    fileDescriptor = open(c_str1, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fileDescriptor == -1)
    {
        qDebug() << "@@@ Serial::openPort: " << "Error serial init!";
        return 1;
    }

    fcntl(fileDescriptor, F_SETFL, 0);
    return 0;
    //port is open
}

auto Comm::configurePort() const -> int
{
    struct termios tty; //structure to store the port settings in
    // Read in existing settings, and handle any error
    if(tcgetattr(fileDescriptor, &tty) != 0) {
        qDebug() << "Error from tcgetattr: " << strerror(errno);
        return 1;
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    const int deciseconds = 10;

    tty.c_cc[VTIME] = deciseconds;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    //cfsetispeed(&tty,_baudrate);
    //cfsetospeed(&tty,_baudrate);
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(fileDescriptor, TCSANOW, &tty) != 0) {
        qDebug() << "Error from tcsetattr: " << strerror(errno);
        return 1;
    }
    return 0;
}   //configure_port

auto Comm::getBaudrate() const -> int
{
    return _baudrate;
}

void Comm::setBaudrate(int baudrate)
{
    _baudrate = baudrate;
}

auto Comm::getPortname() const -> QString
{
    return _portname;
}

void Comm::setPortname(const QString &portname)
{
    _portname = portname;
}

void Comm::addTX(unsigned char byte)
{
    if (tx_index>=TX_BUFFER_SIZE)
    {
        return;
    }
    tx_buf[tx_index]=byte;
    tx_index++;
}

void Comm::writeToMCU()
{
    struct timeval timeout;
    timeout.tv_sec=1;
    timeout.tv_usec=0;

    if (tx_index>0)
    {
        write(fileDescriptor,tx_buf.constData(),tx_index);
        tx_index=0;
    }
}

void Comm::writeTxMessageToMCU(Message message) const
{
    struct timeval timeout;
    timeout.tv_sec=1;
    timeout.tv_usec=0;

    if (message.getSize() > 0)
    {
        write(fileDescriptor,message.getMessage(),message.getSize());
    }
}

auto Comm::readIncoming() -> int
{
    int rx_space = RX_BUFFER_SIZE - rx_index;
    int nBytes = read(fileDescriptor, &rx_buf[rx_index], rx_space);
    rx_index += nBytes;
    return nBytes;
}

auto Comm::nextByteAvailable() -> unsigned char
{
    if (reading_cursor < rx_index)
    {
        return 1;
    }
    rx_index = 0;
    reading_cursor = 0;
    return 0;
}

auto Comm::getRxByte() -> unsigned char
{
    unsigned char next_byte = rx_buf.at(reading_cursor); //[reading_cursor];
    reading_cursor++;
    return next_byte;
}

void Comm::closeSerial() const
{
    close(fileDescriptor);
}
