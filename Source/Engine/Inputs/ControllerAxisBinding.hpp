///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Inputs/InputBinding.hpp>
#include <SFML/Window.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::Binds
///////////////////////////////////////////////////////////////////////////////
namespace tkd::Binds
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class Axis : public InputBinding
{
private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    Uint32 m_controller;            //<!
    sf::Joystick::Axis m_axisX;     //<!
    sf::Joystick::Axis m_axisY;     //<!
    float m_deadzone;               //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param controllerId
    /// \param axisX
    /// \param axisY
    /// \param deadzone
    ///
    ///////////////////////////////////////////////////////////////////////////
    Axis(
        Uint32 controllerId,
        sf::Joystick::Axis axisX,
        sf::Joystick::Axis axisY,
        float deadzone = 20.f
    );

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool isPressed(void) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    Vec2f getAnalogValue(void) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    Uint32 getControllerId(void) const;
};

} // namespace tkd::Binds
