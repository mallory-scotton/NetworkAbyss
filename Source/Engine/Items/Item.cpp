///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Items/Item.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Item::Item(const String& name, const String& description)
    : m_name(name)
    , m_description(description)
{}

///////////////////////////////////////////////////////////////////////////////
const String& Item::getName(void) const
{
    return (m_name);
}

///////////////////////////////////////////////////////////////////////////////
const String& Item::getDescription(void) const
{
    return (m_description);
}

} // namespace tkd
