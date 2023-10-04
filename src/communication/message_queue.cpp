#include "message_queue.h"

void MessageQueue::push(Message message)
{
    QMutexLocker lock(&m_mutex);
    if (m_crc_set.find(message.getCRC()) == m_crc_set.end()) {
        m_crc_set.insert(message.getCRC());
        m_queue.enqueue(message);
    }
    m_dataAvailable.wakeAll();
}

Message MessageQueue::pop()
{
    if (m_queue.isEmpty())
    {
        return Message();
    }

    Message m = m_queue.head();

    m_queue.dequeue();
    m_crc_set.erase(m.getCRC());

    return m;
}

bool MessageQueue::empty() const
{
    return m_queue.isEmpty();
}


int MessageQueue::size() const
{
    return m_queue.size();
}

void MessageQueue::lock()
{
    QMutexLocker lock(&m_mutex);
}

void MessageQueue::wait()
{
    m_dataAvailable.wait(&m_mutex);
}

void MessageQueue::wake()
{
    m_dataAvailable.wakeAll();
}
