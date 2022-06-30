#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"map.h"
#include"view.h"
#include<iostream>
#include <chrono>
#include<cmath>
#include<thread>


using namespace sf;
int WhichPlayerIsUsingCam;
enum Directions
{
	right, left, up, down
};
enum MenuType
{
	menu = 1, pvp, pve, split
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
	bool isCheck = true;
	bool isCanYouTake = true;
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
		shootBuffer.loadFromFile("audio/shooting2.wav");
		shoot.setBuffer(shootBuffer);
		walkingBuffer.loadFromFile("audio/walking2.wav");
		walking.setBuffer(walkingBuffer);
		kickBuffer.loadFromFile("audio/kick.wav");
		kick.setBuffer(kickBuffer);
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
	void move(float time,Ball& ball,int typeOfCam,int typeOfGame,float x_first_player,float y_first_player)
	{
		
		switch (type)
		{
		case 1:
				if (isWalking==2)
				{
				
					end_walk = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur_walk = end_walk - start_walk;
					if (dur_walk.count()> time_of_walking)
					{
						
						isWalking = 0;
					}
				}
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
						time_of_walking = 0.7;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					p.dir = left; p.speed = speed;
					CurrentFrameX += speed_anim * time;
					if (CurrentFrameX > CurrentFrameMax){CurrentFrameX = 0;}
					p.spr.setTextureRect(IntRect(left_anim_x * int(CurrentFrameX) + left_anim_x_rev, left_anim_y, left_rev_num * p.h, p.w));
					
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
					WhichPlayerIsUsingCam = 1;
					if (isWalking == 0)
					{

						isWalking = 1;
					}
					
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
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
					WhichPlayerIsUsingCam = 1;
					if (isWalking == 0)
					{

						isWalking = 1;
					}
					
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
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
					WhichPlayerIsUsingCam = 1;
					if (isWalking == 0)
					{

						isWalking = 1;
					}
					
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
					getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
					WhichPlayerIsUsingCam = 1;
					if (isWalking==0)
					{
						
						isWalking = 1;
					}
					
				}
				if (isWalking == 1)
				{
					isWalking =2;
					start_walk = std::chrono::high_resolution_clock::now();
					walking.play();
					

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
						time_of_walking = 0.5;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::E))
				{
					if (isCanYouTake)
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
						kick.play();
					}
				}
				if (isCheck)
				{
					if (Keyboard::isKeyPressed(Keyboard::F))
					{
						
						shoot.play();
							isShoot = true;
							isCheck = false;
					}
				}
				
				p.update(time);

			break;
		case 2:
			if (typeOfGame != pve)
			{
				if (isWalking == 2)
				{

					end_walk = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur_walk = end_walk - start_walk;
					if (dur_walk.count() > time_of_walking)
					{

						isWalking = 0;
					}
				}
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
					switch (typeOfCam)
					{
					case default_c:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case split_c:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					WhichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}



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
					switch (typeOfCam)
					{
					case default_c:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case split_c:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					WhichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}

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
					switch (typeOfCam)
					{
					case default_c:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case split_c:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					WhichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}

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
					switch (typeOfCam)
					{
					case default_c:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case split_c:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					WhichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}

				}
				if (isWalking == 1)
				{
					isWalking = 2;
					start_walk = std::chrono::high_resolution_clock::now();
					walking.play();


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
					if (isCanYouTake)
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

					/*else
					{

						ball.isfree = true;
						isgrabbed = false;
					}*/

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
				if (isCheck)
				{
					if (Keyboard::isKeyPressed(Keyboard::I))
					{
						shoot.play();
						isShoot = true;
						isCheck = false;
					}
				}
			
			}
			

			else
			{
			if (isWalking == 2)
			{

				end_walk = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> dur_walk = end_walk - start_walk;
				if (dur_walk.count() > time_of_walking)
				{

					isWalking = 0;
				}
			}


			if (!isgrabbed )
			{
				
				if (abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) > 30)
				{
					
					if (p.getPlayerCoordinates().x > ball.getCoordinates().x)
					{
						p.dir = left; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(left_anim_x * int(CurrentFrameX) + left_anim_x_rev, left_anim_y, left_rev_num * p.h, p.w));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
					
					}
					if (p.getPlayerCoordinates().x < ball.getCoordinates().x)
					{
						p.dir = right; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(right_anim_x * int(CurrentFrameX) + right_anim_x_rev, right_anim_y, right_rev_num * p.h, p.w));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						
					}
					if (isWalking == 0)
					{

						isWalking = 1;
					}
				}
				if (abs(p.getPlayerCoordinates().y - ball.getCoordinates().y) > 20)
				{
					
					if (p.getPlayerCoordinates().y < ball.getCoordinates().y)
					{
						p.dir = down; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(down_anim_x * int(CurrentFrameX), down_anim_y + down_anim_y_rev, p.h, p.w * down_rev_num));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						
					}
					if (p.getPlayerCoordinates().y > ball.getCoordinates().y)
					{
						p.dir = up; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(up_anim_x * int(CurrentFrameX), up_anim_y + up_anim_y_rev, p.h, p.w * up_rev_num));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						
					}
					if (isWalking == 0)
					{

						isWalking = 1;
					}
				}
				if (abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) < 30&& abs(p.getPlayerCoordinates().y - ball.getCoordinates().y)< 20)
				{
					if (isCanYouTake)
					{
						ball.isfree = false;
						isgrabbed = true;
					}
					
				}
				
			}



			if (isgrabbed )
			{
				if (abs(p.getPlayerCoordinates().x - 119) > 20)
				{
					if (p.getPlayerCoordinates().x >= 119)
					{
						p.dir = left; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(left_anim_x * int(CurrentFrameX) + left_anim_x_rev, left_anim_y, left_rev_num * p.h, p.w));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						
					}
					if (p.getPlayerCoordinates().x <119)
					{
						p.dir = right; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(right_anim_x * int(CurrentFrameX) + right_anim_x_rev, right_anim_y, right_rev_num * p.h, p.w));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						
					}
					if (isWalking == 0)
					{

						isWalking = 1;
					}
				}
				if (abs(p.getPlayerCoordinates().y - 329) > 30)
				{
					if (p.getPlayerCoordinates().y < 329)
					{
						p.dir = down; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(down_anim_x * int(CurrentFrameX), down_anim_y + down_anim_y_rev, p.h, p.w * down_rev_num));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
					}
					if (p.getPlayerCoordinates().y > 329)
					{
						p.dir = up; p.speed = speed;
						CurrentFrameX += speed_anim * time;
						if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
						p.spr.setTextureRect(IntRect(up_anim_x * int(CurrentFrameX), up_anim_y + up_anim_y_rev, p.h, p.w * up_rev_num));
						if (typeOfCam == split_c) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
					}
					if (isWalking == 0)
					{

						isWalking = 1;
					}
				}

				
			}
			if (abs(p.getPlayerCoordinates().y - y_first_player) <= 20)
			{
				if (isCheck)
				{
					if (rand() % 2 == 0)
					{
						shoot.play();
						isShoot = true;
						isCheck = false;
					}


				}
			}
			}



			if(isWalking == 1)
			{
				isWalking = 2;
				start_walk = std::chrono::high_resolution_clock::now();
				walking.play();


			}
			p.update(time);
		default:
			break;
		}
		if (p.health<=0)
		{
			if (!ball.isfree)
			{
				ball.isfree = true;
				isgrabbed = false;
				
			}
			if (isgrabbed && type ==2 && typeOfGame ==pve)
			{
				ball.isfree = true;
				isgrabbed = false;

			}
			p.setPosition(p.getDefaultCoordinates().x, p.getDefaultCoordinates().y);
			p.health = 20;
		
			switch (typeOfCam)
			{
			case default_c:
				if (WhichPlayerIsUsingCam == type)
				{
					switch (WhichPlayerIsUsingCam)
					{
					case 1:
						view.setCenter(p.getPlayerCoordinates().x + 200, p.getPlayerCoordinates().y + 25);
						break;
					case 2:
						view.setCenter(p.getPlayerCoordinates().x -105, p.getPlayerCoordinates().y + 25);
						break;
					default:
						break;
					}
					
				}
				break;
			case split_c:
				switch (type)
				{
				case 1:
					view.setCenter(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y + 25);
					break;
				case 2:
					view2.setCenter(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y + 25);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
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
	bool  isShoot = false;
private:
	int type,isWalking=0;
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now(), end = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point start_walk = std::chrono::high_resolution_clock::now(), end_walk = std::chrono::high_resolution_clock::now();
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
	SoundBuffer shootBuffer;
	SoundBuffer walkingBuffer;
	SoundBuffer kickBuffer;
	Sound shoot;
	Sound walking;
	Sound kick;
	float time_of_walking = 0.7;
};

class Map
{
public:
	Map(String file)
	{
		this->file = file;
		map_image.loadFromFile("map/" + file);
	
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
				if (TileMap[i][j] == '1')spr_map.setTextureRect(IntRect(328, 0, 32, 32));
				if (TileMap[i][j] == '=')spr_map.setTextureRect(IntRect(362, 0, 32, 32));
				if (TileMap[i][j] == 'P')spr_map.setTextureRect(IntRect(395, 0, 32, 32));
				if (TileMap[i][j] == 'B')spr_map.setTextureRect(IntRect(427, 0, -32, 32));
				if (TileMap[i][j] == 'L')spr_map.setTextureRect(IntRect(395, 34, 32, -32));
				if (TileMap[i][j] == 'N')spr_map.setTextureRect(IntRect(427, 34, -32, -32));
				if (TileMap[i][j] == '2')spr_map.setTextureRect(IntRect(464, 0, 32, 32));
				if (TileMap[i][j] == '3')spr_map.setTextureRect(IntRect(126, -1, 32, 32));
				if (TileMap[i][j] == '4')spr_map.setTextureRect(IntRect(158, -1, -32, 32));
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
	bool is_on = true;
	void setScore(int score)
	{
		this->score = score;
	}
	int getScore()
	{
		return score;
	}
	Gate(int type, float x, float y)
	{
		this->type = type;
		coor.x = x;
		coor.y = y;
		crowdBuffer.loadFromFile("audio/crowd.wav");
		crowd.setBuffer(crowdBuffer);
		
	}
	void update(Ball&ball, Character &first, Character &second,RenderWindow & wind,float x,float y,int typeOfCam,int typeOfGame)
	{
		if (is_on)
		{
			switch (type)
			{
			case 1:
				if (is_check_first && is_check_second)
				{
					if (ball.getCoordinates().x <= coor.x && ball.getCoordinates().x <= coor.x + 200 && abs(ball.getCoordinates().y - coor.y) <= 70)
					{
						score++;
						is_check_first = false;
						start = std::chrono::high_resolution_clock::now();
					}
					if (typeOfGame == pve && second.getIsGrabbed()== true)
					{
						if (ball.getCoordinates().x <= coor.x+20 && ball.getCoordinates().x <= coor.x + 350 && abs(ball.getCoordinates().y - coor.y) <= 140)
						{
						
							score++;
							is_check_first = false;
							start = std::chrono::high_resolution_clock::now();
						
						}
					}
				}
				if (!is_check_first)
				{

					end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur = end - start;
					
					if (dur.count() > 0 && dur.count() < 3)
					{
						
						first.isCanYouTake = false;
						second.isCanYouTake = false;
						first.setIsGrabbed(false);
						second.setIsGrabbed(false);
						ball.isfree = true;
						Font font;
						font.loadFromFile("CyrilicOld.TTF");
						Text text("Goal!", font, 70);
						if (crowdCheck ==1)
						{
							crowd.play();
							crowdCheck = 0;
						}
						text.setFillColor(Color::White);
						text.setOutlineThickness(1);
						text.setOutlineColor(Color::Black);
						text.setStyle(Text::Italic | Text::Bold);

						text.setPosition(x - 60, y - 235);
						wind.draw(text);
						



					}
					if (dur.count() > 3.5)
					{


						ball.set_position(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
						first.p.setPosition(first.p.getDefaultCoordinates().x, first.p.getDefaultCoordinates().y);
						second.p.setPosition(second.p.getDefaultCoordinates().x, second.p.getDefaultCoordinates().y);
						first.isCanYouTake = true;
						second.isCanYouTake = true;
						is_check_first = true;
						crowdCheck = 1;
						switch (typeOfCam)
						{
						case default_c:
							switch (WhichPlayerIsUsingCam)
							{
							case 1:
								view.setCenter(first.p.getPlayerCoordinates().x + 200, first.p.getPlayerCoordinates().y + 25);
								break;
							case 2:
								view.setCenter(second.p.getPlayerCoordinates().x - 105, second.p.getPlayerCoordinates().y + 25);
								break;
							default:
								break;
							}
							break;
						case split_c:
							view.setCenter(first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y + 25);
							view2.setCenter(second.p.getPlayerCoordinates().x, second.p.getPlayerCoordinates().y + 25);
							break;
						default:
							break;
						}
					}

				}
				break;
			case 2:
				if (is_check_second && is_check_first)
				{
					if (ball.getCoordinates().x >= coor.x && ball.getCoordinates().x >= coor.x - 200 && abs(ball.getCoordinates().y - coor.y) <= 70)
					{
						score++;
						is_check_second = false;
						start = std::chrono::high_resolution_clock::now();

					}
				}
				if (!is_check_second)
				{
					first.setIsGrabbed(false);
					second.setIsGrabbed(false);
					ball.isfree = true;
					end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur = end - start;
					
					if (dur.count() > 0 && dur.count() < 3)
					{
						first.isCanYouTake = false;
						second.isCanYouTake = false;
						Font font;
						font.loadFromFile("CyrilicOld.TTF");
						Text text("Goal!", font, 70);
						if (crowdCheck == 1)
						{
							crowd.play();
							crowdCheck = 0;
						}
						text.setFillColor(Color::White);
						text.setOutlineThickness(1);
						text.setOutlineColor(Color::Black);
						text.setStyle(Text::Italic | Text::Bold);

						text.setPosition(x - 60,y - 235);
						wind.draw(text);




					}
					if (dur.count() > 3.5)
					{


						ball.set_position(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
						first.p.setPosition(first.p.getDefaultCoordinates().x, first.p.getDefaultCoordinates().y);
						second.p.setPosition(second.p.getDefaultCoordinates().x, second.p.getDefaultCoordinates().y);
						is_check_second = true;
						first.isCanYouTake = true;
						second.isCanYouTake = true;
						crowdCheck = 1;
						switch (typeOfCam)
						{
						case default_c:
							switch (WhichPlayerIsUsingCam)
							{
							case 1:
								view.setCenter(first.p.getPlayerCoordinates().x + 200, first.p.getPlayerCoordinates().y + 25);
								break;
							case 2:
								view.setCenter(second.p.getPlayerCoordinates().x - 105, second.p.getPlayerCoordinates().y + 25);
								break;
							default:
								break;
							}
							break;
						case split_c:
							view.setCenter(first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y + 25);
							view2.setCenter(second.p.getPlayerCoordinates().x, second.p.getPlayerCoordinates().y+25);
							break;
						default:
							break;
						}
					}

				}
				break;
			default:
				break;
			}
		}
		
		
	}
	int crowdCheck = 1;
	SoundBuffer crowdBuffer;
	Sound crowd;
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
class Bullet
{
	Coordinates main;
	
	float w, h, dx, dy, speed=0.8;
	bool isAlive = false;
	int dir = 0;
	String File;
	Image img;
	Texture texture;
	
public:
	Sprite spr;
	Bullet(Image img, int x,int y,int w ,int h, Character& first)
	{
		this->h = h, this->w = w;
		texture.loadFromImage(img);
		spr.setTexture(texture);
		spr.setTextureRect(IntRect(x, y, this->w, this->h));
		main.x = 0;
		main.y = -100;
		spr.setPosition(main.x, main.y);
		
	}
	void update(float time,Character & first,Character & second)
	{
		if (first.isShoot)
		{
			isAlive = true;
			first.isShoot = false;
			this->dir = first.p.dir;
			main.x = first.p.getPlayerCoordinates().x + 40;
			main.y = first.p.getPlayerCoordinates().y + 50;
			
		}
		
		if (isAlive)
		{	
			
		
			switch (this->dir)
			{
			case right:
				dx = speed, dy = 0; break;
			case left:
				dx = -speed, dy = 0; break;
			case up:
				dx = 0, dy = -speed; break;
			case down:
				dx = 0, dy = speed; break;
			default:
				dx = speed, dy = 0; break;
			
			}
			
			main.x += dx * time;
			main.y += dy * time;
			
			
			bullet_physics(time, first, second);
			if (isAlive)
			{
				spr.setPosition(main.x, main.y);
				
			}
			else
			{
				spr.setPosition(600,800);
				first.isCheck = true;
			}

		

		}
		



		

	}
	void bullet_physics(float time,Character & first, Character & second)
	{

		for (int i = main.y / 32; i < (main.y + h) / 32; i++)
		{
			for (int j = main.x / 32; j < (main.x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'w')
				{
					isAlive = false;
					
				}
			}
		}
		if (abs((main.x - 30) - (second.p.getPlayerCoordinates().x)) < 35 && abs(((main.y - 35) - (second.p.getPlayerCoordinates().y))) < 25)
		{
			isAlive = false;
			second.p.health -= 10;
		}
		
	}
};
class Timer
{
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now(), end = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point start2 = std::chrono::high_resolution_clock::now(), end2 = std::chrono::high_resolution_clock::now();
	int time=300;
	bool check = false,check2=false;
	
public:
	
	int getTime()
	{
		return time;
	}

	void mainTimer(Ball & ball, Character & first, Character& second, Gate &first_g, Gate & second_g,RenderWindow &wind,float x,float y,float size,float size2,int typeOfCam)
	{
		
		if (check)
		{
			if (!check2)
			{
				end = std::chrono::high_resolution_clock::now();
			}
			std::chrono::duration<float> dur = end - start;

			if (int(dur.count())>=1)
			{
				
				if (!check2)
				{
					check = false;
					time--;
				}	
				if (time <=0)
				{
					if (check2)
					{
						end2 = std::chrono::high_resolution_clock::now();
						std::chrono::duration<float> dur2 = end2 - start2;
						first_g.is_on = false;
						second_g.is_on = false;
						if (dur2.count() >= 3)
						{
							Font font;
							font.loadFromFile("CyrilicOld.TTF");
							Text text("Press Enter to Restart", font, size);
							text.setPosition(x - 200, y - 150);
							text.setFillColor(Color::White);
							text.setOutlineThickness(0.5);
							text.setOutlineColor(Color(0, 0, 0));
							text.setStyle(Text::Bold);


							wind.draw(text);
							if (Keyboard::isKeyPressed(Keyboard::Enter))
							{
								ball.isfree = true;
								first.setIsGrabbed(false);
								second.setIsGrabbed(false) ;
								ball.set_position(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
		
								first.p.setPosition(first.p.getDefaultCoordinates().x, first.p.getDefaultCoordinates().y);
								second.p.setPosition(second.p.getDefaultCoordinates().x, second.p.getDefaultCoordinates().y);
								first_g.setScore(0); second_g.setScore(0);
								check = false;
								check2 = false;
								first_g.is_on = true;
								second_g.is_on = true;
								time = 300;
								switch (typeOfCam)
								{
								case default_c:
									switch (WhichPlayerIsUsingCam)
									{
									case 1:
										view.setCenter(first.p.getPlayerCoordinates().x+200, first.p.getPlayerCoordinates().y+25);
										break;
									case 2:
										view.setCenter(second.p.getPlayerCoordinates().x-105, second.p.getPlayerCoordinates().y+25);
										break;
									default:
										break;
									}
									break;
								case split_c:
									view.setCenter(first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y+25);
									view2.setCenter(second.p.getPlayerCoordinates().x, second.p.getPlayerCoordinates().y+25);
									break;
								default:
									break;
								}
								

							}

						}
						else 
						{
							Font font;
							font.loadFromFile("CyrilicOld.TTF");

							Text text("", font, size2);
							
							text.setPosition(x - 200, y - 190);
							if (first_g.getScore() > second_g.getScore())
							{
								text.setFillColor(Color::Blue);
								text.setString("Blue Won!");
							}
							if (first_g.getScore() < second_g.getScore())
							{
								text.setFillColor(Color::Red);
								text.setString("Red Won!");

							}
							if (first_g.getScore() == second_g.getScore())
							{
								text.setFillColor(Color::White);
								text.setString("Draw!");
								text.setPosition(x - 120,y - 210);
							}

							text.setOutlineThickness(0.5);
							text.setOutlineColor(Color(0, 0, 0));
							text.setStyle(Text::Bold);

							
							wind.draw(text);
						}
						
					}
					else
					{
						start2 = std::chrono::high_resolution_clock::now();
						check2 = true;
						check = true;
					}
					
				}
			}
		}
		else 
		{
			start = std::chrono::high_resolution_clock::now();
			check = true;
		}
			
		
		
	}
};
void drawTime(int time,RenderWindow&wind,float x ,float y)
{
	Font font;
	font.loadFromFile("CyrilicOld.TTF");
	Text text(std::to_string(time), font, 60);
	
	text.setFillColor(Color::White);
	

	text.setOutlineThickness(0.5);
	text.setOutlineColor(Color(0, 0, 0));
	text.setStyle(Text::Bold);
	
	text.setPosition(x-35, y-300 );
	wind.draw(text);
}



void menu_(int &typeOfCam,RenderWindow &wind, int & menuCheck,bool menuIsOn, Sound & menuchange, Sound& splitchange,int &soundMenuCheck, int& whichButton)
{
	
	if (menuIsOn)
	{
		
		wind.clear();
		int type = menu;
		Texture menu_file, img_pve, img_pvp, img_split;
		menu_file.loadFromFile("images/menu/Menu.png");
		img_pve.loadFromFile("images/menu/PVE_BUTTON_OFF.png");
		img_pvp.loadFromFile("images/menu/PVP_BUTTON_OFF.png");
		switch (typeOfCam)
		{
		case default_c:
			img_split.loadFromFile("images/menu/SPLIT_BUTTON_OFF.png");
			break;
		case split_c:
			img_split.loadFromFile("images/menu/SPLIT_BUTTON_ON.png");
			break;
		default:
			break;
		}
		
		Sprite sp_menu(menu_file), sp_pve(img_pve), sp_pvp(img_pvp), sp_split(img_split);
		sp_pve.setPosition(0, 0);
		sp_pvp.setPosition(0, 0);
		sp_split.setPosition(0, 0);

		if (IntRect(525, 342, 225, 60).contains(Mouse::getPosition(wind)))
		{
			if (soundMenuCheck == 0 && whichButton != 1)
			{
				soundMenuCheck = 1;
			}
			whichButton = 1;
			type = pve;
			img_pve.loadFromFile("images/menu/PVE_BUTTON_ON.png");
			sp_pve.setTexture(img_pve);
			whichButton = 1;
			if (soundMenuCheck==1)
			{
				menuchange.play();
				soundMenuCheck = 0;
				
			}
			
		}
		if (IntRect(525, 418, 225, 60).contains(Mouse::getPosition(wind)))
		{
			if (soundMenuCheck == 0&& whichButton!=2)
			{
				soundMenuCheck = 1;
			}
			whichButton = 2;
			type = pvp;
			img_pvp.loadFromFile("images/menu/PVP_BUTTON_ON.png");
			sp_pvp.setTexture(img_pvp);
			if (soundMenuCheck == 1)
			{
				menuchange.play();
				soundMenuCheck = 0;
				
			}

		}
		if (IntRect(525, 487, 155, 50).contains(Mouse::getPosition(wind)))
		{
			type = split;
			
			sp_split.setTexture(img_split);
			

		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (type)
			{
			case pve:
				menuCheck = pve;
				menuIsOn = false;
				break;
			case pvp:
				menuCheck = pvp;
				menuIsOn = false;
				break;
			case split:
				splitchange.play();
				if (typeOfCam == default_c)
				{
					typeOfCam = split_c;
				}
				else typeOfCam = default_c;
				break;
			default:
				break;
			}
		}
		wind.draw(sp_menu);
		wind.draw(sp_pve);
		wind.draw(sp_pvp);
		wind.draw(sp_split);
		

	}
	

}

int main()
{
	SoundBuffer menuchangeBuffer;
	menuchangeBuffer.loadFromFile("audio/menuchange.wav");
	
	Sound menuchange(menuchangeBuffer);
	SoundBuffer splitchangeBuffer;
	splitchangeBuffer.loadFromFile("audio/splitchange.wav");
	Sound splitchange(splitchangeBuffer);
	Music menumusic;
	menumusic.openFromFile("audio/menumusic.ogg");
	menumusic.play();
	
	int SizeOfWindowX = 800;
	int soundMenuCheck = 1;
	int SizeOfWindowY = 600;
	int whichButton = 0;
	sf::RenderWindow wind(sf::VideoMode(SizeOfWindowX, SizeOfWindowY), "Wind");
	int typeOfCam= default_c;
	int menuCheck = menu;
	int checkCam = 1;
	bool menuIsOn = true;
	view.reset(FloatRect(0, 0, 800, 600));
	view2.reset(FloatRect(800, 0, 800, 600));
	Ball ball("ball.png", 0,0, 32, 32);
	ball.set_position(767.5, 320);
	int x, y;
	float speed = 0.2;
	srand(time(NULL));
	Character first("Red.png", 0, 196, 96, 96, 3, speed, 96, 96, 96, 96, 110, 110, 288, 0,1);
	Character second("Blue.png", 0, 100, 96, 96, 3, speed, 96, 96, 96, 96, 110, 110, 288, 0,2);
	
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

	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");
	BulletImage.createMaskFromColor(Color(0, 0, 0));
	Bullet bullet_first(BulletImage, 0, 0, 16, 16, first);
	Bullet bullet_second(BulletImage, 0, 0, 16, 16, second);

	Timer timer;
	


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
	
		if (menuCheck!=menu)
		{

			menumusic.stop();
		if (checkCam==1&&menuCheck!=menu)
		{
			checkCam++;
			switch (typeOfCam)
			{
			case default_c:
				x = view.getCenter().x;
				y = view.getCenter().y;
				break;
			case split_c:
				view.setViewport(FloatRect(0, 0, 0.5f, 1.0f));
				view.setSize(SizeOfWindowX / 2, SizeOfWindowY);
				view.setCenter(200, 300);

				view2.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f));
				view2.setSize(SizeOfWindowX / 2, SizeOfWindowY);
				view2.setCenter(1275, 300);
				break;
			default:
				break;
			}
		}
	
		first.move(time, ball,typeOfCam,menuCheck,first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y);
		
		
			second.move(time, ball, typeOfCam, menuCheck, first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y);
		
		
		bullet_first.update(time, first, second);
		bullet_second.update(time, second, first);
		//viewmap(time);
		
		//ShowCoordinate(ev);
		
	
		wind.setView(view);
	
		map.draw_the_map(wind);
		
		ball.update(time, first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y, first.p.dx, first.p.dy, first.get_speed(),first.getIsGrabbed());
		ball.update(time, second.p.getPlayerCoordinates().x, second.p.getPlayerCoordinates().y, second.p.dx, second.p.dy, second.get_speed(),second.getIsGrabbed());
		
		
		wind.draw(bullet_first.spr);
		wind.draw(bullet_second.spr);
		wind.draw(ball.spr);
		wind.draw(first.get_spr());
		wind.draw(second.get_spr());
		
		switch (typeOfCam)
		{
		case default_c:
			Write_Score(wind, std::to_string(gate_second.getScore()), view.getCenter().x - 350, view.getCenter().y - 300, 1);
			Write_Score(wind, std::to_string(gate_first.getScore()), view.getCenter().x + 325, view.getCenter().y - 300, 2);
			timer.mainTimer(ball, first, second, gate_first, gate_second, wind,view.getCenter().x, view.getCenter().y,40,100,typeOfCam);
			drawTime(timer.getTime(), wind, view.getCenter().x, view.getCenter().y);
			gate_first.update(ball, first, second, wind, view.getCenter().x, view.getCenter().y, typeOfCam,menuCheck);
			gate_second.update(ball, first, second, wind ,view.getCenter().x, view.getCenter().y, typeOfCam, menuCheck);
			break;
		case split_c:
			Write_Score(wind, std::to_string(gate_second.getScore()), view.getCenter().x - 140, view.getCenter().y - 300, 1);
			Write_Score(wind, std::to_string(gate_first.getScore()), view.getCenter().x + 130, view.getCenter().y - 300, 2);
			timer.mainTimer(ball, first, second, gate_first, gate_second, wind, view.getCenter().x+70, view.getCenter().y,25,60, typeOfCam);
			drawTime(timer.getTime(), wind, view.getCenter().x, view.getCenter().y);
			gate_first.update(ball, first, second, wind, view.getCenter().x, view.getCenter().y,typeOfCam, menuCheck);
			gate_second.update(ball, first, second, wind, view.getCenter().x, view.getCenter().y, typeOfCam, menuCheck);
			break;
		default:
			break;
		}
		
		
		
		

		if (typeOfCam==split_c )
		{
			
			
			wind.setView(view2);

			map.draw_the_map(wind);



			wind.draw(bullet_first.spr);
			wind.draw(bullet_second.spr);
			wind.draw(ball.spr);
			wind.draw(first.get_spr());
			wind.draw(second.get_spr());
			Write_Score(wind, std::to_string(gate_second.getScore()), view2.getCenter().x - 140, view2.getCenter().y - 300, 1);
			Write_Score(wind, std::to_string(gate_first.getScore()), view2.getCenter().x + 130, view2.getCenter().y - 300, 2);
			timer.mainTimer(ball, first, second, gate_first, gate_second, wind,view2.getCenter().x+70,view2.getCenter().y,25,60, typeOfCam);
			drawTime(timer.getTime(), wind, view2.getCenter().x, view2.getCenter().y);
			gate_first.update(ball, first, second, wind, view2.getCenter().x, view2.getCenter().y, typeOfCam, menuCheck);
			gate_second.update(ball, first, second, wind, view2.getCenter().x, view2.getCenter().y, typeOfCam, menuCheck);
		}
	
		}
		else
		{
			menu_(typeOfCam, wind, menuCheck, menuIsOn, menuchange, splitchange, soundMenuCheck, whichButton);
		}
		wind.display();
		wind.clear();
	}
	return 0;
}


