///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Packet.hpp>
#include <stdexcept>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Packet::Packet(void)
{
    this->clear();
}

///////////////////////////////////////////////////////////////////////////////
Packet::Packet(Type type)
{
    this->clear();
    *this << type;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Packet::Packet(Type type, const T& data)
{
    this->clear();
    *this << type;
    *this << data;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Packet& Packet::operator<<(const T& value)
{
    if (m_wpos + sizeof(T) > MAX_SIZE)
        throw std::out_of_range("Packet write overflow");
    std::memcpy(m_data.data() + m_wpos, &value, sizeof(T));
    m_wpos += sizeof(T);
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
Packet& Packet::operator<<(const String& value)
{
    *this << static_cast<Uint32>(value.size());
    if (m_wpos + value.size() > MAX_SIZE)
        throw std::out_of_range("Packet write overflow");
    std::memcpy(m_data.data() + m_wpos, value.data(), value.size());
    m_wpos += value.size();
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Packet& Packet::operator<<(const Vec2<T>& value)
{
    *this << value.x;
    *this << value.y;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Packet& Packet::operator>>(T& value)
{
    if (m_rpos + sizeof(T) > MAX_SIZE)
        throw std::out_of_range("Packet read overflow");
    std::memcpy(&value, m_data.data() + m_rpos, sizeof(T));
    m_rpos += sizeof(T);
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
Packet& Packet::operator>>(String& value)
{
    Uint32 size;
    *this >> size;
    if (m_rpos + size > MAX_SIZE)
        throw std::out_of_range("Packet read overflow");
    value.assign(reinterpret_cast<const char*>(m_data.data() + m_rpos), size);
    m_rpos += size;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Packet& Packet::operator>>(Vec2<T>& value)
{
    *this >> value.x;
    *this >> value.y;
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
const Byte* Packet::data(void) const
{
    return (m_data.data());
}

///////////////////////////////////////////////////////////////////////////////
Byte* Packet::data(void)
{
    return (m_data.data());
}

///////////////////////////////////////////////////////////////////////////////
Uint64 Packet::size(void) const
{
    return (m_wpos);
}

///////////////////////////////////////////////////////////////////////////////
void Packet::clear(void)
{
    m_data.fill(0);
    m_rpos = 0;
    m_wpos = 0;
}

} // namespace tkd
