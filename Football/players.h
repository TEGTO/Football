#pragma once
class Player
{
public:
	bool isntShootingCheck = true;
	bool CanTakeBall = true;
	Player(String FIle, int x, int y, float h, float w, int CurrentFrameMax, double speed, float LeftAnimPosX, float RightAnimPosX, float UpAnimPosX, float DownAnimPosX, float LeftAnimPosY, float RightAnimPosY, float UpAnimPosY, float DownAnimPosY, int gameModeType)
	{
		p.setPar(FIle, x, y, h, w);
		this->CurrentFrameMax = CurrentFrameMax;
		this->currentSpeed = speed;
		this->RightAnimPosX = RightAnimPosX;
		this->LeftAnimPosX = LeftAnimPosX;
		this->UpAnimPosX = UpAnimPosX;
		this->DownAnimPosX = DownAnimPosX;
		this->RightAnimPosY = RightAnimPosY;
		this->LeftAnimPosY = LeftAnimPosY;
		this->UpAnimPosY = UpAnimPosY;
		this->DownAnimPosY = DownAnimPosY;
		this->gameModeType = gameModeType;
		shootBuffer.loadFromFile("audio/shooting2.wav");
		shoot.setBuffer(shootBuffer);
		walkingBuffer.loadFromFile("audio/walking2.wav");
		walking.setBuffer(walkingBuffer);
		kickBuffer.loadFromFile("audio/kick.wav");
		kick.setBuffer(kickBuffer);
	}

	void setSpeed(double speed)
	{
		this->currentSpeed = speed;
	}
	void setAnimSpeed(double animationSpeed)
	{
		this->animationSpeed = animationSpeed;
	}
	void enableReversRect(int dir)
	{
		switch (dir)
		{
		case right:
			ReverseRightAnimPosX = RightAnimPosX;
			isRightReverseEnabled *= -1;
			break;
		case left:
			ReverseLeftAnimPosX = LeftAnimPosX;
			isLeftReverseEnabled *= -1;
			break;
		case up:
			ReverseUpAnimPosY = UpAnimPosY;
			isUpReverseEnabled *= -1;
			break;
		case down:
			ReverseDownAnimPosY = DownAnimPosY;
			isDownReverseEnabled *= -1;
			break;
		default:
			break;
		}
	}
	void disableReversRect(int dir)
	{
		switch (dir)
		{
		case right:
			ReverseRightAnimPosX = 0;
			isRightReverseEnabled = 1;
			break;
		case left:
			ReverseLeftAnimPosX = 0;
			isLeftReverseEnabled = 1;
			break;
		case up:
			ReverseUpAnimPosY = 0;
			isUpReverseEnabled = 1;
			break;
		case down:
			ReverseDownAnimPosY = 0;
			isDownReverseEnabled = 1;
			break;
		default:
			break;
		}
	}
	Sprite& getSpr()
	{
		return p.spr;
	}
	void move(float time, Ball& ball, int typeOfCam, int typeOfGame, float firstPlayerX, float firstPlayerY)
	{

		switch (gameModeType)
		{
		case 1:
			if (isWalking == 2)
			{

				endTimerWalking = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> durationWalking = endTimerWalking - startTimerWalking;
				//durationWalking after that the timer expired
				if (durationWalking.count() > timeForWalkingAfterTimer)
				{

					isWalking = 0;
				}
			}
			if (checkIsSpeedBoosted == 1)
			{
				end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> dur = end - start;
				if (dur.count() > 3.0)
				{
					currentSpeed = defaultSpeed;
					checkIsSpeedBoosted = 0;
					ball.setSpeedAnim(0.02);
					animationSpeed = 0.005;
					timeForWalkingAfterTimer = 0.7;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				p.dir = left; p.speed = currentSpeed;
				CurrentFrameX += animationSpeed * time;
				if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
				p.spr.setTextureRect(IntRect(LeftAnimPosX * int(CurrentFrameX) + ReverseLeftAnimPosX, LeftAnimPosY, isLeftReverseEnabled * p.h, p.w));

				getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
				whichPlayerIsUsingCam = 1;
				if (isWalking == 0)
				{

					isWalking = 1;
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{

				p.dir = right; p.speed = currentSpeed;
				CurrentFrameX += animationSpeed * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(RightAnimPosX * int(CurrentFrameX) + ReverseRightAnimPosX, RightAnimPosY, isRightReverseEnabled * p.h, p.w));
				getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
				whichPlayerIsUsingCam = 1;
				if (isWalking == 0)
				{

					isWalking = 1;
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				p.dir = up; p.speed = currentSpeed;
				CurrentFrameX += animationSpeed * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(UpAnimPosX * int(CurrentFrameX), UpAnimPosY + ReverseUpAnimPosY, p.h, p.w * isUpReverseEnabled));
				getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
				whichPlayerIsUsingCam = 1;
				if (isWalking == 0)
				{

					isWalking = 1;
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{


				p.dir = down; p.speed = currentSpeed;
				CurrentFrameX += animationSpeed * time;
				if (CurrentFrameX > CurrentFrameMax)
				{
					CurrentFrameX = 0;
				}
				p.spr.setTextureRect(IntRect(DownAnimPosX * int(CurrentFrameX), DownAnimPosY + ReverseDownAnimPosY, p.h, p.w * isDownReverseEnabled));
				getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
				whichPlayerIsUsingCam = 1;
				if (isWalking == 0)
				{

					isWalking = 1;
				}

			}
			if (isWalking == 1)
			{
				isWalking = 2;
				startTimerWalking = std::chrono::high_resolution_clock::now();
				walking.play();


			}

			if (Keyboard::isKeyPressed(Keyboard::LShift))
			{

				if (checkIsSpeedBoosted == 0)
				{
					defaultSpeed = currentSpeed;
					currentSpeed += 0.15;
					checkIsSpeedBoosted = 1;
					start = std::chrono::high_resolution_clock::now();
					ball.setSpeedAnim(0.03);
					animationSpeed = 0.01;
					timeForWalkingAfterTimer = 0.5;
				}

			}
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				if (CanTakeBall)
				{


					if (ball.isBallFree)
					{

						switch (p.dir)
						{
						case right:
							if (p.getPlayerCoordinates().x<ball.getCoordinates().x && p.getPlayerCoordinates().x + 150 > ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
							{
								if (ball.isBallFree)
								{
									ball.isBallFree = false;
									isBallGrabbed = true;
								}
							}
							break;
						case left:
							if (p.getPlayerCoordinates().x > ball.getCoordinates().x && p.getPlayerCoordinates().x - 150 < ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
							{
								if (ball.isBallFree)
								{
									ball.isBallFree = false;
									isBallGrabbed = true;
								}
							}
							break;
						case up:
							if (p.getPlayerCoordinates().y > ball.getCoordinates().y && p.getPlayerCoordinates().y - 100 < ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
							{
								if (ball.isBallFree)
								{
									ball.isBallFree = false;
									isBallGrabbed = true;
								}
							}
							break;
						case down:
							if (p.getPlayerCoordinates().y < ball.getCoordinates().y && p.getPlayerCoordinates().y + 100 > ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
							{
								if (ball.isBallFree)
								{
									ball.isBallFree = false;
									isBallGrabbed = true;
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

				if (isBallGrabbed)
				{

					switch (p.dir)
					{
					case right:

						ball.isBallFree = true;
						ball.setPosition(p.getPlayerCoordinates().x + 200, p.getPlayerCoordinates().y + 60);
						if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
						if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
						if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
						if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }

						break;
					case left:

						ball.isBallFree = true;
						ball.setPosition(p.getPlayerCoordinates().x - 150, p.getPlayerCoordinates().y + 60);
						if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
						if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
						if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
						if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }
						break;
					case up:
						ball.isBallFree = true;
						ball.setPosition(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y - 120);
						if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
						if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
						if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
						if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }
						break;
					case down:
						ball.isBallFree = true;
						ball.setPosition(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y + 220);
						if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
						if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
						if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
						if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }
						break;
					default:
						break;
					}
					isBallGrabbed = false;
					kick.play();
				}
			}
			if (isntShootingCheck)
			{
				if (Keyboard::isKeyPressed(Keyboard::F))
				{

					shoot.play();
					isShoot = true;
					isntShootingCheck = false;
				}
			}

			p.update(time);

			break;
		case 2:
			if (typeOfGame != pve)
			{
				if (isWalking == 2)
				{

					endTimerWalking = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur_walk = endTimerWalking - startTimerWalking;
					if (dur_walk.count() > timeForWalkingAfterTimer)
					{

						isWalking = 0;
					}
				}
				if (checkIsSpeedBoosted == 1)
				{

					end = std::chrono::high_resolution_clock::now();

					std::chrono::duration<float> dur = end - start;

					if (dur.count() > 3.0)
					{
						currentSpeed = defaultSpeed;
						checkIsSpeedBoosted = 0;
						ball.setSpeedAnim(0.02);
						animationSpeed = 0.005;

					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					p.dir = left; p.speed = currentSpeed;
					CurrentFrameX += animationSpeed * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(LeftAnimPosX * int(CurrentFrameX) + ReverseLeftAnimPosX, LeftAnimPosY, isLeftReverseEnabled * p.h, p.w));
					switch (typeOfCam)
					{
					case defaultCamera:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case splitCamera:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					whichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}



				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					p.dir = right; p.speed = currentSpeed;
					CurrentFrameX += animationSpeed * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(RightAnimPosX * int(CurrentFrameX) + ReverseRightAnimPosX, RightAnimPosY, isRightReverseEnabled * p.h, p.w));
					switch (typeOfCam)
					{
					case defaultCamera:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case splitCamera:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					whichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					p.dir = up; p.speed = currentSpeed;
					CurrentFrameX += animationSpeed * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(UpAnimPosX * int(CurrentFrameX), UpAnimPosY + ReverseUpAnimPosY, p.h, p.w * isUpReverseEnabled));
					switch (typeOfCam)
					{
					case defaultCamera:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case splitCamera:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					whichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					p.dir = down; p.speed = currentSpeed;
					CurrentFrameX += animationSpeed * time;
					if (CurrentFrameX > CurrentFrameMax)
					{
						CurrentFrameX = 0;
					}
					p.spr.setTextureRect(IntRect(DownAnimPosX * int(CurrentFrameX), DownAnimPosY + ReverseDownAnimPosY, p.h, p.w * isDownReverseEnabled));
					switch (typeOfCam)
					{
					case defaultCamera:
						getPlayerCoordinatesForView(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y, typeOfCam);
						break;
					case splitCamera:
						getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y);
						break;
					default:
						break;
					}
					whichPlayerIsUsingCam = 2;
					if (isWalking == 0)
					{

						isWalking = 1;
					}

				}
				if (isWalking == 1)
				{
					isWalking = 2;
					startTimerWalking = std::chrono::high_resolution_clock::now();
					walking.play();


				}
				if (Keyboard::isKeyPressed(Keyboard::J))
				{

					if (checkIsSpeedBoosted == 0)
					{
						defaultSpeed = currentSpeed;
						currentSpeed += 0.15;
						checkIsSpeedBoosted = 1;
						start = std::chrono::high_resolution_clock::now();
						ball.setSpeedAnim(0.03);
						animationSpeed = 0.01;
					}

				}
				if (Keyboard::isKeyPressed(Keyboard::K))
				{
					if (CanTakeBall)
					{


						if (ball.isBallFree)
						{

							switch (p.dir)
							{
							case right:
								if (p.getPlayerCoordinates().x<ball.getCoordinates().x && p.getPlayerCoordinates().x + 150 > ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
								{
									if (ball.isBallFree)
									{
										ball.isBallFree = false;
										isBallGrabbed = true;
									}
								}
								break;
							case left:
								if (p.getPlayerCoordinates().x > ball.getCoordinates().x && p.getPlayerCoordinates().x - 150 < ball.getCoordinates().x && abs(p.getPlayerCoordinates().y + 50 - ball.getCoordinates().y) <= 64)
								{
									if (ball.isBallFree)
									{
										ball.isBallFree = false;
										isBallGrabbed = true;
									}
								}
								break;
							case up:
								if (p.getPlayerCoordinates().y > ball.getCoordinates().y && p.getPlayerCoordinates().y - 100 < ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
								{
									if (ball.isBallFree)
									{
										ball.isBallFree = false;
										isBallGrabbed = true;
									}
								}
								break;
							case down:
								if (p.getPlayerCoordinates().y < ball.getCoordinates().y && p.getPlayerCoordinates().y + 100 > ball.getCoordinates().y && abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) <= 80)
								{
									if (ball.isBallFree)
									{
										ball.isBallFree = false;
										isBallGrabbed = true;
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

					if (isBallGrabbed)
					{

						switch (p.dir)
						{
						case right:

							ball.isBallFree = true;
							ball.setPosition(p.getPlayerCoordinates().x + 200, p.getPlayerCoordinates().y + 60);
							if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }

							break;
						case left:

							ball.isBallFree = true;
							ball.setPosition(p.getPlayerCoordinates().x - 150, p.getPlayerCoordinates().y + 60);
							if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }
							break;
						case up:
							ball.isBallFree = true;
							ball.setPosition(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y - 120);
							if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }
							break;
						case down:
							ball.isBallFree = true;
							ball.setPosition(p.getPlayerCoordinates().x + 35, p.getPlayerCoordinates().y + 220);
							if (ball.getCoordinates().x <= 22) { ball.setPosition(30, ball.getCoordinates().y); }
							if (ball.getCoordinates().x > 1510) { ball.setPosition(1490, ball.getCoordinates().y); }
							if (ball.getCoordinates().y < 17) { ball.setPosition(ball.getCoordinates().x, 32); }
							if (ball.getCoordinates().y > 629) { ball.setPosition(ball.getCoordinates().x, 605); }
							break;
						default:
							break;
						}
						isBallGrabbed = false;
					}

				}
				if (isntShootingCheck)
				{
					if (Keyboard::isKeyPressed(Keyboard::I))
					{
						shoot.play();
						isShoot = true;
						isntShootingCheck = false;
					}
				}

			}


			else
			{
				if (isWalking == 2)
				{

					endTimerWalking = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur_walk = endTimerWalking - startTimerWalking;
					if (dur_walk.count() > timeForWalkingAfterTimer)
					{

						isWalking = 0;
					}
				}


				if (!isBallGrabbed)
				{

					if (abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) > 30)
					{

						if (p.getPlayerCoordinates().x > ball.getCoordinates().x)
						{
							p.dir = left; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(LeftAnimPosX * int(CurrentFrameX) + ReverseLeftAnimPosX, LeftAnimPosY, isLeftReverseEnabled * p.h, p.w));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }

						}
						if (p.getPlayerCoordinates().x < ball.getCoordinates().x)
						{
							p.dir = right; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(RightAnimPosX * int(CurrentFrameX) + ReverseRightAnimPosX, RightAnimPosY, isRightReverseEnabled * p.h, p.w));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }

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
							p.dir = down; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(DownAnimPosX * int(CurrentFrameX), DownAnimPosY + ReverseDownAnimPosY, p.h, p.w * isDownReverseEnabled));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }

						}
						if (p.getPlayerCoordinates().y > ball.getCoordinates().y)
						{
							p.dir = up; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(UpAnimPosX * int(CurrentFrameX), UpAnimPosY + ReverseUpAnimPosY, p.h, p.w * isUpReverseEnabled));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }

						}
						if (isWalking == 0)
						{

							isWalking = 1;
						}
					}
					if (abs(p.getPlayerCoordinates().x - ball.getCoordinates().x) < 30 && abs(p.getPlayerCoordinates().y - ball.getCoordinates().y) < 20)
					{
						if (CanTakeBall)
						{
							ball.isBallFree = false;
							isBallGrabbed = true;
						}

					}

				}



				if (isBallGrabbed)
				{
					if (abs(p.getPlayerCoordinates().x - 119) > 20)
					{
						if (p.getPlayerCoordinates().x >= 119)
						{
							p.dir = left; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(LeftAnimPosX * int(CurrentFrameX) + ReverseLeftAnimPosX, LeftAnimPosY, isLeftReverseEnabled * p.h, p.w));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }

						}
						if (p.getPlayerCoordinates().x < 119)
						{
							p.dir = right; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(RightAnimPosX * int(CurrentFrameX) + ReverseRightAnimPosX, RightAnimPosY, isRightReverseEnabled * p.h, p.w));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }

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
							p.dir = down; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(DownAnimPosX * int(CurrentFrameX), DownAnimPosY + ReverseDownAnimPosY, p.h, p.w * isDownReverseEnabled));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						}
						if (p.getPlayerCoordinates().y > 329)
						{
							p.dir = up; p.speed = currentSpeed;
							CurrentFrameX += animationSpeed * time;
							if (CurrentFrameX > CurrentFrameMax) { CurrentFrameX = 0; }
							p.spr.setTextureRect(IntRect(UpAnimPosX * int(CurrentFrameX), UpAnimPosY + ReverseUpAnimPosY, p.h, p.w * isUpReverseEnabled));
							if (typeOfCam == splitCamera) { getPlayerCoordinatesForView2(p.getPlayerCoordinates().x, p.getPlayerCoordinates().y); }
						}
						if (isWalking == 0)
						{

							isWalking = 1;
						}
					}


				}
				if (abs(p.getPlayerCoordinates().y - firstPlayerY) <= 20)
				{
					if (isntShootingCheck)
					{
						if (rand() % 2 == 0)
						{
							shoot.play();
							isShoot = true;
							isntShootingCheck = false;
						}


					}
				}
			}



			if (isWalking == 1)
			{
				isWalking = 2;
				startTimerWalking = std::chrono::high_resolution_clock::now();
				walking.play();


			}
			p.update(time);
		default:
			break;
		}
		if (p.health <= 0)
		{
			if (!ball.isBallFree)
			{
				ball.isBallFree = true;
				isBallGrabbed = false;

			}
			if (isBallGrabbed && gameModeType == 2 && typeOfGame == pve)
			{
				ball.isBallFree = true;
				isBallGrabbed = false;

			}
			p.setPosition(p.getDefaultCoordinates().x, p.getDefaultCoordinates().y);
			p.health = 20;

			switch (typeOfCam)
			{
			case defaultCamera:
				if (whichPlayerIsUsingCam == gameModeType)
				{
					switch (whichPlayerIsUsingCam)
					{
					case 1:
						view.setCenter(p.getPlayerCoordinates().x + 200, p.getPlayerCoordinates().y + 25);
						break;
					case 2:
						view.setCenter(p.getPlayerCoordinates().x - 105, p.getPlayerCoordinates().y + 25);
						break;
					default:
						break;
					}

				}
				break;
			case splitCamera:
				switch (gameModeType)
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

	float getSpeed()
	{
		return currentSpeed;
	}
	Character p;
	bool getIsBallGrabbed()
	{
		return isBallGrabbed;
	}
	void setIsBallGrabbed(bool isgrabbed)
	{
		this->isBallGrabbed = isgrabbed;
	}
	bool  isShoot = false;
private:
	int gameModeType, isWalking = 0;
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now(), end = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point startTimerWalking = std::chrono::high_resolution_clock::now(), endTimerWalking = std::chrono::high_resolution_clock::now();
	float defaultSpeed;
	int checkIsSpeedBoosted = 0;
	float CurrentFrameX = 0;
	int CurrentFrameMax;
	double currentSpeed;
	bool isBallGrabbed = false;
	float LeftAnimPosX, RightAnimPosX, UpAnimPosX, DownAnimPosX;
	float LeftAnimPosY, RightAnimPosY, UpAnimPosY, DownAnimPosY;
	double animationSpeed = 0.005;
	float ReverseLeftAnimPosX = 0, ReverseRightAnimPosX = 0;
	float ReverseUpAnimPosY = 0, ReverseDownAnimPosY = 0;
	int isRightReverseEnabled = 1, isLeftReverseEnabled = 1, isUpReverseEnabled = 1, isDownReverseEnabled = 1; // 1 - reverse is disabled, -1 - reverse is enabled
	SoundBuffer shootBuffer;
	SoundBuffer walkingBuffer;
	SoundBuffer kickBuffer;
	Sound shoot;
	Sound walking;
	Sound kick;
	float timeForWalkingAfterTimer = 0.7;
};