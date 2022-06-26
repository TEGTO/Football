#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"map.h"
#include"view.h"
#include<iostream>
#include <chrono>
#include<cmath>
#include<thread>


using namespace sf;
enum Directions
{
	right, left, up, down
};
class Coordinates
{public:
	float x, y;
};
class Player
{
private:
	Coordinates main;
	Coordinates default_position;
public:
	float w, h, dx, dy, speed = 0;
	int dir = 0, health=20;
	bool isalive;
	String File;
	Image img;
	Texture texture;
	Sprite spr;
	Player()
	{

	}
	void setPosition(float x, float y)
	{
		main.x = x;
		main.y = y;
	}
	void setDefaultCoordinates(float x, float y)
	{
		default_position.x = x;
		default_position.y = y;
	}
	Coordinates getDefaultCoordinates()
	{
		return default_position;
	}
	void set_par(String FIle, int x, int y, float h, float w)
	{
		
		File = FIle;
		main.x = x, main.y = y, this->h = h, this->w = w;
		img.loadFromFile("images/" + File);
		img.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(img);
		spr.setTexture(texture);
		spr.setTextureRect(IntRect(main.x, main.y, this->w, this->h));
	}
	Coordinates getPlayerCoordinates()
	{
		return main;
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
		main.x += dx * time;
		main.y += dy * time;
		speed = 0;
		spr.setPosition(main.x, main.y);
		interactionWithMap();
	}
	void interactionWithMap()
	{
		for (int i = main.y / 32; i < (main.y + h) / 32; i++)
		{
			for (int j = main.x / 32; j < (main.x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
					{
						main.y = i * 32 - h;

					}
					if (dy < 0)
					{
						main.y = i * 32 + 32;

					}
					if (dx > 0)
					{
						main.x = j * 32 - w;

					}
					if (dx < 0)
					{
						main.x = j * 32 + 32;

					}
				}
				
				
				
				if (TileMap[i][j] == 'p')
				{
					health -= 50;

					TileMap[i][j] = ' ';

				}
			}
		}
		for (int i = main.y / 32; i < (main.y + h) / 32; i++)
		{
			for (int j = main.x / 32 ;j < (main.x + w) / 32; j++)
			{
				if (TileMap[i][j] == 'w')
				{
					if (dy > 0)
					{
						main.y = i * 32 - h;

					}
					if (dy < 0)
					{
						main.y = i * 32 + 32;

					}
					if (dx > 0)
					{
						main.x = j * 32 - w;

					}
					if (dx < 0)
					{
						main.x = j * 32 + 32;

					}
				}
			}
		}
	}
private:

};
class Ball
{
private:
	
	float CurrentFrameX = 0;
	float sped_anim = 0.02;
	Coordinates default_position;
	Coordinates main;
	void animations(float time)
	{
		CurrentFrameX += sped_anim * time;
		if (CurrentFrameX > 3)
		{
			CurrentFrameX = 0;
		}
		spr.setTextureRect(IntRect(32 * int(CurrentFrameX), 0, 32, 32));
	}
public:
	void setSpeedAnim(float speed)
	{
		this->sped_anim = speed;
	}
	bool isfree = true;
	float w, h, dx, dy, speed = 0;
	
	int dir = 0;
	String File;
	Image img;
	Texture texture;
	Sprite spr;
	Coordinates getCoordinates()
	{
		return main;
	}
	void setDefaultCoordinates(float x, float y)
	{
		default_position.x = x;
		default_position.y = y;
	}
	Coordinates getDefaultCoordinates()
	{
		return default_position;
	}
	Ball(String FIle, int x, int y, float h, float w)
	{

		File = FIle;
		main.x = x, main.y = y, this->h = h, this->w = w;
		img.loadFromFile("images/ball/" + File);

		texture.loadFromImage(img);
		spr.setTexture(texture);
		spr.setTextureRect(IntRect(main.x, main.y, this->w, this->h));
	}
	void set_position(float x, float y)
	{
		main.x = x;
		main.y = y;
	}
	void update(float time, float p_x, float p_y, float p_dx, float p_dy, float speed,bool isgrabbed)
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
		main.x += dx * time;
		main.y += dy * time;
		this->speed = 0;

		spr.setPosition(main.x, main.y);

		ball_physics(time, p_x, p_y, p_dx, p_dy, speed);

		}
		else
		{
			if (isgrabbed)
			{
				if (p_dy > 0)
				{
					dir = down;
					main.y = p_y + 85;
					main.x = p_x + 32;
					animations(time);
				}
				if (p_dy < 0)
				{
					dir = up;

					main.y = p_y - 15;
					main.x = p_x + 32;
					animations(time);

				}
				if (p_dx > 0)
				{
					dir = left;
					main.y = p_y + 60;
					main.x = p_x + 70;
					animations(time);
				}
				if (p_dx < 0)
				{
					dir = left;
					main.y = p_y + 60;
					main.x = p_x - 10;
					animations(time);
				}

				spr.setPosition(main.x, main.y);
			}
		
			
			
		}

	}
	void ball_physics(float time, float p_x, float p_y, float p_dx, float p_dy, float speed)
	{

		for (int i = main.y / 32; i < (main.y + h) / 32; i++)
		{
			for (int j = main.x / 32; j < (main.x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0'|| TileMap[i][j] == 'w')
				{
					if (dy > 0)
					{
						main.y = i * 32 - h*3;

					}
					if (dy < 0)
					{
						main.y = i * 32 + 32*3 ;

					}
					if (dx > 0)
					{
						main.x = j * 32 - w*3;

					}
					if (dx < 0)
					{
						main.x = j * 32 + 32 *3;

					}
				}
			}
		}
		if (abs((main.x - 30) - (p_x)) < 35 &&abs(((main.y - 35) - (p_y))) < 45)
		{


			if (p_dy > 0)
			{

				dir = down;
				main.y += dy * speed * time;
				animations(time);
			}
			if (p_dy < 0)
			{
				dir = up;
				main.y += dy * speed * time;

				animations(time);

			}
			if (p_dx > 0)
			{
				dir = right;
				main.x += speed * time;

				animations(time);
			}
			if (p_dx < 0)
			{
				dir = left;

				main.x += dx * speed * time;
				animations(time);
			}

			this->speed = speed;
		}
	}
};
class Character
{
public:
	Character(String FIle, int x, int y, float h, float w, int CurrentFrameMax, double speed, float left_anim_x, float right_anim_x, float up_anim_x, float down_anim_x, float left_anim_y, float right_anim_y, float up_anim_y, float down_anim_y,int type)
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
		this->type = type;
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
		switch (type)
		{
		case 1:
				if (check_s == 1)
				{
					end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur = end - start;
					if (dur.count() > 3.0)
					{
						speed = s_ordinary;
						check_s = 0;
						ball.setSpeedAnim(0.02);
						speed_anim = 0.005;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					p.dir = left; p.speed = speed;
					CurrentFrameX += speed_anim * time;
					if (CurrentFrameX > CurrentFrameMax){CurrentFrameX = 0;}
					p.spr.setTextureRect(IntRect(left_anim_x * int(CurrentFrameX) + left_anim_x_rev, left_anim_y, left_rev_num * p.h, p.w));
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
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
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
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
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
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
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
				}
				if (Keyboard::isKeyPressed(Keyboard::LShift))
				{

					if (check_s == 0)
					{
						s_ordinary = speed;
						speed += 0.15;
						check_s = 1;
						start = std::chrono::high_resolution_clock::now();
						ball.setSpeedAnim(0.03);
						speed_anim = 0.01;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::E))
				{

					if (ball.isfree)
					{

						switch (p.dir)
						{
						case right:
							if (p.getPlayerCoordinates().x<ball.getCoordinates().x && p.getPlayerCoordinates().x + 150 > ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
								}
							}
							break;
						case left:
							if (p.getPlayerCoordinates().x > ball.getCoordinates().x && p.getPlayerCoordinates().x - 150 < ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
								}
							}
							break;
						case up:
							if (p.getPlayerCoordinates().y > ball.getCoordinates().y && p.getPlayerCoordinates().y - 100 < ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
								}
							}
							break;
						case down:
							if (p.getPlayerCoordinates().y < ball.getCoordinates().y && p.getPlayerCoordinates().y + 100 > ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
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
						isgrabbed = false;
					}



				}
				if (Keyboard::isKeyPressed(Keyboard::Q))
				{

					if (isgrabbed)
					{

						switch (p.dir)
						{
						case right:

							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x + 200, p.getPlayerCoordinates().y + 60);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }

							break;
						case left:

							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x - 150, p.getPlayerCoordinates().y + 60);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }
							break;
						case up:
							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y - 120);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }
							break;
						case down:
							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y + 220);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }
							break;
						default:
							break;
						}
						isgrabbed = false;
					}
				}
				p.update(time);
			break;
		case 2:
			
				if (check_s == 1)
				{

					end = std::chrono::high_resolution_clock::now();

					std::chrono::duration<float> dur = end - start;

					if (dur.count() > 3.0)
					{
						speed = s_ordinary;
						check_s = 0;
						ball.setSpeedAnim(0.02);
						speed_anim = 0.005;

					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					p.dir = left; p.speed = speed;
					CurrentFrameX += speed_anim * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(left_anim_x * int(CurrentFrameX) + left_anim_x_rev, left_anim_y, left_rev_num * p.h, p.w));
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);


				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					p.dir = right; p.speed = speed;
					CurrentFrameX += speed_anim * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(right_anim_x * int(CurrentFrameX) + right_anim_x_rev, right_anim_y, right_rev_num * p.h, p.w));
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
				}
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					p.dir = up; p.speed = speed;
					CurrentFrameX += speed_anim * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(up_anim_x * int(CurrentFrameX), up_anim_y + up_anim_y_rev, p.h, p.w * up_rev_num));
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					p.dir = down; p.speed = speed;
					CurrentFrameX += speed_anim * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(down_anim_x * int(CurrentFrameX), down_anim_y + down_anim_y_rev, p.h, p.w * down_rev_num));
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
				}
				if (Keyboard::isKeyPressed(Keyboard::J))
				{

					if (check_s == 0)
					{
						s_ordinary = speed;
						speed += 0.15;
						check_s = 1;
						start = std::chrono::high_resolution_clock::now();
						ball.setSpeedAnim(0.03);
						speed_anim = 0.01;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::K))
				{

					if (ball.isfree)
					{

						switch (p.dir)
						{
						case right:
							if (p.getPlayerCoordinates().x<ball.getCoordinates().x && p.getPlayerCoordinates().x + 150 > ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
								}
							}
							break;
						case left:
							if (p.getPlayerCoordinates().x > ball.getCoordinates().x && p.getPlayerCoordinates().x - 150 < ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
								}
							}
							break;
						case up:
							if (p.getPlayerCoordinates().y > ball.getCoordinates().y && p.getPlayerCoordinates().y - 100 < ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
								}
							}
							break;
						case down:
							if (p.getPlayerCoordinates().y < ball.getCoordinates().y && p.getPlayerCoordinates().y + 100 > ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
							{
								if (ball.isfree)
								{
									ball.isfree = false;
									isgrabbed = true;
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
						isgrabbed = false;
					}



				}
				if (Keyboard::isKeyPressed(Keyboard::L))
				{

					if (isgrabbed)
					{

						switch (p.dir)
						{
						case right:

							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x + 200, p.getPlayerCoordinates().y + 60);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }

							break;
						case left:

							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x - 150, p.getPlayerCoordinates().y + 60);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }
							break;
						case up:
							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y - 120);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }
							break;
						case down:
							ball.isfree = true;
							ball.set_position(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y + 220);
							if (ball.getCoordinates().x <= 22) { ball.set_position(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.set_position(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.set_position(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.set_position(ball.getCoordinates().x, 605); }
							break;
						default:
							break;
						}
						isgrabbed = false;
					}

				}

				p.update(time);
			
		default:
			break;
		}
			
		
	}
	
	float get_speed()
	{
		return speed;
	}
	Player p;
	bool getIsGrabbed()
	{
		return isgrabbed;
	}
	void setIsGrabbed(bool isgrabbed)
	{
		this->isgrabbed = isgrabbed;
	}
private:
	int type;
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
				if (TileMap[i][j] == ' ')  spr_map.setTextureRect(IntRect(162, 0, 32, 32));
				if (TileMap[i][j] == 's') spr_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0')spr_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'i')spr_map.setTextureRect(IntRect(195, 0, 32, 32));
				if (TileMap[i][j] == 'j')spr_map.setTextureRect(IntRect(228, 0, -32, 32));
				if (TileMap[i][j] == 'b')spr_map.setTextureRect(IntRect(259, 0, 32, 32));
				if (TileMap[i][j] == 'k')spr_map.setTextureRect(IntRect(291, 0, -32, 32));
				if (TileMap[i][j] == '|')spr_map.setTextureRect(IntRect(228, 0, 32, 32));
				if (TileMap[i][j] == 'l')spr_map.setTextureRect(IntRect(260, 0, -32, 32));
				if (TileMap[i][j] == 'w')spr_map.setTextureRect(IntRect(291, 0, 32, 32));
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
class Gate
{
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now(), end = std::chrono::high_resolution_clock::now();

	int score=0;
	int type=1;
	Coordinates coor;
	bool is_check_first;
	bool is_check_second;
public:
	
	int getScore()
	{
		return score;
	}
	Gate(int type, float x, float y)
	{
		this->type = type;
		coor.x = x;
		coor.y = y;
	}
	void update(Ball&ball, Character &one, Character &two,RenderWindow & wind)
	{
		
		switch (type)
		{
		case 1:
			if (is_check_first&& is_check_second)
			{
				if (ball.getCoordinates().x <= coor.x && ball.getCoordinates().x <= coor.x + 200 && abs(ball.getCoordinates().y - coor.y) <= 70)
				{
					score++;
					is_check_first = false;
					 start = std::chrono::high_resolution_clock::now();
				}
			}
			if (!is_check_first)
			{
				
				 end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> dur = end - start;
				std::cout << dur.count() << std::endl;
				if (dur.count()>0&&dur.count()<3)
				{
					one.setIsGrabbed(false);
					two.setIsGrabbed(false);
					ball.isfree = true;
					Font font;
						font.loadFromFile("CyrilicOld.TTF");
						Text text("Goal!", font, 70);
						text.setFillColor(Color::White);
						text.setOutlineThickness(1);
						text.setOutlineColor(Color::Black);
						text.setStyle(Text::Italic|Text::Bold);
						
						text.setPosition(view.getCenter().x-100, view.getCenter().y-250);
						wind.draw(text);
						
					
					
					
				}
				if (dur.count() > 3.5)
				{


					ball.set_position(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
					one.p.setPosition(one.p.getDefaultCoordinates().x, one.p.getDefaultCoordinates().y);
					two.p.setPosition(two.p.getDefaultCoordinates().x, two.p.getDefaultCoordinates().y);
					
					is_check_first = true;
					
				}
				
			}
			break;
		case 2:
			if (is_check_second&& is_check_first)
			{
				if (ball.getCoordinates().x >= coor.x && ball.getCoordinates().x >= coor.x - 200 && abs(ball.getCoordinates().y - coor.y) <=70)
				{
					score++;
					is_check_second = false;
					start = std::chrono::high_resolution_clock::now();

				}
			}
			if (!is_check_second)
			{
				one.setIsGrabbed(false);
				two.setIsGrabbed(false);
				ball.isfree = true;
				end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> dur = end - start;
				std::cout << dur.count() << std::endl;
				if (dur.count() > 0 && dur.count() < 3)
				{

					Font font;
					font.loadFromFile("CyrilicOld.TTF");
					Text text("Goal!", font, 70);
					text.setFillColor(Color::White);
					text.setOutlineThickness(1);
					text.setOutlineColor(Color::Black);
					text.setStyle(Text::Italic | Text::Bold);

					text.setPosition(view.getCenter().x - 100, view.getCenter().y - 250);
					wind.draw(text);




				}
				if (dur.count() > 3.5)
				{


					ball.set_position(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
					one.p.setPosition(one.p.getDefaultCoordinates().x, one.p.getDefaultCoordinates().y);
					two.p.setPosition(two.p.getDefaultCoordinates().x, two.p.getDefaultCoordinates().y);
					is_check_second = true;
					
				}

			}
			break;
		default:
			break;
		}
		
	}
};
void ShowCoordinate(Event &ev)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		std::cout << "x= " << ev.mouseMove.x << std::endl;
		std::cout << "y= " << ev.mouseMove.y << std::endl;
	}
}

void Write_Score(RenderWindow &wind,String s,float x , float y,int type)
{
	Font font;
	font.loadFromFile("CyrilicOld.TTF");
	Text text(s,font, 60);
	switch (type)
	{
	case 1:
		text.setFillColor(Color::Red);
		break;
	case 2:
		text.setFillColor(Color::Blue);
		break;
	default:
		break;
	}
	
	text.setOutlineThickness(0.5);
	text.setOutlineColor(Color(0, 0, 0));
	text.setStyle(Text::Bold);
	
	text.setPosition(x, y);
	wind.draw(text);
}

int main()
{
	sf::RenderWindow wind(sf::VideoMode(800, 600), "Wind");

	view.reset(FloatRect(0, 0, 800, 600));
	Ball ball("ball.png", 0,0, 32, 32);
	ball.set_position(767.5, 320);

	float speed = 0.2;

	Character first("Red.png", 0, 196, 96, 96, 3, speed, 96, 96, 96, 96, 110, 110, 288, 0,1);
	Character second("Blue.png", 0, 196, 96, 96, 3, speed, 96, 96, 96, 96, 110, 110, 288, 0,2);
	
	first.enable_revers_rect(0);
	second.enable_revers_rect(0);
	Gate gate_first(1, 119, 323);
	Gate gate_second(2, 1407, 323);
	Map map("map.png");
	Clock clock;
	first.p.setPosition(200, 275);
	second.p.setPosition(1275, 275);
	first.p.setDefaultCoordinates(200, 275);
	second.p.setDefaultCoordinates(1275, 275);
	ball.setDefaultCoordinates(767.5, 320);
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

		//viewmap(time);
		first.move(time,ball);
		second.move(time, ball);
		//ShowCoordinate(ev);
		wind.setView(view);
		wind.clear();
		map.draw_the_map(wind);
		ball.update(time, first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y, first.p.dx, first.p.dy, first.get_speed(),first.getIsGrabbed());
		ball.update(time, second.p.getPlayerCoordinates().x, second.p.getPlayerCoordinates().y, second.p.dx, second.p.dy, second.get_speed(),second.getIsGrabbed());
		gate_first.update(ball,first,second,wind);
		gate_second.update(ball,first,second,wind);
		Write_Score(wind, std::to_string(gate_first.getScore()), view.getCenter().x-350, view.getCenter().y-300, 1);
		Write_Score(wind, std::to_string(gate_second.getScore()), view.getCenter().x +325 , view.getCenter().y - 300, 2);
		wind.draw(ball.spr);
		wind.draw(first.get_spr());
		wind.draw(second.get_spr());
		wind.display();
	}
	return 0;
}


