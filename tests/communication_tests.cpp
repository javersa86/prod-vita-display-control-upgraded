#include "communication_tests.h"
#include "src/communication/api.h"

#include <QtTest>

CommunicationTests::CommunicationTests(QObject *parent)
    :QObject(parent)
{
}

void CommunicationTests::testFloatToBytes()
{
    QVERIFY(1 == 1);
}

//QTEST_MAIN(CommunicationTests)
