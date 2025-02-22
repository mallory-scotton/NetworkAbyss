///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Items/Item.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::Items
///////////////////////////////////////////////////////////////////////////////
namespace tkd::Items
{

class ForbiddenMask : public Item
{
public:
    ForbiddenMask(void)
        : Item(
            "Forbidden Mask",
            "You got promoted! Enhance your stats in all areas."
        )
    {
        m_effects = {
            Effect(Effect::Type::WeaponDamage, .15f),
            Effect(Effect::Type::MovementSpeed, .1f),
            Effect(Effect::Type::RateOfFire, .1f)
        };
    }
};

} // namespace tkd::Items
