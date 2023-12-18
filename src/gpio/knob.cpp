#include "knob.h"

Knob::Knob(uint pin_a, uint pin_b, uint pin_switch, char* edge) :
      m_pinA(new GPIO{pin_a, edge, false}),
      m_pinB(new GPIO{pin_b, edge, false}),
      m_pinButton(new GPIO{pin_switch, edge, false}),
      button(new Switch()),
      encoder(new Encoder())
{
    connect(encoder,&Encoder::encoderIncrement,
            this, &Knob::onEncoderIncrement);

    connect(button,&Switch::push,
            this, &Knob::onButtonPush);
}

void Knob::run()
{
        int nfds = 4;
        int rcProcessPoll = -1;
        const int timeout_count = 1000;

        m_pinA->openFd();
        m_pinB->openFd();
        m_pinButton->openFd();

        button->setState(m_pinButton->getValue());
        encoder->setState(m_pinA->getValue(), m_pinB->getValue());

        while(m_running)
        {
            memset((void*)fdset, 0, sizeof(fdset));
            //memset(buf, 0, sizeof(buf));

            fdset[0].fd = m_pinA->getFD();
            fdset[0].events = POLLPRI;

            fdset[1].fd = m_pinB->getFD();
            fdset[1].events = POLLPRI;

            fdset[2].fd = m_pinButton->getFD();
            fdset[2].events = POLLPRI;

            rcProcessPoll = poll(fdset, nfds, 3 * timeout_count);

            if(rcProcessPoll < 0) {
                qDebug()<<"\npoll() failed!\n";
            }

            pollPinA(fdset,buf);
            pollPinB(fdset,buf);
            pollPinSwitch(fdset,buf);

            fflush(stdout);
        }
}

void Knob::pollPinA(pollfd *fdset, char *buf)
{
    if (fdset[0].revents & POLLPRI)
    {
        lseek(fdset[0].fd, 0, SEEK_SET);
        int len = read(fdset[0].fd, buf, MAX_BUF);

        if (len > 0)
        {
            unsigned char result = buf[0] - '0';
            if((result | 1) == 1)
            {
                encoder->onPinAChange(result);
            }
        }
    }
}

void Knob::pollPinB(pollfd *fdset, char *buf)
{
    if (fdset[1].revents & POLLPRI)
    {
        lseek(fdset[1].fd, 0, SEEK_SET);
        int len = read(fdset[1].fd, buf, MAX_BUF);

        if (len > 0)
        {
            unsigned char result = buf[0] - '0';
            if((result | 1) == 1)
            {
                encoder->onPinBChange(result);
            }
        }
    }
}

void Knob::pollPinSwitch(pollfd *fdset, char *buf)
{
    const unsigned long milliseconds = 75;
    if (fdset[2].revents & POLLPRI)
    {
        lseek(fdset[2].fd, 0, SEEK_SET);
        int len = read(fdset[2].fd, buf, MAX_BUF);

        if (len > 0)
        {
            unsigned char result = buf[0] - '0';
            if((result | 1) == 1)
            {
                button->onPinChange(result);
            }
            msleep(milliseconds);
        }
    }
}

void Knob::listen(unsigned char listen)
{
    m_running = listen == 1;
    if (m_running)
    {
        start();
    }
    else
    {
        exit();
    }
}

void Knob::onButtonPush()
{
    if(m_running)
    {
        emit buttonPush();
    }
}

void Knob::onEncoderIncrement(unsigned char value)
{
    if (m_running)
    {
        emit encoderIncrement((int) (value * 2) - 1);
    }
}
