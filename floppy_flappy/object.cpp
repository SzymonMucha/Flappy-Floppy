#include "object.h"

sf::Text highscore;
sf::Text score_txt;
int score = 0;

bool isPlaying = true;

void physics(Object* o, Player* p)
{
	srand(time(NULL));
	while (isPlaying)
	{
		//floppy physics
		if (p->force.y < p->get_gravity())
		{
			p->force.y += .1f;
		}
		if (p->force.x < 0.0)
		{
			p->force.x += .1f;
		}
		if (p->force.x > 0.0)
		{
			p->force.x -= .1f;
		}
		
		//brick move loop
		if (o->sprite.getPosition().x < -60)
		{
			o->sprite.setPosition(660, (rand() % 2 ? 230 : -71) + (rand() % 100));
			(o->speed <= 15.f) ? o->speed += .5f : 0;
			score++;
			score_txt.setString(string("Present score: ") + to_string(score));
		}

		//collisions
		if (p->sprite.getPosition().y <= o->sprite.getPosition().y + 175 && p->sprite.getPosition().y >= o->sprite.getPosition().y - 78
			&& p->sprite.getPosition().x >= o->sprite.getPosition().x - 60 && p->sprite.getPosition().x <= o->sprite.getPosition().x - 30
			&& o->sprite.getPosition().x >= 0 && o->sprite.getPosition().x <= 600)
		{
			p->force.x = -(o->speed);
		}
		if (p->sprite.getPosition().y <= o->sprite.getPosition().y + 175 && p->sprite.getPosition().y >= o->sprite.getPosition().y - 78
			&& p->sprite.getPosition().x >= o->sprite.getPosition().x -50 && p->sprite.getPosition().x <= o->sprite.getPosition().x + 60
			&& o->sprite.getPosition().x >= 0 && o->sprite.getPosition().x <= 600)
		{
			p->force.x = 1.5;
			p->force.y = 0;
			p->move_block = true;
		}
		else
			p->move_block = false;
		if (p->sprite.getPosition().x < -32)
		{
			isPlaying = false;
		}
		if (p->sprite.getPosition().x > 600)
		{
			p->force.x = -0.01;
		}
		if (p->sprite.getPosition().y <= 0)
		{
			p->force.y = p->get_speed();
		}
		if (p->sprite.getPosition().y >= 350)
		{
			
			p->force.y = -(p->get_speed());
		}

		this_thread::sleep_for(16ms);
	}
}

void inputs(Player* p)
{
	while (isPlaying)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !p->move_block)
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
			p->force.y = -(p->get_speed());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !p->move_block)
		{
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
			p->force.y = (p->get_speed());
		}
		this_thread::sleep_for(16ms);
		cout << p->force.x <<endl;
	}
}
/*
void Object::move_left()
{	
	srand(time(NULL));
	while (isPlaying)
	{
		this->sprite.move(-this->speed, 0.0f);
		this_thread::sleep_for(0.001ms);

		if (this->sprite.getPosition().x < -60)
		{
			this->sprite.setPosition(660, (rand() % 2 ? 230 : -71) + (rand() % 100));
			(speed <= 1.5f) ? this->speed += 0.05f : 0;
			score++;
			score_txt.setString(string("Present score: ") + to_string(score));
		}
	}
}

void collision(Object* o, Player* p)
{
	while (isPlaying)
	{
		if (p->sprite.getPosition().y <= o->sprite.getPosition().y + 175 && p->sprite.getPosition().y >= o->sprite.getPosition().y -78
			&& p->sprite.getPosition().x >= o->sprite.getPosition().x -60 && p->sprite.getPosition().x <= o->sprite.getPosition().x -35
			&& o->sprite.getPosition().x >= 0 && o->sprite.getPosition().x <= 600)
		{
			p->force.x = -(o->speed);
		}
		if (p->sprite.getPosition().y <= o->sprite.getPosition().y + 175 && p->sprite.getPosition().y >= o->sprite.getPosition().y - 78
			&& p->sprite.getPosition().x >= o->sprite.getPosition().x - 40 && p->sprite.getPosition().x <= o->sprite.getPosition().x + 60
			&& o->sprite.getPosition().x >= 0 && o->sprite.getPosition().x <= 600)
		{
			p->force.x = 0.05;
			p->force.y = 0;
		}
		if (p->sprite.getPosition().x < -70)
		{
			isPlaying = false;
		}
	}
}*/