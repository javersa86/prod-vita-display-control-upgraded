#include <QtDebug>

#include "mock_api.h"

/**
 * @brief MockApi::MockApi Connection to mock API for testing
 * @param parent
 */
MockApi::MockApi(QObject *parent)
    : QObject(parent)
{
    connect(&m_updateTimer, &QTimer::timeout,
            this, &MockApi::sendUpdates);
    m_updateTimer.start(1000);
}

/**
 * @brief MockApi::receiveSettingsUpdate Update mock API
 * @param id
 * @param value
 */
void MockApi::receiveSettingsUpdate(int id, int value)
{
    qDebug() << "@@@ MockApi::receiveSettingsUpdate: " << id << value;
    m_valueMap.insert(id, value);
}

/**
 * @brief MockApi::sendUpdates Emits signal changes to mock API
 */
void MockApi::sendUpdates()
{
    auto pos = m_valueMap.begin();
    while (pos != m_valueMap.end())
    {
        qDebug() << "@@@ MockApi::settingsConfirmationSent: " << pos.key() << pos.value();
        emit settingsConfirmationSent(pos.key(), pos.value());
        pos = m_valueMap.erase(pos);
    }
}
