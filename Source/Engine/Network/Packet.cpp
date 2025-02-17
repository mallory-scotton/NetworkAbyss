///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Packet.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
void Packet::write(const String& value)
{
    Uint32 length = static_cast<Uint32>(value.size());
    this->write(length);
    if (m_pos + length > MAX_SIZE)
        throw std::out_of_range("Packet write overflow");
    std::memcpy(m_buffer.data() + m_pos, value.data(), length);
    m_pos += length;
}

///////////////////////////////////////////////////////////////////////////////
void Packet::write(const Packet::PlayerList& value)
{
    this->write(value.count);
    for (const auto& [id, position] : value.players) {
        this->write(id);
        this->write(position);
    }
}

///////////////////////////////////////////////////////////////////////////////
void Packet::read(String& value)
{
    Uint32 length;
    this->read(length);
    if (m_pos + length > MAX_SIZE)
        throw std::out_of_range("Packet read overflow");
    value.assign(
        reinterpret_cast<const char*>(m_buffer.data() + m_pos),
        length
    );
    m_pos += length;
}

///////////////////////////////////////////////////////////////////////////////
void Packet::read(Packet::PlayerList& value)
{
    this->read(value.count);
    for (Uint32 i = 0; i < value.count; i++) {
        int id;
        Vec2f position;
        this->read(id);
        this->read(position);
        value.players[id] = position;
    }
}

///////////////////////////////////////////////////////////////////////////////
const Byte* Packet::data(void) const
{
    return (m_buffer.data());
}

///////////////////////////////////////////////////////////////////////////////
Byte* Packet::data(void)
{
    return (m_buffer.data());
}

///////////////////////////////////////////////////////////////////////////////
Uint64 Packet::size(void) const
{
    return (m_pos);
}

///////////////////////////////////////////////////////////////////////////////
void Packet::clear(void)
{
    m_pos = 0;
}

///////////////////////////////////////////////////////////////////////////////
void Packet::serialize(void)
{
    m_pos = 0;
    std::visit([this](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        this->write(static_cast<Uint8>(m_data.index()));

        if constexpr (
            !std::is_same_v<T, Connect> &&
            !std::is_same_v<T, Disconnect>
        ) this->write(arg);
    }, m_data);
}

///////////////////////////////////////////////////////////////////////////////
void Packet::deserialize(void)
{
    constexpr std::size_t subTypeSize = std::variant_size_v<decltype(m_data)>;
    m_pos = 0;
    Uint8 index;
    this->read(index);

    if (index >= subTypeSize)
        throw std::out_of_range("Invalid variant type during deserialization");
    switch (index) {
        // Connect
        case 0: m_data = Connect{}; break;
        // Disconnect
        case 1: m_data = Disconnect{}; break;
        // PlayerMove
        case 2: {
            PlayerMove move;
            this->read(move.position);
            m_data = move;
            break;
        }
        // PlayerList
        case 3: {
            PlayerList list;
            this->read(list);
            m_data = list;
            break;
        }
        // PlayerJoined
        case 4: {
            PlayerJoined joined;
            read(joined.id);
            m_data = joined;
            break;
        }
        // PlayerLeft
        case 5: {
            PlayerLeft left;
            read(left.id);
            m_data = left;
            break;
        }
        // Unknown
        default:
            throw std::runtime_error(
                "Unknown packet type during deserialization");
    }
}

} // namespace tkd
