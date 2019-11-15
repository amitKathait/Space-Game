#ifndef LEVEL1_HPP_INCLUDED
#define LEVEL1_HPP_INCLUDED

#include "Screen.hpp"
#include "Objects.hpp"

class Level1 : public Screen{
    private:
        int alpha_max;
        int alpha_div;
        bool playing;
    public:
        Level1(void);
        virtual int Run(sf::RenderWindow &window);

    };


#endif // LEVEL1_HPP_INCLUDED
