#ifndef OBJECTS_HPP_INCLUDED
#define OBJECTS_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include <vector>
using namespace sf;

class Objects{
       public:
        int HP;
        int HP_Max;
        //float speed;


        Sprite shape;
        void setHP(int HP){this->HP = HP;}
        int getHP() const {return this->HP;}
        void setHP_Max(int HP){this->HP_Max = HP;}
        int getHP_Max() const {return this->HP_Max;}
        //void setSpeed(float speed){this->speed=speed;}
       // float getSpeed() const {return this->speed;}

};

class Bullet : public Objects{
public:
    Bullet(Texture *texture, Vector2f pos){
        this->HP = 0;
        this->HP_Max = 0;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.07f, 0.07f);
        this->shape.setPosition(pos);
    }
    ~Bullet(){}
};
class Player : public Objects{
public:
    std::vector<Bullet> bullets;
    Player(Texture *texture){
        this->HP = 10;
        this->HP_Max = 10;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.5f, 0.5f);
        this->shape.setPosition(350.0f,500.0f);
    }
    ~Player(){}
};

class Enemy : public Objects{
public:
    Enemy(Texture *texture, float windowSize){
        this->HP = 2;
        this->HP_Max = 2;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.5f, 0.5f);
        this->shape.setPosition(rand()% (int)(windowSize - this->shape.getGlobalBounds().width),0);
    }
    ~Enemy(){}
};


class Background {
public:
    Sprite img;
    Background(Texture *texture,float x,float y){
        img.setTexture(*texture);
        float scaleX = x/img.getGlobalBounds().width;
        float scaleY = y/img.getGlobalBounds().height;
        img.scale(scaleX, scaleY);
    }
    bool touchBounds(){

    }
};
#endif // OBJECTS_HPP_INCLUDED
