///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Inputs/InputManager.hpp>
#include <Engine/Inputs/KeyBinding.hpp>
#include <Engine/Inputs/MouseBinding.hpp>
#include <Engine/Inputs/ControllerButtonBinding.hpp>
#include <Engine/Inputs/ControllerAxisBinding.hpp>
#include <Engine/Core/Renderer.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
#define HAS_FOCUS Renderer::getInstance()->getWindow().hasFocus()

///////////////////////////////////////////////////////////////////////////////
InputManager::InputManager(void)
{
    setupDefaultBindings();
    if (sf::Joystick::isConnected(0))
        setupControllerBindings(0);
}

///////////////////////////////////////////////////////////////////////////////
void InputManager::update(void)
{
    for (auto& [action, bindings] : m_bindings) {
        for (auto& binding : bindings) {
            binding->update();
        }
    }

    for (Uint32 i = 0; i < sf::Joystick::Count; ++i) {
        if (sf::Joystick::isConnected(i)) {
            if (!m_controllers[i]) {
                m_controllers[i] = true;
                onControllerConnected(i);
            }
        } else if (m_controllers[i]) {
            m_controllers[i] = false;
            onControllerDisconnected(i);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
bool InputManager::isActionPressed(GameAction action) const
{
    if (!HAS_FOCUS)
        return (false);
    auto it = m_bindings.find(action);
    if (it == m_bindings.end())
        return (false);
    for (const auto& binding : it->second) {
        if (binding->isPressed())
            return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
bool InputManager::isActionJustPressed(GameAction action) const
{
    if (!HAS_FOCUS)
        return (false);
    auto it = m_bindings.find(action);
    if (it == m_bindings.end())
        return (false);
    for (const auto& binding : it->second) {
        if (binding->isJustPressed())
            return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
bool InputManager::isActionJustReleased(GameAction action) const
{
    if (!HAS_FOCUS)
        return (false);
    auto it = m_bindings.find(action);
    if (it == m_bindings.end())
        return (false);
    for (const auto& binding : it->second) {
        if (binding->isJustReleased())
            return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
Vec2f InputManager::getActionAnalogValue(GameAction action) const
{
    if (!HAS_FOCUS)
        return (Vec2f::zeroVector);
    auto it = m_bindings.find(action);
    if (it == m_bindings.end())
        return (Vec2f::zeroVector);
    for (const auto& binding : it->second) {
        Vec2f value = binding->getAnalogValue();
        if (value.getAbsMax() > 0.f)
            return (value);
    }
    return (Vec2f::zeroVector);
}

///////////////////////////////////////////////////////////////////////////////
void InputManager::bindAction(GameAction action, UPtr<InputBinding> binding)
{
    m_bindings[action].push_back(std::move(binding));
}

///////////////////////////////////////////////////////////////////////////////
void InputManager::setupDefaultBindings(void)
{
    // Movement
    bindAction(GameAction::MOVE_LEFT,
        std::make_unique<Binds::Key>(sf::Keyboard::Key::A));
    bindAction(GameAction::MOVE_RIGHT,
        std::make_unique<Binds::Key>(sf::Keyboard::Key::D));
    bindAction(GameAction::MOVE_UP,
        std::make_unique<Binds::Key>(sf::Keyboard::Key::W));
    bindAction(GameAction::MOVE_DOWN,
        std::make_unique<Binds::Key>(sf::Keyboard::Key::S));

    // Actions
    bindAction(GameAction::JUMP,
        std::make_unique<Binds::Key>(sf::Keyboard::Key::Space));
    bindAction(GameAction::PAUSE,
        std::make_unique<Binds::Key>(sf::Keyboard::Key::Escape));
    bindAction(GameAction::SHOOT,
        std::make_unique<Binds::Mouse>(sf::Mouse::Button::Left));
}

///////////////////////////////////////////////////////////////////////////////
void InputManager::setupControllerBindings(Uint32 id)
{
    // Movement with analog stick
    bindAction(
        GameAction::MOVE_LEFT,
        std::make_unique<Binds::Axis>(
            id,
            sf::Joystick::Axis::X,
            sf::Joystick::Axis::Y
        )
    );
}

///////////////////////////////////////////////////////////////////////////////
void InputManager::onControllerConnected(Uint32 id)
{
    setupControllerBindings(id);
}

///////////////////////////////////////////////////////////////////////////////
void InputManager::onControllerDisconnected(Uint32 id)
{
    for (auto& [action, bindings] : m_bindings) {
        bindings.erase(
            std::remove_if(
                bindings.begin(),
                bindings.end(),
                [id](const auto& binding) {
                    auto* ctrl = dynamic_cast<Binds::Button*>(binding.get());
                    auto* axis = dynamic_cast<Binds::Axis*>(binding.get());
                    return (
                        (ctrl && ctrl->getControllerId() == id) ||
                        (axis && axis->getControllerId() == id)
                    );
                }
            ),
            bindings.end()
        );
    }
}

} // namespace tkd
