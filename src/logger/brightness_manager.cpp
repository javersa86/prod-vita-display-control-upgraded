#include "brightness_manager.h"
#include <QDebug>

BrightnessManager::BrightnessManager(QObject *parent)
    : QObject(parent)
{
    m_file = QString::fromStdString("/sys/class/backlight/backlight/brightness");

    int max = getMax();
    if( max > 0 )
    {
        m_max = max;
    }

}

auto BrightnessManager::getMax() -> int
{
    QFile maxFile(QString::fromStdString("/sys/class/backlight/backlight/max_brightness"));
    if (maxFile.open(QIODevice::ReadOnly))
    {
        QString line = QString::fromLatin1(maxFile.readAll());
        if (!line.isNull())
        {
            return line.toInt();
        }
    }
    return -1;
}

auto BrightnessManager::getMaxPercent() const -> int
{
    return m_max_percent;
}

auto BrightnessManager::getMinPercent() const -> int
{
    return m_min_percent;
}

void BrightnessManager::changeBrightness(double percentage)
{
    if (m_max > 0)
    {
        double val = percentage * m_max;
        QFile file(m_file);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream stream (&file);
        stream << val;

        qInfo() << "NVENT" << "," << "BRIGHTNESS" << "," << "Update brightness to " + QString::number(val);
    }
}

auto BrightnessManager::getBrightness() -> double
{
    QFile maxFile(m_file);
    if (maxFile.open(QIODevice::ReadOnly))
    {
        QString line = QString::fromLatin1(maxFile.readAll());
        if (!line.isNull())
        {
            return line.toInt() / m_max * m_max_percent;
        }
    }
    return -1;
}
