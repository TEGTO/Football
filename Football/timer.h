#pragma once
class Timer
{
	std::chrono::steady_clock::time_point timerStart = std::chrono::high_resolution_clock::now(), timerEnd = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point timerStartAnother = std::chrono::high_resolution_clock::now(), timerEndAnother = std::chrono::high_resolution_clock::now();
	int matchTime = 300;
	bool check = false, check2 = false;

public:

	int getTime()
	{
		return matchTime;
	}

	void mainTimer(Ball& ball, Player& firstPlayer, Player& secondPlayer, Gate& firstGate, Gate& secondGate, RenderWindow& wind, float x, float y, float textSizeFIrst, float textSizeSecond, int typeOfCam)
	{

		if (check)
		{
			if (!check2)
			{
				timerEnd = std::chrono::high_resolution_clock::now();
			}
			std::chrono::duration<float> timerDuration = timerEnd - timerStart;

			if (int(timerDuration.count()) >= 1)
			{

				if (!check2)
				{
					check = false;
					matchTime--;
				}
				if (matchTime <= 0)
				{
					if (check2)
					{
						timerEndAnother = std::chrono::high_resolution_clock::now();
						std::chrono::duration<float> dur2 = timerEndAnother - timerStartAnother;
						firstGate.isBothGatesEnabled = false;
						secondGate.isBothGatesEnabled = false;
						if (dur2.count() >= 3)
						{
							Font font;
							font.loadFromFile("CyrilicOld.TTF");
							Text text("Press Enter to Restart", font, textSizeFIrst);
							text.setPosition(x - 200, y - 150);
							text.setFillColor(Color::White);
							text.setOutlineThickness(0.5);
							text.setOutlineColor(Color(0, 0, 0));
							text.setStyle(Text::Bold);


							wind.draw(text);
							if (Keyboard::isKeyPressed(Keyboard::Enter))
							{
								ball.isBallFree = true;
								firstPlayer.setIsBallGrabbed(false);
								secondPlayer.setIsBallGrabbed(false);
								ball.setPosition(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);

								firstPlayer.p.setPosition(firstPlayer.p.getDefaultCoordinates().x, firstPlayer.p.getDefaultCoordinates().y);
								secondPlayer.p.setPosition(secondPlayer.p.getDefaultCoordinates().x, secondPlayer.p.getDefaultCoordinates().y);
								firstGate.setScore(0); secondGate.setScore(0);
								check = false;
								check2 = false;
								firstGate.isBothGatesEnabled = true;
								secondGate.isBothGatesEnabled = true;
								matchTime = 300;
								switch (typeOfCam)
								{
								case defaultCamera:
									switch (whichPlayerIsUsingCam)
									{
									case 1:
										view.setCenter(firstPlayer.p.getPlayerCoordinates().x + 200, firstPlayer.p.getPlayerCoordinates().y + 25);
										break;
									case 2:
										view.setCenter(secondPlayer.p.getPlayerCoordinates().x - 105, secondPlayer.p.getPlayerCoordinates().y + 25);
										break;
									default:
										break;
									}
									break;
								case splitCamera:
									view.setCenter(firstPlayer.p.getPlayerCoordinates().x, firstPlayer.p.getPlayerCoordinates().y + 25);
									view2.setCenter(secondPlayer.p.getPlayerCoordinates().x, secondPlayer.p.getPlayerCoordinates().y + 25);
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

							Text text("", font, textSizeSecond);

							text.setPosition(x - 200, y - 190);
							if (firstGate.getScore() > secondGate.getScore())
							{
								text.setFillColor(Color::Blue);
								text.setString("Blue Won!");
							}
							if (firstGate.getScore() < secondGate.getScore())
							{
								text.setFillColor(Color::Red);
								text.setString("Red Won!");

							}
							if (firstGate.getScore() == secondGate.getScore())
							{
								text.setFillColor(Color::White);
								text.setString("Draw!");
								text.setPosition(x - 120, y - 210);
							}

							text.setOutlineThickness(0.5);
							text.setOutlineColor(Color(0, 0, 0));
							text.setStyle(Text::Bold);


							wind.draw(text);
						}

					}
					else
					{
						timerStartAnother = std::chrono::high_resolution_clock::now();
						check2 = true;
						check = true;
					}

				}
			}
		}
		else
		{
			timerStart = std::chrono::high_resolution_clock::now();
			check = true;
		}



	}
};