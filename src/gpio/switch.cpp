#include "switch.h"


void Switch::onPinChange(unsigned char value)
{
    if(value == 0 && m_state == 1 && m_ignore == 0)
    {
        emit push();
    }
    m_ignore = 0;
    m_state = value;
}

void Switch::setState(unsigned char value)
{
    m_state = value;
    m_ignore = value;
}
