#include "brightness_manager.h"
#include <QDebug>

BrightnessManager::BrightnessManager(QObject *parent)
    : QObject(parent)
{
    m_file = "/sys/class/backlight/backlight/brightness";

    int max = getMax();
    if( max > 0 )
    {
        m_max = max;
    }

}

int BrightnessManager::getMax()
{
    QFile maxFile("/sys/class/backlight/backlight/max_brightness");
    if (maxFile.open(QIODevice::ReadOnly))
    {
        QString line = maxFile.readAll();
        if (!line.isNull())
        {
            return line.toInt();
        }
    }
    return -1;
}

int BrightnessManager::getMaxPercent()
{
    return m_max_percent;
}

int BrightnessManager::getMinPercent()
{
    return m_min_percent;
}

void BrightnessManager::changeBrightness(double percentage)
{
    if (m_max > 0)
    {
        int val = percentage * m_max;
        QFile file(m_file);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream stream (&file);
        stream << val;

        qInfo() << "NVENT" << "," << "BRIGHTNESS" << "," << "Update brightness to " + QString::number(val);
    }
}

double BrightnessManager::getBrightness()
{
    QFile maxFile(m_file);
    if (maxFile.open(QIODevice::ReadOnly))
    {
        QString line = maxFile.readAll();
        if (!line.isNull())
        {
            return line.toInt() / m_max * 100;
        }
    }
    return -1;
}
