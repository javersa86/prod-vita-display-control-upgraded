#include "knob.h"
#include "gpio.h"
#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <QDebug>


Knob::Knob(uint pin_a, uint pin_b, uint pin_switch)
{
    char edge[]="both";
    m_pinA= new GPIO{pin_a, edge, false};
    m_pinB = new GPIO{pin_b, edge, false};
    m_pinButton = new GPIO{pin_switch, edge, false};

    button = new Switch();

    encoder = new Encoder();


    connect(encoder,&Encoder::encoderIncrement,
            this, &Knob::onEncoderIncrement);

    connect(button,&Switch::push,
            this, &Knob::onButtonPush);
}

void Knob::run()
{
        struct pollfd fdset[4];
        int nfds = 4;
        int rc;
        int MAX_BUF = 64;
        char buf[MAX_BUF];
        int len;

        m_pinA->openFd();
        m_pinB->openFd();
        m_pinButton->openFd();

        button->setState(m_pinButton->getValue());
        encoder->setState(m_pinA->getValue(),m_pinB->getValue());

        while(m_running)
        {

            memset((void*)fdset, 0, sizeof(fdset));

            fdset[0].fd = m_pinA->getFD();
            fdset[0].events = POLLPRI;

            fdset[1].fd = m_pinB->getFD();
            fdset[1].events = POLLPRI;

            fdset[2].fd = m_pinButton->getFD();
            fdset[2].events = POLLPRI;

            rc = poll(fdset,nfds, 3 * 1000);

            if(rc < 0) {
                qDebug()<<"\npoll() failed!\n";
            }

            if (rc == 0)
            {
                //No knob changes
            }

            if (fdset[0].revents & POLLPRI)
            {
                lseek(fdset[0].fd, 0, SEEK_SET);
                len = read(fdset[0].fd, buf, MAX_BUF);
                if (len)
                {
                    unsigned char result = buf[0] - '0';
                    if((result | 1) == 1)
                    {
                        encoder->onPinAChange(result);
                    }
                }
            }

            if (fdset[1].revents & POLLPRI)
            {
                lseek(fdset[1].fd, 0, SEEK_SET);
                len = read(fdset[1].fd, buf, MAX_BUF);
                if (len)
                {
                    unsigned char result = buf[0] - '0';
                    if((result | 1) == 1)
                    {
                        encoder->onPinBChange(result);
                    }
                }
            }

            if (fdset[2].revents & POLLPRI)
            {
                lseek(fdset[2].fd, 0, SEEK_SET);
                len = read(fdset[2].fd, buf, MAX_BUF);
                if (len)
                {
                    unsigned char result = buf[0] - '0';
                    if((result | 1) == 1)
                    {
                        button->onPinChange(result);
                    }
                    msleep(75);
                }
            }

            fflush(stdout);
        }
}

void Knob::listen(unsigned char listen)
{
    m_running = listen;
    if(listen) start();
    else exit();
}

void Knob::onButtonPush()
{
    if(m_running) Q_EMIT buttonPush();
}

void Knob::onEncoderIncrement(unsigned char value)
{
    if (m_running) Q_EMIT encoderIncrement((int)(value * 2) - 1);
}
