#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"map.h"
#include"view.h"
#include<iostream>
#include <chrono>
#include<cmath>


using namespace sf;
enum Directions
{
	right, left, up, down
};
class Player
{
private:
	float x, y = 0;

public:
	int playerscore;
	float w, h, dx, dy, speed = 0;
	int dir = 0, health;
	bool isalive;
	String File;
	Image img;
	Texture texture;
	Sprite spr;
	Player()
	{

	}
	void set_par(String FIle, int x, int y, float h, float w)
	{
		playerscore = 0;
		File = FIle;
		this->x = x, this->y = y, this->h = h, this->w = w;
		img.loadFromFile("images/" + File);
		img.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(img);
		spr.setTexture(texture);
		spr.setTextureRect(IntRect(this->x, this->y, this->w, this->h));
	}
	float getPlayerCoordinateX()
	{
		return x;
	}
	float getPlayerCoordinateY()
	{
		return y;
	}
	void update(float time)
	{
		
		switch (dir)
		{
		case right:
			dx = speed, dy = 0; break;
		case left:
			dx = -speed, dy = 0; break;
		case up:
			dx = 0, dy = -speed; break;
		case down:
			dx = 0, dy = speed; break;

		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		spr.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
		{
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
					{
						y = i * 32 - h;

					}
					if (dy < 0)
					{
						y = i * 32 + 32;

					}
					if (dx > 0)
					{
						x = j * 32 - w;

					}
					if (dx < 0)
					{
						x = j * 32 + 32;

					}
				}

				if (TileMap[i][j] == 's')
				{
					playerscore++;
					TileMap[i][j] = ' ';

				}
				if (TileMap[i][j] == 'c')
				{
					health += 50;
					TileMap[i][j] = ' ';

				}
				if (TileMap[i][j] == 'p')
				{
					health -= 50;

					TileMap[i][j] = ' ';

				}
			}
		}
	}
private:

};
class Ball
{
private:
	float x, y = 0;
public:
	bool isfree = true;
	float w, h, dx, dy, speed = 0;
	int dir = 0;
	String File;
	Image img;
	Texture texture;
	Sprite spr;
	float getCoordinateX()
	{
		return x;
	}
	float getCoordinateY()
	{
		return y;
	}

	Ball(String FIle, int x, int y, float h, float w)
	{

		File = FIle;
		this->x = x, this->y = y, this->h = h, this->w = w;
		img.loadFromFile("images/ball/" + File);

		texture.loadFromImage(img);
		spr.setTexture(texture);
		spr.setTextureRect(IntRect(this->x, this->y, this->w, this->h));
	}
	void set_position(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void update(float time, float p_x, float p_y, float p_dx, float p_dy, float speed)
	{
		if(isfree)
		{ 
		switch (dir)
		{
		case right:
			dx = this->speed, dy = 0; break;
		case left:
			dx = -this->speed, dy = 0; break;
		case up:
			dx = 0, dy = -this->speed; break;
		case down:
			dx = 0, dy = this->speed; break;

		}
		x += dx * time;
		y += dy * time;
		this->speed = 0;

		spr.setPosition(x, y);

		ball_physics(time, p_x, p_y, p_dx, p_dy, speed);

		}
		else
		{
			if (p_dy > 0)
			{
				dir = down;
				y = p_y+85;
				x = p_x+32;
			}
			if (p_dy < 0)
			{
				dir = up;
				
				y = p_y- 15;
				x = p_x + 32;
			}
			if (p_dx > 0)
			{
				dir = left;
				y = p_y + 60;
				x = p_x + 70;
			}
			if (p_dx < 0)
			{
				dir = left;
				y = p_y + 60;
				x = p_x - 10;
			}
			
			
			
			spr.setPosition(x ,y);
		}

	}
	void ball_physics(float time, float p_x, float p_y, float p_dx, float p_dy, float speed)
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
		{
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
					{
						y = i * 32 - h * 3;

					}
					if (dy < 0)
					{
						y = i * 32 + 32 * 3;

					}
					if (dx > 0)
					{
						x = j * 32 - w * 3;

					}
					if (dx < 0)
					{
						x = j * 32 + 32 * 3;

					}
				}
			}
		}
		if (abs((x - 30) - (p_x)) < 35 &&abs(((y - 35) - (p_y))) < 45)
		{


			if (p_dy > 0)
			{

				dir = down;
				y += dy * speed * time;

			}
			if (p_dy < 0)
			{
				dir = up;
				y += dy * speed * time;



			}
			if (p_dx > 0)
			{
				dir = right;
				x += speed * time;


			}
			if (p_dx < 0)
			{
				dir = left;

				x += dx * speed * time;

			}

			this->speed = speed;
		}
	}
};
class Character
{
public:
	Character(String FIle, int x, int y, float h, float w, int CurrentFrameMax, double speed, float left_anim_x, float right_anim_x, float up_anim_x, float down_anim_x, float left_anim_y, float right_anim_y, float up_anim_y, float down_anim_y)
	{
		p.set_par(FIle, x, y, h, w);
		this->CurrentFrameMax = CurrentFrameMax;
		this->speed = speed;
		this->right_anim_x = right_anim_x;
		this->left_anim_x = left_anim_x;
		this->up_anim_x = up_anim_x;
		this->down_anim_x = down_anim_x;
		this->right_anim_y = right_anim_y;
		this->left_anim_y = left_anim_y;
		this->up_anim_y = up_anim_y;
		this->down_anim_y = down_anim_y;
	}
	
	void set_speed(double speed)
	{
		this->speed = speed;
	}
	void set_speed_anim(double speed_anim)
	{
		this->speed_anim = speed_anim;
	}
	void enable_revers_rect(int dir)
	{
		switch (dir)
		{
		case right:
			right_anim_x_rev = right_anim_x;
			right_rev_num *= -1;
			break;
		case left:
			left_anim_x_rev = left_anim_x;
			left_rev_num *= -1;
			break;
		case up:
			up_anim_y_rev = up_anim_y;
			up_rev_num *= -1;
			break;
		case down:
			down_anim_y_rev = down_anim_y;
			down_rev_num *= -1;
			break;
		default:
			break;
		}
	}
	void disable_revers_rect(int dir)
	{
		switch (dir)
		{
		case right:
			right_anim_x_rev = 0;
			right_rev_num = 1;
			break;
		case left:
			left_anim_x_rev = 0;
			left_rev_num = 1;
			break;
		case up:
			up_anim_y_rev = 0;
			up_rev_num = 1;
			break;
		case down:
			down_anim_y_rev = 0;
			down_rev_num = 1;
			break;
		default:
			break;
		}
	}
	Sprite& get_spr()
	{
		return p.spr;
	}
	void move(float time,Ball& ball)
	{
		


			if (check_s == 1)
			{
				end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> dur = end - start;
				if (dur.count() > 3.0)
				{
					speed = s_ordinary;
					check_s = 0;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				p.dir = left; p.speed = speed;
				CurrentFrameX += speed_anim * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(left_anim_x * int(CurrentFrameX) + left_anim_x_rev, left_anim_y, left_rev_num * p.h, p.w));
				getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
				

			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				p.dir = right; p.speed = speed;
				CurrentFrameX += speed_anim * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(right_anim_x * int(CurrentFrameX) + right_anim_x_rev, right_anim_y, right_rev_num * p.h, p.w));
				getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				p.dir = up; p.speed = speed;
				CurrentFrameX += speed_anim * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(up_anim_x * int(CurrentFrameX), up_anim_y + up_anim_y_rev, p.h, p.w * up_rev_num));
				getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				p.dir = down; p.speed = speed;
				CurrentFrameX += speed_anim * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(down_anim_x * int(CurrentFrameX), down_anim_y + down_anim_y_rev, p.h, p.w * down_rev_num));
				getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}
			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{

				if (check_s == 0)
				{
					s_ordinary = speed;
					speed += 0.15;
					check_s = 1;
					start = std::chrono::high_resolution_clock::now();
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				std::cout << "pX= " << p.getPlayerCoordinateX() << std::endl;
				
				std::cout << "bX= " << ball.getCoordinateX() << std::endl;
				std::cout << "pY= " << p.getPlayerCoordinateY() << std::endl;
				std::cout << "bY= " << ball.getCoordinateY() << std::endl;
				if(ball.isfree)
				{ 

				switch (p.dir)
				{
				case right:
					if (p.getPlayerCoordinateX()<ball.getCoordinateX()&& p.getPlayerCoordinateX()+150 > ball.getCoordinateX()&&abs(p.getPlayerCoordinateY()+50 - ball.getCoordinateY())<=64)
					{
						if (ball.isfree)
						{
							ball.isfree = false;

						}
					}
					break;
				case left:
					if (p.getPlayerCoordinateX() > ball.getCoordinateX() && p.getPlayerCoordinateX() - 150 <ball.getCoordinateX() && abs(p.getPlayerCoordinateY() + 50 - ball.getCoordinateY()) <= 64)
					{
						if (ball.isfree)
						{
							ball.isfree = false;

						}
					}
					break;
				case up:
					if (p.getPlayerCoordinateY() > ball.getCoordinateY()  && p.getPlayerCoordinateY() - 100 < ball.getCoordinateY() && abs(p.getPlayerCoordinateX() - ball.getCoordinateX()) <= 80)
					{
						if (ball.isfree)
						{
							ball.isfree = false;

						}
					}
					break;
				case down:
					if (p.getPlayerCoordinateY() < ball.getCoordinateY()  && p.getPlayerCoordinateY() + 100 > ball.getCoordinateY() && abs(p.getPlayerCoordinateX() - ball.getCoordinateX()) <= 80)
					{
						if (ball.isfree)
						{
							ball.isfree = false;

						}
					}
					break;
				default:
					break;
				}
				}	
				else
				{
					
						ball.isfree = true;
					
				}
				
				

			}
			p.update(time);
		
	}
	int get_score()
	{
		return p.playerscore;
	}
	float get_speed()
	{
		return speed;
	}
	Player p;
private:
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now(), end = std::chrono::high_resolution_clock::now();
	float s_ordinary;
	int check_s = 0;
	float CurrentFrameX = 0;
	int CurrentFrameMax;
	double speed;
	bool isgrabbed = false;
	float left_anim_x, right_anim_x, up_anim_x, down_anim_x;
	float left_anim_y, right_anim_y, up_anim_y, down_anim_y;
	double speed_anim = 0.005;
	float left_anim_x_rev = 0, right_anim_x_rev = 0;
	float up_anim_y_rev = 0, down_anim_y_rev = 0;
	int right_rev_num = 1, left_rev_num = 1, up_rev_num = 1, down_rev_num = 1;
};

class Map
{
public:
	Map(String file)
	{
		this->file = file;
		map_image.loadFromFile("map/" + file);
		map_image.createMaskFromColor(Color::White);
		tex_map.loadFromImage(map_image);
		spr_map.setTexture(tex_map);
	}
	Sprite& get_spr()
	{
		return spr_map;
	}

	void draw_the_map(RenderWindow& wind)
	{
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  spr_map.setTextureRect(IntRect(160, 0, 32, 32));
				if (TileMap[i][j] == 's') spr_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0')spr_map.setTextureRect(IntRect(64, 0, 32, 32));
				spr_map.setPosition(j * 32, i * 32);
				wind.draw(spr_map);
			}
		}
	}
private:
	Image map_image;
	Texture tex_map;
	Sprite spr_map;
	String file;

};





int main()
{
	sf::RenderWindow wind(sf::VideoMode(800, 600), "Wind");
	Font font;
	font.loadFromFile("CyrilicOld.TTF");
	Text text("", font, 40);
	text.setFillColor(Color(244, 244, 244));
	text.setOutlineThickness(0.5);
	text.setOutlineColor(Color(0, 0, 0));
	text.setStyle(Text::Bold);
	view.reset(FloatRect(0, 0, 800, 600));

	Ball ball("ball.png", 0,0, 32, 32);
	
	ball.set_position(450, 250);
	float speed = 0.2;
	Character hero("4.png", 196, 196, 96, 96, 3, speed, 96, 96, 96, 96, 110, 110, 288, 0);
	hero.enable_revers_rect(0);
	
	Map map("map.png");
	Clock clock;

	while (wind.isOpen())
	{
		sf::Event ev;
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;
		while (wind.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				wind.close();
			}

		}

		viewmap(time);
		hero.move(time,ball);

		wind.setView(view);
		wind.clear();
		map.draw_the_map(wind);
		std::string s = std::to_string(hero.get_score());
		text.setString(s);
		text.setPosition(view.getCenter().x - 270, view.getCenter().y + 250);
		ball.update(time, hero.p.getPlayerCoordinateX(), hero.p.getPlayerCoordinateY(), hero.p.dx, hero.p.dy, hero.get_speed());
		wind.draw(text);
		
		
		wind.draw(ball.spr);
		wind.draw(hero.get_spr());
		wind.display();
	}
	return 0;
}


