#include "Level1.hpp"
#include <string>
Level1::Level1(void)
{
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
}

int Level1::Run(sf::RenderWindow &window){
    //sf::Event Event;
    float shootTimer = 20.0f;
    int score = 0;
    Clock clock;
	float dt = 0.f;
	float dtMultiplier = 62.5f;
	//Intialize font
	Font font;
	font.loadFromFile("Fonts/verdanab.ttf");
	//init Textures
	Texture playerTex,backgroundTexture,backgroundTexture2;
    playerTex.loadFromFile("Textures/suttle5.png");
    Player player(&playerTex);
    float windowX = window.getSize().x;
    float windowY = window.getSize().y;
    backgroundTexture.loadFromFile("Textures/space3.jpg");
    backgroundTexture2.loadFromFile("Textures/space5.jpg");
    Background B(&backgroundTexture,windowX,windowY);
    Background B2(&backgroundTexture2,windowX,windowY);
    B2.img.setPosition(0,-600);
    //UI init
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 10.f);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(window.getSize().x / 3, window.getSize().y / 2);
	gameOverText.setString("GAME OVER!");
    Texture enemyTex;
    enemyTex.loadFromFile("Textures/enemysShipf.png");
    Text hpText;
	hpText.setFont(font);
	hpText.setCharacterSize(15);
	hpText.setFillColor(Color::White);
	scoreText.setPosition(10.f, 20.f);

	//Enemy init
	float enemySpawnTimer = 0.f;
	std::vector<Enemy> enemies;

	Text eHpText;
	eHpText.setFont(font);
	eHpText.setCharacterSize(12);
	eHpText.setFillColor(Color::White);
    Texture playerBulletTex;
    playerBulletTex.loadFromFile("Textures/laser_purple.png");
	// Start the game loop
    while (window.isOpen())
    {
        // Process events
       Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                window.close();
        }
        //If enter key is pressed go to menu
        if(Keyboard::isKeyPressed(Keyboard::Escape))
            return 0;
        if (player.HP >0)
		{
        //dt = 0,016 seconds / frame at 60fps
		dt = clock.restart().asSeconds();
            if (Keyboard::isKeyPressed(Keyboard::W))
                player.shape.move(0.f, -2.f );
			if (Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-2.f , 0.f);
			if (Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0.f, 2.f);
			if (Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(2.f , 0.f);

			hpText.setString("HP : " + std::to_string(player.HP) + "/" + std::to_string(player.HP_Max));

				if (player.shape.getPosition().x <= 0) //Left
                    player.shape.setPosition(0.f, player.shape.getPosition().y);
                if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
                    player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
                if (player.shape.getPosition().y <= 0) //Top
                    player.shape.setPosition(player.shape.getPosition().x, 0.f);
                if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
                    player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
                //Scrolling Backgroung
                B.img.move(0.0f,0.30f);
                B2.img.move(0.0f,0.30f);
                if (B.img.getPosition().y >= window.getSize().y ) //Bottom
                    B.img.setPosition(0.0f,-600.0f);
                if (B2.img.getPosition().y >= window.getSize().y ) //Bottom
                    B2.img.setPosition(0.0f,-600.0f);

            //Bullet update
            if (shootTimer < 15)
				shootTimer += 1.f *dt * dtMultiplier;

			if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 15) //Shooting
			{
				player.bullets.push_back(Bullet(&playerBulletTex, player.shape.getPosition()));
				shootTimer = 0; //reset timer
			}

			//Bullets
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				//Move
				player.bullets[i].shape.move(0.0f,-20.f * dt * dtMultiplier);

				//Out of window bounds
				if (player.bullets[i].shape.getPosition().x > window.getSize().x)
				{
					player.bullets.erase(player.bullets.begin() + i);
					break;
                }

				//Enemy collision
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
					{
						if (enemies[k].HP <= 1)
						{
							score += enemies[k].HP_Max;
							enemies.erase(enemies.begin() + k);
						}
						else
							enemies[k].HP--; //ENEMY TAKE DAMAGE

						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
				}
			}
			//Enemy
			if (enemySpawnTimer < 25)
				enemySpawnTimer += 1.f * dt * dtMultiplier;

			//enemy spawn
			if (enemySpawnTimer >= 25)
			{
				enemies.push_back(Enemy(&enemyTex, window.getSize().x));
				enemySpawnTimer = 0; //reset timer
			}

			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(0.0f,4.f * dt * dtMultiplier);

				if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
				{
					enemies.erase(enemies.begin() + i);
					break;
				}

				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + i);

					player.HP--; // PLAYER TAKE DAMAGE
					break;
				}
			}
			scoreText.setString("Scores : " + std::to_string(score));
			}
        // Clear screen
        window.clear();

        // Draw the sprite

        window.draw(B.img);
        window.draw(B2.img);
        window.draw(player.shape);
        //Bullets
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
            window.draw(player.bullets[i].shape);
		}
		//enemy
		for (size_t i = 0; i < enemies.size(); i++)
		{
			eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HP_Max));
			eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
			window.draw(eHpText);
			window.draw(enemies[i].shape);
		}

		//UI
		window.draw(scoreText);
		window.draw(hpText);
        if (player.HP <= 0)
			window.draw(gameOverText);

        // Update the window
        window.display();
    }

	//Never reaching this point normally, but just in case, exit the application
	return (-1);

    }
