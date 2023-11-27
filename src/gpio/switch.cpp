#include "switch.h"
#include <QObject>
#include <QDebug>

Switch::Switch()
{
}

void Switch::onPinChange(unsigned char value)
{
    if(!value && m_state && !m_ignore)
    {
        Q_EMIT push();
    }
    m_ignore = 0;
    m_state = value;
}

void Switch::setState(unsigned char value)
{
    m_state = value;
    m_ignore = value;
}
