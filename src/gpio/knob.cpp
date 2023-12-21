#include "knob.h"

Knob::Knob(uint pin_a, uint pin_b, uint pin_switch) : button(new Switch()), encoder(new Encoder())
{
    const int edge_len = 5;
    std::array<char, edge_len> edge = {'b', 'o', 't', 'h', '\0'};

    m_pinA = std::unique_ptr<GPIO>(new GPIO(pin_a, edge.data(), false));
    m_pinB = std::unique_ptr<GPIO>(new GPIO(pin_b, edge.data(), false));
    m_pinButton = std::unique_ptr<GPIO>(new GPIO(pin_switch, edge.data(), false));


    connect(encoder,&Encoder::encoderIncrement,
            this, &Knob::onEncoderIncrement);

    connect(button,&Switch::push,
            this, &Knob::onButtonPush);
}

void Knob::run()
{
    std::array<pollfd, 4> fdset{};
    int nfds = 4;
    int rcProcessPoll = -1;
    const int timeout_count = 1000;
    //char buf[MAX_BUF];
    std::vector<char> buf(MAX_BUF);
    int len = 0;

    m_pinA->openFd();
    m_pinB->openFd();
    m_pinButton->openFd();

    button->setState(m_pinButton->getValue());
    encoder->setState(m_pinA->getValue(), m_pinB->getValue());

    while(m_running)
    {
        memset((void*)fdset.data(), 0, sizeof(fdset));

        fdset[0].fd = m_pinA->getFD();
        fdset[0].events = POLLPRI;

        fdset[1].fd = m_pinB->getFD();
        fdset[1].events = POLLPRI;

        fdset[2].fd = m_pinButton->getFD();
        fdset[2].events = POLLPRI;

        rcProcessPoll = poll(fdset.data(), nfds, 3 * timeout_count);

        if(rcProcessPoll < 0) {
            qDebug()<<"\npoll() failed!\n";
        }

        if ((fdset[0].revents & POLLPRI) != 0)
        {
            lseek(fdset[0].fd, 0, SEEK_SET);
            len = read(fdset[0].fd, buf.data(), MAX_BUF);

            if (len > 0)
            {
                resultPinA(buf[0] - '0');
            }
        }

        if ((fdset[1].revents & POLLPRI) != 0)
        {
            lseek(fdset[1].fd, 0, SEEK_SET);
            len = read(fdset[1].fd, buf.data(), MAX_BUF);

            if (len > 0)
            {
                resultPinB(buf[0] - '0');
            }
        }

        const unsigned long milliseconds = 75;
        if ((fdset[2].revents & POLLPRI) != 0)
        {
            lseek(fdset[2].fd, 0, SEEK_SET);
            len = read(fdset[2].fd, buf.data(), MAX_BUF);

            if (len > 0)
            {
                resultPinButton(buf[0] - '0');
                msleep(milliseconds);
            }
        }

        fflush(stdout);
    }
}

void Knob::resultPinA(unsigned char result)
{
    if((result | 1) == 1)
    {
        encoder->onPinAChange(result);
    }
}

void Knob::resultPinB(unsigned char result)
{
    if((result | 1) == 1)
    {
        encoder->onPinBChange(result);
    }
}

void Knob::resultPinButton(unsigned char result)
{
    if((result | 1) == 1)
    {
        button->onPinChange(result);
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
