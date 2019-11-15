#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include "Screen.hpp"
#include "Objects.hpp"

class menu : public Screen{
    private:
        int alpha_max;
        int alpha_div;
        bool playing;
    public:
        menu(void);
        virtual int Run(sf::RenderWindow &window);
};



#endif // MENU_HPP_INCLUDED
