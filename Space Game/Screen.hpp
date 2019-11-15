#ifndef SCREEN_HPP_INCLUDED
#define SCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
using namespace sf;
class Screen
{
public :
    virtual int Run (RenderWindow &App) = 0;
};

#endif // SCREEN_HPP_INCLUDED
