///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Utils/Types.hpp>
#include <Engine/Utils/Vec2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class Renderer
{
private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    sf::RenderWindow m_window;      //<!
    sf::View m_view;                //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param dimension
    /// \param title
    ///
    ///////////////////////////////////////////////////////////////////////////
    Renderer(const Vec2u& dimension, const String& title);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void clear(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param drawable
    ///
    ///////////////////////////////////////////////////////////////////////////
    void draw(const sf::Drawable& drawable);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void display(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param view
    ///
    ///////////////////////////////////////////////////////////////////////////
    void setView(const sf::View& view);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    sf::RenderWindow& getWindow(void);
};

} // namespace tkd
