#include "encoder.h"
#include <QObject>
#include <QDebug>

/**
 * This class encapsulates the rotary knob behavior. It listens for changes on the A pin and the B pin and emits signals
 * when the knob is turned.
 */

Encoder::Encoder()
{
}

void Encoder::onPinAChange(unsigned char value)
{
    m_a_state = value;
    updateEncoder();
}

void Encoder::onPinBChange(unsigned char value)
{
    m_b_state = value;
    updateEncoder();
}

void Encoder::setState(unsigned char aState, unsigned char bState)
{
    m_a_state = aState;
    m_b_state = bState;
}

void Encoder::updateEncoder()
{
    int MSB = m_a_state;
    int LSB = m_b_state;

    int encoded = (MSB << 1) | LSB;
    int sum = (m_last_encoded << 2) | encoded;

    //The sum will look like [0b last_a_state last_b_state current_a_state current_b_state]
    if(sum == 0b1101 || sum == 0b0010) // 13 || 2
    {
        if (m_sum_0 == -1)
        {
            emit encoderIncrement(0);
            m_sum_0 = sum;
        }
        else if (sum != m_sum_0)
        {
            emit encoderIncrement(0); //emit 0 for -1
            m_sum_0 = sum;
        }
    }
    else if(sum == 0b1110 || sum == 0b0001) // 14 || 1
    {
        if (m_sum_1 == -1)
        {
            emit encoderIncrement(1);
            m_sum_1 = sum;
        }
        else if (sum != m_sum_1)
        {
            emit encoderIncrement(1); //emit 1 for +1
            m_sum_1 = sum;
        }
    }

    m_last_encoded = encoded;
}
