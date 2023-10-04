#pragma once

#include <QObject>
#include <QtTest/QtTest>

#include "src/warnings/warning_manager.h"

class WarningTests : public QObject
{
    Q_OBJECT
public:
    explicit WarningTests(QObject *parent = nullptr);


private slots:

private:
    QVector<int> m_fake_warning_1;

};
