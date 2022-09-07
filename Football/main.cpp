#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"map.h"
#include"view.h"
#include<iostream>
#include <chrono>
#include<cmath>
#include<thread>
#include "coordinates.h"
#include "character.h"
#include "enums.h"
#include "ball.h"
#include "players.h"
#include "mapDrawing.h"
#include "gate.h"
#include "bullet.h"
#include "timer.h"
using namespace sf;






void ShowCoordinate(Event &ev)//Debug foo
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		std::cout << "x= " << ev.mouseMove.x << std::endl;
		std::cout << "y= " << ev.mouseMove.y << std::endl;
	}
}

void writingScore(RenderWindow &wind,String s,float x , float y,int ColorOfTeam)
{
	Font font;
	font.loadFromFile("CyrilicOld.TTF");
	Text text(s,font, 60);
	//1 - red team , 2 - blue team
	switch (ColorOfTeam)
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



void mainMenu(int &typeOfCam,RenderWindow &wind, int & menuCheck,bool isMenuEnabled, Sound & menuChangeButtonSound, Sound& splitChangeButtonSound,int &soundMenuCheck, int& whichButton,float x ,float y)
{
	
	if (isMenuEnabled)
	{
		
		wind.clear();
		int type = menu;
		Texture textureMenuBackground, textureButtonPVE, textureButtonPVP, textureButtonSPLIT;
		textureMenuBackground.loadFromFile("images/menu/Menu.png");
		textureButtonPVE.loadFromFile("images/menu/PVE_BUTTON_OFF.png");
		textureButtonPVP.loadFromFile("images/menu/PVP_BUTTON_OFF.png");
		switch (typeOfCam)
		{
		case defaultCamera:
			textureButtonSPLIT.loadFromFile("images/menu/SPLIT_BUTTON_OFF.png");
			break;
		case splitCamera:
			textureButtonSPLIT.loadFromFile("images/menu/SPLIT_BUTTON_ON.png");
			break;
		default:
			break;
		}
		
		Sprite spriteMenuBackground(textureMenuBackground), spriteButtonPVE(textureButtonPVE), spriteButtonPVP(textureButtonPVP), spriteButtonSPLIT(textureButtonSPLIT);
		spriteButtonPVE.setPosition(x, y);
		spriteButtonPVP.setPosition(x, y);
		spriteButtonSPLIT.setPosition(x, y);

		if (IntRect(525, 342, 225, 60).contains(Mouse::getPosition(wind)))
		{
			if (soundMenuCheck == 0 && whichButton != 1)
			{
				soundMenuCheck = 1;
			}
			whichButton = 1;
			type = pve;
			textureButtonPVE.loadFromFile("images/menu/PVE_BUTTON_ON.png");
			spriteButtonPVE.setTexture(textureButtonPVE);
			whichButton = 1;
			if (soundMenuCheck==1)
			{
				menuChangeButtonSound.play();
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
			textureButtonPVP.loadFromFile("images/menu/PVP_BUTTON_ON.png");
			spriteButtonPVP.setTexture(textureButtonPVP);
			if (soundMenuCheck == 1)
			{
				menuChangeButtonSound.play();
				soundMenuCheck = 0;
				
			}

		}
		if (IntRect(525, 487, 155, 50).contains(Mouse::getPosition(wind)))
		{
			type = split;
			
			spriteButtonSPLIT.setTexture(textureButtonSPLIT);
			

		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (type)
			{
			case pve:
				menuCheck = pve;
				isMenuEnabled = false;
				break;
			case pvp:
				menuCheck = pvp;
				isMenuEnabled = false;
				break;
			case split:
				splitChangeButtonSound.play();
				if (typeOfCam == defaultCamera)
				{
					typeOfCam = splitCamera;
				}
				else typeOfCam = defaultCamera;
				break;
			default:
				break;
			}
		}
		wind.draw(spriteMenuBackground);
		wind.draw(spriteButtonPVE);
		wind.draw(spriteButtonPVP);
		wind.draw(spriteButtonSPLIT);
		

	}
	

}

int main()
{restart:
	int SizeOfWindowX = 800;
	int soundMenuCheck = 1;
	int SizeOfWindowY = 600;
	int whichButton = 0;
	
	SoundBuffer menuchangeBuffer;
	menuchangeBuffer.loadFromFile("audio/menuchange.wav");
	sf::RenderWindow wind(sf::VideoMode(SizeOfWindowX, SizeOfWindowY), "Wind");
	Sound menuchange(menuchangeBuffer);
	SoundBuffer splitchangeBuffer;
	splitchangeBuffer.loadFromFile("audio/splitchange.wav");
	Sound splitchange(splitchangeBuffer);
	Music menumusic;
	menumusic.openFromFile("audio/menumusic.ogg");
	menumusic.play();
	
	
	int typeOfCam= defaultCamera;
	int currentStatusOfGame = menu;
	int checkCam = 1;
	bool menuIsOn = true;
	view.reset(FloatRect(0, 0, 800, 600));
	view2.reset(FloatRect(800, 0, 800, 600));
	Ball ball("ball.png", 0,0, 32, 32);
	ball.setPosition(767.5, 320);
	int camCenterX, camCenterY;
	float defaultPlayerSpeed = 0.2;
	srand(time(NULL));
	Player firstPlayer("Red.png", 0, 196, 96, 96, 3, defaultPlayerSpeed, 96, 96, 96, 96, 110, 110, 288, 0,1);
	Player secondPlayer("Blue.png", 0, 100, 96, 96, 3, defaultPlayerSpeed, 96, 96, 96, 96, 110, 110, 288, 0,2);
	
	firstPlayer.enableReversRect(0);
	secondPlayer.enableReversRect(0);
	//1 - left gate, 2 - right gate
	Gate leftGate(lGate, 119, 323);
	Gate rightGate(rGate, 1407, 323);
	Map map("map.png");
	Clock clock;
	firstPlayer.p.setPosition(200, 275);
	secondPlayer.p.setPosition(1275, 275);
	firstPlayer.p.setDefaultCoordinates(200, 275);
	secondPlayer.p.setDefaultCoordinates(1275, 275);
	ball.setDefaultCoordinates(767.5, 320);

	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");
	BulletImage.createMaskFromColor(Color(0, 0, 0));
	Bullet firstPlayerBullet(BulletImage, 0, 0, 16, 16, firstPlayer);
	Bullet secondPlayerBullet(BulletImage, 0, 0, 16, 16, secondPlayer);

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
		if (Keyboard::isKeyPressed(Keyboard::Escape))// if we want to back to the menu 
		{
			wind.clear();
			currentStatusOfGame = menu;
			ball.isBallFree = true;
			firstPlayer.p.setPosition(200, 275);
			secondPlayer.p.setPosition(1275, 275);
			firstPlayer.p.setDefaultCoordinates(200, 275);
			secondPlayer.p.setDefaultCoordinates(1275, 275);
			firstPlayer.setIsBallGrabbed(false);
			secondPlayer.setIsBallGrabbed(false);
			ball.setDefaultCoordinates(767.5, 320);
			leftGate.isFirstGateEnabled = true;
			leftGate.isSecondGateEnabled = true;
			rightGate.isFirstGateEnabled = true;
			rightGate.isSecondGateEnabled = true;
			leftGate.setScore(0);
			rightGate.setScore(0);
			leftGate.isBothGatesEnabled=false;
			rightGate.isBothGatesEnabled = false;
			
			typeOfCam = defaultCamera;
			view.setViewport((FloatRect(0, 0, 1.0f, 1)));

			goto restart;
		
		}

		if (currentStatusOfGame!=menu)
		{
			leftGate.isBothGatesEnabled = true;
			rightGate.isBothGatesEnabled = true;
			menumusic.stop();
		if (checkCam==1&&currentStatusOfGame!=menu)
		{
			checkCam++;
			switch (typeOfCam)
			{
			case defaultCamera:
				camCenterX = view.getCenter().x;
				camCenterY = view.getCenter().y;
				break;
			case splitCamera:
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
	
		firstPlayer.move(time, ball,typeOfCam,currentStatusOfGame,firstPlayer.p.getPlayerCoordinates().x, firstPlayer.p.getPlayerCoordinates().y);
		secondPlayer.move(time, ball, typeOfCam, currentStatusOfGame, firstPlayer.p.getPlayerCoordinates().x, firstPlayer.p.getPlayerCoordinates().y);
		
		
		firstPlayerBullet.update(time, firstPlayer, secondPlayer);
		secondPlayerBullet.update(time, secondPlayer, firstPlayer);
		//viewmap(time);
		
		//ShowCoordinate(ev);
		
	
		wind.setView(view);
	
		map.drawTheMap(wind);
		
		ball.update(time, firstPlayer.p.getPlayerCoordinates().x, firstPlayer.p.getPlayerCoordinates().y, firstPlayer.p.dx, firstPlayer.p.dy, firstPlayer.getSpeed(),firstPlayer.getIsBallGrabbed());
		ball.update(time, secondPlayer.p.getPlayerCoordinates().x, secondPlayer.p.getPlayerCoordinates().y, secondPlayer.p.dx, secondPlayer.p.dy, secondPlayer.getSpeed(),secondPlayer.getIsBallGrabbed());
		
		
		wind.draw(firstPlayerBullet.spr);
		wind.draw(secondPlayerBullet.spr);
		wind.draw(ball.spr);
		wind.draw(firstPlayer.getSpr());
		wind.draw(secondPlayer.getSpr());
		
		switch (typeOfCam)
		{
		case defaultCamera:
			writingScore(wind, std::to_string(rightGate.getScore()), view.getCenter().x - 350, view.getCenter().y - 300, 1);
			writingScore(wind, std::to_string(leftGate.getScore()), view.getCenter().x + 325, view.getCenter().y - 300, 2);
			timer.mainTimer(ball, firstPlayer, secondPlayer, leftGate, rightGate, wind,view.getCenter().x, view.getCenter().y,40,100,typeOfCam);
			drawTime(timer.getTime(), wind, view.getCenter().x, view.getCenter().y);
			leftGate.update(ball, firstPlayer, secondPlayer, wind, view.getCenter().x, view.getCenter().y, typeOfCam,currentStatusOfGame);
			rightGate.update(ball, firstPlayer, secondPlayer, wind ,view.getCenter().x, view.getCenter().y, typeOfCam, currentStatusOfGame);
			break;
		case splitCamera:
			writingScore(wind, std::to_string(rightGate.getScore()), view.getCenter().x - 140, view.getCenter().y - 300, 1);
			writingScore(wind, std::to_string(leftGate.getScore()), view.getCenter().x + 130, view.getCenter().y - 300, 2);
			timer.mainTimer(ball, firstPlayer, secondPlayer, leftGate, rightGate, wind, view.getCenter().x+70, view.getCenter().y,25,60, typeOfCam);
			drawTime(timer.getTime(), wind, view.getCenter().x, view.getCenter().y);
			leftGate.update(ball, firstPlayer, secondPlayer, wind, view.getCenter().x, view.getCenter().y,typeOfCam, currentStatusOfGame);
			rightGate.update(ball, firstPlayer, secondPlayer, wind, view.getCenter().x, view.getCenter().y, typeOfCam, currentStatusOfGame);
			break;
		default:
			break;
		}
		
		
		
		

		if (typeOfCam==splitCamera )
		{
			
			
			wind.setView(view2);

			map.drawTheMap(wind);



			wind.draw(firstPlayerBullet.spr);
			wind.draw(secondPlayerBullet.spr);
			wind.draw(ball.spr);
			wind.draw(firstPlayer.getSpr());
			wind.draw(secondPlayer.getSpr());
			writingScore(wind, std::to_string(rightGate.getScore()), view2.getCenter().x - 140, view2.getCenter().y - 300, 1);
			writingScore(wind, std::to_string(leftGate.getScore()), view2.getCenter().x + 130, view2.getCenter().y - 300, 2);
			timer.mainTimer(ball, firstPlayer, secondPlayer, leftGate, rightGate, wind,view2.getCenter().x+70,view2.getCenter().y,25,60, typeOfCam);
			drawTime(timer.getTime(), wind, view2.getCenter().x, view2.getCenter().y);
			leftGate.update(ball, firstPlayer, secondPlayer, wind, view2.getCenter().x, view2.getCenter().y, typeOfCam, currentStatusOfGame);
			rightGate.update(ball, firstPlayer, secondPlayer, wind, view2.getCenter().x, view2.getCenter().y, typeOfCam, currentStatusOfGame);
		}
	
		}
		else
		{
			mainMenu(typeOfCam, wind, currentStatusOfGame, menuIsOn, menuchange, splitchange, soundMenuCheck, whichButton,0,0);
		}
		wind.display();
		wind.clear();
	}
	return 0;
}


