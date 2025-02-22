///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Inputs/ControllerAxisBinding.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::Binds
///////////////////////////////////////////////////////////////////////////////
namespace tkd::Binds
{

///////////////////////////////////////////////////////////////////////////////
Axis::Axis(
    Uint32 controllerId,
    sf::Joystick::Axis axisX,
    sf::Joystick::Axis axisY,
    float deadzone
)
    : InputBinding()
    , m_controller(controllerId)
    , m_axisX(axisX)
    , m_axisY(axisY)
    , m_deadzone(deadzone * .01f)
{}

///////////////////////////////////////////////////////////////////////////////
bool Axis::isPressed(void) const
{
    Vec2f value = getAnalogValue();

    return (
        std::abs(value.x) > m_deadzone ||
        std::abs(value.y) > m_deadzone
    );
}

///////////////////////////////////////////////////////////////////////////////
Vec2f Axis::getAnalogValue(void) const
{
    float x = sf::Joystick::getAxisPosition(m_controller, m_axisX) * .01f;
    float y = sf::Joystick::getAxisPosition(m_controller, m_axisY) * .01f;

    if (std::abs(x) < m_deadzone)
        x = 0.f;
    if (std::abs(y) < m_deadzone)
        y = 0.f;
    return (Vec2f(x, y));
}

///////////////////////////////////////////////////////////////////////////////
Uint32 Axis::getControllerId(void) const
{
    return (m_controller);
}

} // namespace tkd::Binds
