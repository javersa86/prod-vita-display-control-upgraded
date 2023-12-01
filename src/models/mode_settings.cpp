#include "mode_settings.h"

ModeSetting::ModeSetting(int mode_id, int min, int max, int step)
    : m_id(mode_id)
    , m_min(min)
    , m_max(max)
    , m_step(step)
{
}

void ModeSetting::value(int value)
{
    m_value = value;
}

auto ModeSetting::value() const -> int
{
    return m_value;
}

auto ModeSetting::id() const -> int
{
    return m_id;
}

auto ModeSetting::min() const -> int
{
    return m_min;
}

auto ModeSetting::max() const -> int
{
    return m_max;
}

auto ModeSetting::step() const -> int
{
    return m_step;
}
