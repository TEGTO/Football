#pragma once
class Bullet
{
	Coordinates bulletCurrentCoordinates;

	float bulletWight, bulletHeight, bulletDx, BulletDy, BulletSpeed = 0.8;
	bool isAlive = false;
	int diraction = 0;
	Image bulletImg;
	Texture bulletTexture;

public:
	Sprite spr;
	Bullet(Image img, int x, int y, int w, int h, Player& firstPlayer)
	{
		this->bulletHeight = h, this->bulletWight = w;
		bulletTexture.loadFromImage(img);
		spr.setTexture(bulletTexture);
		spr.setTextureRect(IntRect(x, y, this->bulletWight, this->bulletHeight));
		bulletCurrentCoordinates.x = 0;
		bulletCurrentCoordinates.y = -100;
		spr.setPosition(bulletCurrentCoordinates.x, bulletCurrentCoordinates.y);

	}
	void update(float time, Player& firstPlayer, Player& secondPlayer)
	{
		if (firstPlayer.isShoot)
		{
			isAlive = true;
			firstPlayer.isShoot = false;
			this->diraction = firstPlayer.p.dir;
			bulletCurrentCoordinates.x = firstPlayer.p.getPlayerCoordinates().x + 40;
			bulletCurrentCoordinates.y = firstPlayer.p.getPlayerCoordinates().y + 50;

		}

		if (isAlive)
		{


			switch (this->diraction)
			{
			case right:
				bulletDx = BulletSpeed, BulletDy = 0; break;
			case left:
				bulletDx = -BulletSpeed, BulletDy = 0; break;
			case up:
				bulletDx = 0, BulletDy = -BulletSpeed; break;
			case down:
				bulletDx = 0, BulletDy = BulletSpeed; break;
			default:
				bulletDx = BulletSpeed, BulletDy = 0; break;

			}

			bulletCurrentCoordinates.x += bulletDx * time;
			bulletCurrentCoordinates.y += BulletDy * time;


			bulletPhysics(time, firstPlayer, secondPlayer);
			if (isAlive)
			{
				spr.setPosition(bulletCurrentCoordinates.x, bulletCurrentCoordinates.y);

			}
			else
			{
				spr.setPosition(600, 800);
				firstPlayer.isntShootingCheck = true;
			}



		}






	}
	void bulletPhysics(float time, Player& firstPlayer, Player& secondPlayer)
	{

		for (int i = bulletCurrentCoordinates.y / 32; i < (bulletCurrentCoordinates.y + bulletHeight) / 32; i++)
		{
			for (int j = bulletCurrentCoordinates.x / 32; j < (bulletCurrentCoordinates.x + bulletWight) / 32; j++)
			{
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'w')
				{
					isAlive = false;

				}
			}
		}
		if (abs((bulletCurrentCoordinates.x - 30) - (secondPlayer.p.getPlayerCoordinates().x)) < 35 && abs(((bulletCurrentCoordinates.y - 35) - (secondPlayer.p.getPlayerCoordinates().y))) < 25)
		{
			isAlive = false;
			secondPlayer.p.health -= 10;
		}

	}
};