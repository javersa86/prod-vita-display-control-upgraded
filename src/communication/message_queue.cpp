#include "message_queue.h"

void MessageQueue::push(const Message &message)
{
    QMutexLocker lock(&m_mutex);
    if (m_crc_set.find(message.getCRC()) == m_crc_set.end()) {
        m_crc_set.insert(message.getCRC());
        m_queue.enqueue(message);
    }
    m_dataAvailable.wakeAll();
}

auto MessageQueue::pop() -> Message
{
    if (m_queue.isEmpty())
    {
        return {};
    }

    Message message = m_queue.dequeue();
    m_crc_set.erase(message.getCRC());

    return message;
}

auto MessageQueue::empty() const -> bool
{
    return m_queue.isEmpty();
}


auto MessageQueue::size() const -> int
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
