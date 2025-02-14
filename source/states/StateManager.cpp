///////////////////////////////////////////////////////////////////////////////
///
/// MIT License
///
/// Copyright(c) 2025 TekyoDrift
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following coditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software?
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "states/StateManager.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
StateManager::StateManager(
    sf::RenderWindow& window,
    Client* client,
    bool* debug
)
    : m_window(window)
    , m_client(client)
    , m_debug(debug)
{}

///////////////////////////////////////////////////////////////////////////////
void StateManager::push(State state)
{
    if (!state)
        return;
    state->m_manager = this;
    state->m_window = &m_window;
    state->m_client = m_client;
    state->m_debug = m_debug;
    state->init();
    m_states.push(std::move(state));
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::pop(void)
{
    if (!m_states.empty())
        m_states.pop();
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::change(State state)
{
    this->pop();
    this->push(std::move(state));
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::handleEvent(sf::Event event)
{
    if (!m_states.empty())
        m_states.top()->handleEvent(event);
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::handlePacket(Packet packet)
{
    if (!m_states.empty())
        m_states.top()->handlePacket(packet);
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::update(float deltaT)
{
    if (!m_states.empty())
        m_states.top()->update(deltaT);
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::render(void)
{
    if (!m_states.empty())
        m_states.top()->render();
}

///////////////////////////////////////////////////////////////////////////////
bool StateManager::empty(void) const
{
    return (m_states.empty());
}

} // namespace tkd
