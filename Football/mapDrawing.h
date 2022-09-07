#pragma once
class Map
{
public:
	Map(String file)
	{
		this->file = file;
		mapImage.loadFromFile("map/" + file);

		textureOfMap.loadFromImage(mapImage);
		sprMap.setTexture(textureOfMap);
	}
	Sprite& getSpr()
	{
		return sprMap;
	}

	void drawTheMap(RenderWindow& wind)
	{
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  sprMap.setTextureRect(IntRect(162, 0, 32, 32));
				if (TileMap[i][j] == 's') sprMap.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0')sprMap.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'i')sprMap.setTextureRect(IntRect(195, 0, 32, 32));
				if (TileMap[i][j] == 'j')sprMap.setTextureRect(IntRect(228, 0, -32, 32));
				if (TileMap[i][j] == 'b')sprMap.setTextureRect(IntRect(259, 0, 32, 32));
				if (TileMap[i][j] == 'k')sprMap.setTextureRect(IntRect(291, 0, -32, 32));
				if (TileMap[i][j] == '|')sprMap.setTextureRect(IntRect(228, 0, 32, 32));
				if (TileMap[i][j] == 'l')sprMap.setTextureRect(IntRect(260, 0, -32, 32));
				if (TileMap[i][j] == 'w')sprMap.setTextureRect(IntRect(291, 0, 32, 32));
				if (TileMap[i][j] == '1')sprMap.setTextureRect(IntRect(328, 0, 32, 32));
				if (TileMap[i][j] == '=')sprMap.setTextureRect(IntRect(362, 0, 32, 32));
				if (TileMap[i][j] == 'P')sprMap.setTextureRect(IntRect(395, 0, 32, 32));
				if (TileMap[i][j] == 'B')sprMap.setTextureRect(IntRect(427, 0, -32, 32));
				if (TileMap[i][j] == 'L')sprMap.setTextureRect(IntRect(395, 34, 32, -32));
				if (TileMap[i][j] == 'N')sprMap.setTextureRect(IntRect(427, 34, -32, -32));
				if (TileMap[i][j] == '2')sprMap.setTextureRect(IntRect(464, 0, 32, 32));
				if (TileMap[i][j] == '3')sprMap.setTextureRect(IntRect(126, -1, 32, 32));
				if (TileMap[i][j] == '4')sprMap.setTextureRect(IntRect(158, -1, -32, 32));
				sprMap.setPosition(j * 32, i * 32);
				wind.draw(sprMap);
			}
		}
	}
private:
	Image mapImage;
	Texture textureOfMap;
	Sprite sprMap;
	String file;

};