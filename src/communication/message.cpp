#include "message.h"

Message::Message(const unsigned char* data, unsigned char crc, int tx_size)
{
    int index = 0;

    m_message[index] = START_CHAR;
    index = index + 1;

    for (int i = 0; i < tx_size; i++)
    {
        m_message[index] = data[i];
        index = index + 1;
    }

    m_message[index] = crc;

    m_crc = crc;
    m_tx_size = tx_size + 2;
}

auto Message::getCRC() const -> unsigned char
{
    return m_crc;
}

auto Message::getMessage() -> unsigned char *
{
    return &(m_message.data())[0];
}

auto Message::getSize() const -> int
{
    return m_tx_size;
}

auto Message::toString() -> QString
{
    QString tmp = QString::fromStdString("");
    for (int i = 0; i < m_tx_size; i++)
    {
        tmp = tmp + QString::number(m_message.at(i)) + ", ";
    }
    return tmp;
}
