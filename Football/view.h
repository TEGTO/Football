#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
View view;
View getPlayerCoordinatesForView(float x, float y)
{
	float tempX = x, tempY = y;
	if (x < 400)tempX = 400;
	if (x > 880) tempX = 880;
	if (y < 300)tempY = 300;
	if (y > 495)tempY = 495;
	view.setCenter(tempX, tempY);
	return view;
}

View viewmap(float time)
{

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		view.move(0.1 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		view.move(0, 0.1 * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		view.move(-0.1 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		view.move(0, -0.1 * time);
	}

	return view;
}
View changeView()
{
	if (Keyboard::isKeyPressed(Keyboard::PageUp))
	{
		view.zoom(1.0100f);
	}
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		view.rotate(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		view.setSize(800, 600);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		view.setViewport(FloatRect(0, 0, 0.5f, 1));
	}
	return view;
}