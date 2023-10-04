#include "gpio_tests.h"
#include "src/gpio/gpio.h"
#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <QDebug>
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

#include <QtTest>

GPIOTests::GPIOTests(QObject *parent)
    :QObject(parent)
{
}

void GPIOTests::listenGPIO()
{

    auto current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto end = current + 15 * 1000;
    char edge[]="both";
    GPIO* gpio = new GPIO(93, edge, false);

    gpio->openFd();

    struct pollfd fdset[1];



    char buf[64];

    while(current < end)
    {
        current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        memset((void*)fdset, 0, 1);

        fdset[0].events = POLLPRI;
        fdset[0].fd = gpio->getFD();

        int rc = poll(fdset,1, 3 * 1000);

        if(rc < 0) {
            qDebug()<<"\npoll() failed!\n";
        }

        if (rc == 0)
        {
            qDebug()<< ".";
        }

        if (fdset[0].revents & POLLPRI)
        {
            lseek(fdset[0].fd, 0, SEEK_SET);
            int len = read(fdset[0].fd, buf, 64);
            if (len)
            {
                unsigned char result = buf[0] - '0';
                if((result | 1) == 1)
                {
                    emit knobSignal();

                }
            }
        }

        fflush(stdout);
        current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

}

void GPIOTests::countEdges()
{
    QSignalSpy gpioSpy(this, SIGNAL(knobSignal()));

    //gpioSpy.wait();
    listenGPIO();
    qDebug() << "Count: " <<gpioSpy.count();
    QVERIFY(gpioSpy.count() == 1001);


}

QTEST_MAIN(GPIOTests)
