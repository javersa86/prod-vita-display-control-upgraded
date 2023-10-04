#pragma once

#include <QObject>

class CommunicationTests : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationTests(QObject *parent = nullptr);
    void testFloatToBytes();

};
