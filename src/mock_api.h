#pragma once

#include <QMap>
#include <QObject>
#include <QTimer>

/**
 * @brief The MockApi class
 */
class MockApi : public QObject
{
    Q_OBJECT
public:
    explicit MockApi(QObject *parent = nullptr);

public slots:
    void receiveSettingsUpdate(int id, int value);

signals:
    void settingsConfirmationSent(int id, int value);

private slots:
    void sendUpdates();

private:
    QTimer m_updateTimer;
    QMap<int, int> m_valueMap;
};
