#pragma once

#include <QObject>
#include <QtTest/QtTest>

class GPIOTests : public QObject
{
    Q_OBJECT
public:
    explicit GPIOTests(QObject *parent = nullptr);
private slots:
    void countEdges();

signals:
    void knobSignal();
private:
    void listenGPIO();
    int m_run;

};
