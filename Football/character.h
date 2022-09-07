
#include "enums.h"
int whichPlayerIsUsingCam;
class Character
{
protected:
	Coordinates main;
	Coordinates defaultPosition;
public:
	float w, h, dx, dy, speed = 0;
	int dir = 0, health = 20;
	bool isalive;
	String File;
	Image img;
	Texture texture;
	Sprite spr;
	void setPosition(float x, float y)
	{
		main.x = x;
		main.y = y;
	}
	void setDefaultCoordinates(float x, float y)
	{
		defaultPosition.x = x;
		defaultPosition.y = y;
	}
	Coordinates getDefaultCoordinates()
	{
		return defaultPosition;
	}
	void setPar(String FIle, int x, int y, float h, float w)
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
			for (int j = main.x / 32; j < (main.x + w) / 32; j++)
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


};

