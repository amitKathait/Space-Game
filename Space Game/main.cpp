//#include "Objects.hpp"
#include <iostream>
#include <vector>
#include "Views.hpp"
int main()
{   srand(time(NULL));
    // Create the main window
    RenderWindow window(VideoMode(800, 600), "Space Game");
    window.setFramerateLimit(200);
   //Applications variables
	std::vector<Screen*> Screens;
	menu M;
	Screens.push_back(&M);
	Level1 lvl1;
	Screens.push_back(&lvl1);
	int screen = 0;
    //Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}
    return EXIT_SUCCESS;
}
