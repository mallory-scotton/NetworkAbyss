///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Core/State.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::States
///////////////////////////////////////////////////////////////////////////////
namespace tkd::States
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class Play : public Base
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void init(void) override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param deltaT
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void update(float deltaT) override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void render(void) override;
};

} // namespace tkd::States
