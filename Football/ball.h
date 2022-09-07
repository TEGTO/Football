
class Ball
{
private:

	float currentFrameX = 0;
	float spedAnim = 0.02;
	Coordinates defaultPosition;
	Coordinates main;
	void animations(float time)
	{
		currentFrameX += spedAnim * time;
		if (currentFrameX > 3)
		{
			currentFrameX = 0;
		}
		spr.setTextureRect(IntRect(32 * int(currentFrameX), 0, 32, 32));
	}
public:
	void setSpeedAnim(float speed)
	{
		this->spedAnim = speed;
	}
	bool isBallFree = true;
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
		defaultPosition.x = x;
		defaultPosition.y = y;
	}
	Coordinates getDefaultCoordinates()
	{
		return defaultPosition;
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
	void setPosition(float x, float y)
	{
		main.x = x;
		main.y = y;
	}
	void update(float time, float playerX, float playerY, float playerDx, float playerDy, float speed, bool isBallGrabbed)
	{

		if (isBallFree)
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

			ballPhysics(time, playerX, playerY, playerDx, playerDy, speed);

		}
		else
		{
			if (isBallGrabbed)
			{
				if (playerDy > 0)
				{
					dir = down;
					main.y = playerY + 85;
					main.x = playerX + 32;
					animations(time);
				}
				if (playerDy < 0)
				{
					dir = up;

					main.y = playerY - 15;
					main.x = playerX + 32;
					animations(time);

				}
				if (playerDx > 0)
				{
					dir = left;
					main.y = playerY + 60;
					main.x = playerX + 70;
					animations(time);
				}
				if (playerDx < 0)
				{
					dir = left;
					main.y = playerY + 60;
					main.x = playerX - 10;
					animations(time);
				}

				spr.setPosition(main.x, main.y);
			}



		}
	}
	void ballPhysics(float time, float playerX, float playerY, float playerDx, float playerDy, float speed)
	{

		for (int i = main.y / 32; i < (main.y + h) / 32; i++)
		{
			for (int j = main.x / 32; j < (main.x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'w')
				{
					if (dy > 0)
					{
						main.y = i * 32 - h * 3;

					}
					if (dy < 0)
					{
						main.y = i * 32 + 32 * 3;

					}
					if (dx > 0)
					{
						main.x = j * 32 - w * 3;

					}
					if (dx < 0)
					{
						main.x = j * 32 + 32 * 3;

					}
				}
			}
		}
		if (abs((main.x - 30) - (playerX)) < 35 && abs(((main.y - 35) - (playerY))) < 45)
		{


			if (playerDy > 0)
			{

				dir = down;
				main.y += dy * speed * time;
				animations(time);
			}
			if (playerDy < 0)
			{
				dir = up;
				main.y += dy * speed * time;

				animations(time);

			}
			if (playerDx > 0)
			{
				dir = right;
				main.x += speed * time;

				animations(time);
			}
			if (playerDx < 0)
			{
				dir = left;

				main.x += dx * speed * time;
				animations(time);
			}

			this->speed = speed;
		}
	}
};