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

unsigned char Message::getCRC() const
{
    return m_crc;
}

unsigned char * Message::getMessage()
{
    return &(m_message.data())[0];
}

int Message::getSize() const
{
    return m_tx_size;
}

QString Message::toString()
{
    QString tmp = QString::fromStdString("");
    for (int i = 0; i < m_tx_size; i++)
    {
        tmp = tmp + QString::number(m_message.at(i)) + ", ";
    }
    return tmp;
}
