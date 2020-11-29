/*
предварительная версия программы без обработки столкновений шариков
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <cmath> 

#define PI 3.14159265

using namespace sf;
Font font;

class Ball
{
	float sX = 180.f, sY = 720.f;

public:
	CircleShape ball;
	bool flag, step;

	Ball(float rad)
	{
		ball.setRadius(rad);
		ball.setRotation(-90);
	}

	void Move(float currtime, float azimuth, int v0)
	{

		ball.move(-((v0 - (2.2 * currtime * currtime / 2)) * sin((azimuth)* PI / 180)), -((v0 - (2.2 * currtime * currtime / 2)) * cos((azimuth)* PI / 180)));
	}

	void SetColor(int r, int g, int b, int a)
	{
		ball.setFillColor(Color(r, g, b, a));
	}

	void SetStartPosition()
	{
		ball.setPosition(sX, sY);
	}

	void SetKoshPosition()
	{
		ball.setPosition(192.f, 170.f);
	}

	bool CheckOut()
	{
		if ((ball.getPosition().x >= 400.f) || (ball.getPosition().x < -40.f) || (ball.getPosition().x < -40.f))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CheckLowline(float& lowline)
	{
		if (ball.getPosition().x < lowline) return true;
		else return false;
	}

	float CurrVelocity(int v0, float currtime)
	{
		return v0 - (2.2 * currtime * currtime / 2);
	}

	float distance(Ball & otherBall)
	{
		return sqrt(pow((ball.getPosition().x) - (otherBall.ball.getPosition().x), 2) + pow((ball.getPosition().y) - (otherBall.ball.getPosition().y), 2));
	}
};

class Azimuth
{
public:
	int azimuth = 0;
	RectangleShape AzLine;

	Azimuth()
	{
		AzLine.setSize(Vector2f(50.f, 1.f));
		AzLine.setPosition(450.f, 750.f);
		AzLine.setFillColor(Color(255, 255, 255, 255));
	}

	int SetAzimuth(int azimuth)
	{
		this->azimuth = -azimuth - 90;
		AzLine.setRotation(-azimuth - 90);
		return azimuth;
	}

	int GetAzimuth()
	{
		return this->azimuth;
	}
};

class StaticFigures
{
public:
	RectangleShape SFigure;

	StaticFigures(float X, float Y, int r, int g, int b, int a, float sX, float sY)
	{
		SFigure.setSize(Vector2f(X, Y));
		SFigure.setFillColor(Color(r, g, b, a));
		SFigure.setPosition(sX, sY);
	}
};

class ForceStage
{
public:
	ConvexShape stage;

	ForceStage()
	{
		stage.setPointCount(4);
		stage.setPoint(0, Vector2f(500.f, 780.f));
		stage.setPoint(1, Vector2f(520.f, 780.f));
		stage.setPoint(2, Vector2f(520.f, 780.f));
		stage.setPoint(3, Vector2f(500.f, 780.f));
		stage.setFillColor(Color(255, 32, 32, 255));
	}

	void SetStage(int setForce)
	{
		stage.setPoint(2, Vector2f(520.f, 780 - setForce));
		stage.setPoint(3, Vector2f(500.f, 780 - setForce));
	}
};

class MyText
{
public:

	Text text;

	MyText(int size, int r, int g, int b, int a, float sX, float sY)
	{

		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(Color(r, g, b, a));
		text.setPosition(sX, sY);
	}

	MyText(int size, int r, int g, int b, int a)
	{

		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(Color(r, g, b, a));
	}
};

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(600, 800), "Petank Game", Style::Close, settings);

	float lowline, currtime = 0, velocity0 = 0;
	int setForce = 0, angle = 0, count1 = 0, count2 = 0;
	char str[10], str2[10], str3[10], str4[10];
	bool hit = false, stop = false, winner = false;

	std::srand(time(NULL));
	lowline = 280.f + (float)(std::rand() % 120);

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	Ball BallB(20.f);
	BallB.SetColor(163, 4, 251, 255);
	BallB.SetStartPosition();

	Ball BallO(20.f);
	BallO.SetColor(253, 162, 2, 255);
	BallO.SetStartPosition();

	MyText txtAngle(14, 255, 255, 255, 255, 443.f, 753.f);
	MyText txtForce(14, 255, 255, 255, 255);
	MyText txtWin(18, 28, 28, 28, 255, 413.f, 320.f);
	txtWin.text.setStyle(Text::Bold);

	MyText txtCountB(24, 24, 15, 61, 255, 485.f, 280.f);
	txtCountB.text.setStyle(Text::Bold);
	MyText txtCountO(24, 206, 93, 34, 255, 515.f, 280.f);
	txtCountO.text.setStyle(Text::Bold);

	StaticFigures checkplus1(2.f, 2.f, 255, 255, 255, 255, 425.f, 707.f);
	StaticFigures checkplus2(2.f, 2.f, 255, 255, 255, 255, 475.f, 707.f);
	StaticFigures checkplus3(1.f, 3.f, 255, 255, 255, 255, 450.f, 695.f);

	StaticFigures status(190.f, 130.f, 65, 61, 230, 255, 410.f, 670.f);

	StaticFigures border1(10.f, 790.f, 222, 227, 53, 255, 0.f, 10.f);
	StaticFigures border2(410.f, 10.f, 222, 227, 53, 255, 0.f, 0.f);
	StaticFigures border3(10.f, 790.f, 222, 227, 53, 255, 400.f, 10.f);

	ForceStage stage;

	RectangleShape mainArea(Vector2f(400.f, lowline));
	mainArea.setFillColor(Color(47, 137, 54, 224));

	Azimuth Line;

	Ball koshonet(8.f);
	koshonet.SetColor(255, 219, 88, 255);
	koshonet.SetKoshPosition();

	BallB.flag = true;
	BallO.flag = false;
	BallB.step = false;
	BallO.step = false;

	while (window.isOpen())
	{
		Event event; // очередь обработки событий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::Up) setForce += 1;

				else if (event.key.code == Keyboard::Down) setForce -= 1;

				else if (event.key.code == Keyboard::Left) angle += 1;

				else if (event.key.code == Keyboard::Right) angle -= 1;

				else if (event.key.code == Keyboard::Space)
				{
					hit = 1;
				}
			}
		}

		window.clear(Color(3, 252, 163, 255));

		// грницы изменения угла
		if (angle >= 30) angle = 30;
		else if (angle <= -30) angle = -30;

		Line.SetAzimuth(angle);

		// границы изменения скорости
		if (setForce >= 100) setForce = 100;
		else if (setForce <= 0) setForce = 0;
		velocity0 = (float)setForce / 10 + 0.1 * (float)(setForce % 10);

		// установка шкалы силы броска
		stage.SetStage(setForce);
		//обработка движения
		if (BallB.flag)
		{
			if (hit)
			{
				currtime += 0.016;
				BallB.Move(currtime, angle, velocity0);
				if (BallB.CurrVelocity(velocity0, currtime) <= 0)
				{
					hit = 0;
					currtime = 0;
					setForce = 0;
					angle = 0;
					Line.AzLine.setRotation(angle);
					BallB.step = true;
					BallB.flag = false;
					BallO.flag = true;
				}
			}
		}

		if (BallO.flag)
		{
			if (hit)
			{
				currtime += 0.016;
				BallO.Move(currtime, angle, velocity0);
				if (BallO.CurrVelocity(velocity0, currtime) <= 0)
				{
					hit = 0;
					currtime = 0;
					setForce = 0;
					angle = 0;
					Line.AzLine.setRotation(angle);
					BallO.step = true;
					BallO.flag = false;
					BallB.flag = true;
				}
			}
		}
		// подсчет очков и переход на следующий раунд
		if (BallB.step && BallO.step)
		{
			if (BallB.distance(koshonet) < BallO.distance(koshonet))
			{
				if (!BallB.CheckOut() && BallB.CheckLowline(lowline)) count1++;
			}
			else if (BallB.distance(koshonet) > BallO.distance(koshonet))
			{
				if (!BallO.CheckOut() && BallO.CheckLowline(lowline)) count2++;
			}
			else
			{
				if (!BallB.CheckOut() && !BallO.CheckOut())
				{
					count1++;
					count2++;
				}
			}

			_itoa_s(count1, str3, 10);
			txtCountB.text.setString(str3);
			_itoa_s(count2, str4, 10);
			txtCountO.text.setString(str4);
			BallB.step = false;
			BallO.step = false;
			BallB.SetStartPosition();
			BallO.SetStartPosition();
		}

		if (count1 == 13)
		{
			txtWin.text.setString("First Player win!");
			winner = true;
		}
		else if (count2 == 13)
		{
			txtWin.text.setString("Second Player win!");
			winner = true;
		}

		_itoa_s(Line.AzLine.getRotation() - 270, str, 10);
		txtAngle.text.setString(str);
		_itoa_s(setForce, str2, 10);
		txtForce.text.setString(str2);
		txtForce.text.setPosition(530.f, 773.f - setForce);

		// отрисовка объектов
		window.draw(mainArea);
		window.draw(status.SFigure);
		window.draw(border1.SFigure);
		window.draw(border2.SFigure);
		window.draw(border3.SFigure);
		window.draw(koshonet.ball);
		if (!BallO.CheckOut())
		{
			window.draw(BallO.ball);
		}
		if (!BallB.CheckOut())
		{
			window.draw(BallB.ball);
		}
		window.draw(txtAngle.text);
		window.draw(txtForce.text);
		window.draw(stage.stage);
		window.draw(Line.AzLine);
		window.draw(checkplus1.SFigure);
		window.draw(checkplus2.SFigure);
		window.draw(checkplus3.SFigure);
		window.draw(txtCountB.text);
		window.draw(txtCountO.text);
		if (winner)
		{
			window.draw(txtWin.text);
			stop = true;
		}

		// задержка обновления экрана
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		window.display();

		// обработка закрытия программы
		if (stop)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			txtWin.text.setString("Game is over.\nWait 5 seconds.");
			txtWin.text.move(0.f, 30.f);
			window.draw(txtWin.text);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			std::exit(0);
		}
	}
	return 0;
}
