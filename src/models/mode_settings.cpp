#include "mode_settings.h"

ModeSetting::ModeSetting()
{

}

ModeSetting::ModeSetting(int id, int min, int max, int step)
    : m_id(id)
    , m_min(min)
    , m_max(max)
    , m_step(step)
{
}

void ModeSetting::value(int value)
{
    m_value = value;
}

int ModeSetting::value() const
{
    return m_value;
}

int ModeSetting::id() const
{
    return m_id;
}

int ModeSetting::min() const
{
    return m_min;
}

int ModeSetting::max() const
{
    return m_max;
}

int ModeSetting::step() const
{
    return m_step;
}
