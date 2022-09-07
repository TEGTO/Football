#pragma once
class Gate
{
	std::chrono::steady_clock::time_point timerStart = std::chrono::high_resolution_clock::now(), timeEnd = std::chrono::high_resolution_clock::now();

	int score = 0;
	int whichGate = 1;
	Coordinates gateCoordinates;


public:
	bool isBothGatesEnabled = true;
	bool isFirstGateEnabled;
	bool isSecondGateEnabled;
	void setScore(int score)
	{
		this->score = score;
	}
	int getScore()
	{
		return score;
	}
	Gate(int whichGate, float x, float y)
	{
		//1 - left gate, 2 - right gate
		this->whichGate = whichGate;
		gateCoordinates.x = x;
		gateCoordinates.y = y;
		crowdBuffer.loadFromFile("audio/crowd.wav");
		crowdSound.setBuffer(crowdBuffer);

	}
	void update(Ball& ball, Player& first, Player& second, RenderWindow& wind, float x, float y, int typeOfCam, int currentStatusOfGame)
	{
		if (isBothGatesEnabled)
		{
		
			switch (whichGate)
			{
			case 1:
				if (isFirstGateEnabled && isSecondGateEnabled)
				{
					if (ball.getCoordinates().x <= gateCoordinates.x && ball.getCoordinates().x <= gateCoordinates.x + 200 && abs(ball.getCoordinates().y - gateCoordinates.y) <= 70)
					{
						score++;
						isFirstGateEnabled = false;
						timerStart = std::chrono::high_resolution_clock::now();
					}
					if (currentStatusOfGame == pve && second.getIsBallGrabbed() == true)
					{
						if (ball.getCoordinates().x <= gateCoordinates.x + 20 && ball.getCoordinates().x <= gateCoordinates.x + 350 && abs(ball.getCoordinates().y - gateCoordinates.y) <= 140)
						{

							score++;
							isFirstGateEnabled = false;
							timerStart = std::chrono::high_resolution_clock::now();

						}
					}
				}
				if (!isFirstGateEnabled)
				{

					timeEnd = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur = timeEnd - timerStart;

					if (dur.count() > 0 && dur.count() < 3)
					{

						first.CanTakeBall = false;
						second.CanTakeBall = false;
						first.setIsBallGrabbed(false);
						second.setIsBallGrabbed(false);
						ball.isBallFree = true;
						Font font;
						font.loadFromFile("CyrilicOld.TTF");
						Text text("Goal!", font, 70);
						if (crowdCheck == 1)
						{
							crowdSound.play();
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


						ball.setPosition(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
						first.p.setPosition(first.p.getDefaultCoordinates().x, first.p.getDefaultCoordinates().y);
						second.p.setPosition(second.p.getDefaultCoordinates().x, second.p.getDefaultCoordinates().y);
						first.CanTakeBall = true;
						second.CanTakeBall = true;
						isFirstGateEnabled = true;
						crowdCheck = 1;
						switch (typeOfCam)
						{
						case defaultCamera:
							switch (whichPlayerIsUsingCam)
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
						case splitCamera:
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
				if (isSecondGateEnabled && isFirstGateEnabled)
				{
					if (ball.getCoordinates().x >= gateCoordinates.x && ball.getCoordinates().x >= gateCoordinates.x - 200 && abs(ball.getCoordinates().y - gateCoordinates.y) <= 70)
					{
						score++;
						isSecondGateEnabled = false;
						timerStart = std::chrono::high_resolution_clock::now();

					}
				}
				if (!isSecondGateEnabled)
				{
					first.setIsBallGrabbed(false);
					second.setIsBallGrabbed(false);
					ball.isBallFree = true;
					timeEnd = std::chrono::high_resolution_clock::now();
					std::chrono::duration<float> dur = timeEnd - timerStart;

					if (dur.count() > 0 && dur.count() < 3)
					{
						first.CanTakeBall = false;
						second.CanTakeBall = false;
						Font font;
						font.loadFromFile("CyrilicOld.TTF");
						Text text("Goal!", font, 70);
						if (crowdCheck == 1)
						{
							crowdSound.play();
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


						ball.setPosition(ball.getDefaultCoordinates().x, ball.getDefaultCoordinates().y);
						first.p.setPosition(first.p.getDefaultCoordinates().x, first.p.getDefaultCoordinates().y);
						second.p.setPosition(second.p.getDefaultCoordinates().x, second.p.getDefaultCoordinates().y);
						isSecondGateEnabled = true;
						first.CanTakeBall = true;
						second.CanTakeBall = true;
						crowdCheck = 1;
						switch (typeOfCam)
						{
						case defaultCamera:
							switch (whichPlayerIsUsingCam)
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
						case splitCamera:
							view.setCenter(first.p.getPlayerCoordinates().x, first.p.getPlayerCoordinates().y + 25);
							view2.setCenter(second.p.getPlayerCoordinates().x, second.p.getPlayerCoordinates().y + 25);
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
	int crowdCheck = 1;// check if need to use crowdSound
	SoundBuffer crowdBuffer;
	Sound crowdSound;
};
