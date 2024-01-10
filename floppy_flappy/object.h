#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <thread>
#include <time.h>
#include <string>

//tests
#include <iostream>

using namespace std;

extern bool isPlaying;
extern int score;
extern sf::Text highscore;
extern sf::Text score_txt;

class Object
{
public:
	sf::Sprite sprite;
	float speed;
	Object(const char* path, float scale, float x, float y)
	{
		this->texture.loadFromFile(path);
		this->sprite.setTexture(this->texture);

		this->speed = 1.f;

		this->sprite.setScale(scale, scale);
		this->sprite.setOrigin(this->getSizeX() * .5, this->getSizeY() * .5);
		this->sprite.setPosition(x, y);
	}
	float getSizeX() { return this->sprite.getTexture()->getSize().x * this->sprite.getScale().x; };
	float getSizeY() { return this->sprite.getTexture()->getSize().y * this->sprite.getScale().y; };
	float getPosX() { return this->sprite.getPosition().x; }
	float getPosY() { return this->sprite.getPosition().y; }
private:
	sf::Texture texture;
};

class Player
{
public:
	struct Force {
		float x, y;
	};

	sf::Sprite sprite;
	Force force;
	bool move_block;

	//bool isColliding(Object* o);
	float get_gravity() { return this->gravity; }
	float get_speed() { return this->speed; }
	Force get_force() { return this->force; }
	float getSizeX() { return this->sprite.getTexture()->getSize().x* this->sprite.getScale().x; }
	float getSizeY() { return this->sprite.getTexture()->getSize().y* this->sprite.getScale().y; }
	float getPosX() { return this->sprite.getPosition().x; }
	float getPosY() { return this->sprite.getPosition().y; }
	Player(const char* path, float scale, float x, float y, float gravity = 0, float speed = 0)
	{
		this->gravity = gravity;
		this->speed = speed;
		this->force.y = 0.0f;
		this->force.x = 0.0f;

		this->texture.loadFromFile(path);
		this->sprite.setTexture(this->texture);

		this->sprite.setScale(scale, scale);
		this->sprite.setOrigin(this->getSizeX() * .5, this->getSizeY() * .5);
		this->sprite.setPosition(x, y);
		this->move_block = false;
	}
private:	
	sf::Texture texture;	
	
	//physics
	float gravity, speed;
};

void physics(Object* o, Player* p);
void inputs(Player* p);