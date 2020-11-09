/*
предварительная версия программы без обраотки столкновений шариков
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

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(600, 800), "Petank", Style::Close, settings);

	std::srand(time(NULL));
	float lowline = 300.f + (float)(std::rand() % 100), setAngle = 0.f, x = 180.f, y = 720.f, addPosX = 0, addPosY = 0, currtime = 0, velocity0 = 0, velocityX = 0;
	int angle = 0, stop = 1, setForce = 0, azimuth = 0, count1 = 0, count2 = 0, winner = 0;
	char str[4], str2[4], str7[3], str8[3];
	bool hit = 0, ballStop = 0, ballStop2 = 0, player = 0, step1 = 0, step2 = 0;

	CircleShape ball(20.f);
	ball.setFillColor(Color(24, 15, 61, 255));
	ball.setPosition(x, y);

	CircleShape ball2(20.f);
	ball2.setFillColor(Color(206, 93, 34, 255));
	ball2.setPosition(x, y);

	Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	Text txtAngle;
	txtAngle.setFont(font);
	txtAngle.setPosition(443.f, 753.f);
	txtAngle.setCharacterSize(14);
	txtAngle.setFillColor(Color(255, 255, 255, 255));

	Text txtForce;
	txtForce.setFont(font);
	txtForce.setCharacterSize(14);
	txtForce.setFillColor(Color(255, 255, 255, 255));

	Text win;
	win.setFont(font);
	win.setPosition(413.f, 320.f);
	win.setCharacterSize(18);
	win.setFillColor(Color(28, 28, 28, 255));
	win.setStyle(Text::Bold);

	Text countB;
	countB.setFont(font);
	countB.setPosition(485.f, 280.f);
	countB.setCharacterSize(24);
	countB.setFillColor(Color(24, 15, 61, 255));
	countB.setStyle(Text::Bold);

	Text countO;
	countO.setFont(font);
	countO.setPosition(515.f, 280.f);
	countO.setCharacterSize(24);
	countO.setFillColor(Color(206, 93, 34, 255));
	countO.setStyle(Text::Bold);

	RectangleShape checkplus1(Vector2f(2.f, 2.f));
	checkplus1.move(425.f, 707.f);
	checkplus1.setFillColor(Color(255, 255, 255, 255));

	RectangleShape checkplus2(Vector2f(2.f, 2.f));
	checkplus2.move(475.f, 707.f);
	checkplus2.setFillColor(Color(255, 255, 255, 255));

	RectangleShape checkplus3(Vector2f(3.f, 3.f));
	checkplus3.move(449.f, 700.f);
	checkplus3.setFillColor(Color(255, 255, 255, 255));

	RectangleShape status(Vector2f(190.f, 130.f));
	status.setFillColor(Color(65, 61, 230, 255));
	status.setPosition(410.f, 670.f);

	ConvexShape stage;
	

	RectangleShape mainArea(Vector2f(400.f, lowline));
	mainArea.setFillColor(Color(47, 137, 54, 224));

	RectangleShape border1(Vector2f(10.f, 790.f));
	border1.setFillColor(Color(222, 227, 53, 236));
	border1.setPosition(0.f, 10.f);

	RectangleShape border2(Vector2f(410.f, 10.f));
	border2.setFillColor(Color(222, 227, 53, 236));

	RectangleShape border3(Vector2f(10.f, 790.f));
	border3.setFillColor(Color(222, 227, 53, 236));
	border3.setPosition(400.f, 10.f);

	RectangleShape azimuthLine(Vector2f(50.f, 1.f));
	azimuthLine.move(450.f, 750.f);

	CircleShape koshonet(8.f, 30);
	koshonet.setFillColor(Color(255, 219, 88, 255));
	koshonet.setPosition(192.f, 170.f);

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

				else if (event.key.code == Keyboard::Left) azimuth += 1;

				else if (event.key.code == Keyboard::Right) azimuth -= 1;

				else if (event.key.code == Keyboard::Space)
				{
					hit = 1;
				}
			}
		}

		window.clear(Color(252, 218, 197, 255));

		// грницы изменения угла
		if (azimuth >= 30)
		{
			azimuth = 30;
		}
		if (azimuth <= -30)
		{
			azimuth = -30;
		}
		azimuthLine.setRotation(- 90 - azimuth);
		azimuthLine.setFillColor(Color(255, 255, 255, 255));

		// границы изменения скорости
		if (setForce >= 100)
		{
			setForce = 100;
		}
		if (setForce <= 0)
		{
			setForce = 0;
		}
		velocity0 = setForce / 10 + 0.1 * (float)(setForce % 10);

		// установка шкалы силы броска
		stage.setPointCount(4);
		stage.setPoint(0, Vector2f(500.f, 780.f));
		stage.setPoint(1, Vector2f(520.f, 780.f));
		stage.setPoint(2, Vector2f(520.f, 780.f - setForce));
		stage.setPoint(3, Vector2f(500.f, 780.f - setForce));
		stage.setFillColor(Color(255, 32, 32, 255));

		//просчет движения шариков
		if (player == 0)
		{
			if (hit == 1)
			{
				currtime += 0.016;
				if (velocityX >= 0)
				{
					
					velocityX = (velocity0 - (2.2 * currtime * currtime / 2));
					addPosX = velocityX * sin(azimuth * PI / 180);
					addPosY = velocityX * cos(azimuth * PI / 180);
					ball.move(-addPosX, -addPosY);
				}
				else
				{
					velocityX = 0;
					hit = 0;
					currtime = 0;
					setForce = 0;
					azimuth = 0;
					ballStop = 0;
					player = 1;
					step1 = 1;
				}
			} 
			if ((ball.getPosition().x >= 400.f) || (ball.getPosition().x < -40.f) || (ball.getPosition().y < -40.f))
			{
				velocityX = 0;
				hit = 0;
				currtime = 0;
				setForce = 0;
				azimuth = 0;
				ballStop = 1;
				player = 1;
				step1 = 1;
			}
		}

		if(player == 1)
		{
			if (hit == 1)
			{
				currtime += 0.016;
				if (velocityX >= 0)
				{

					velocityX = (velocity0 - (2.2 * currtime * currtime / 2));
					addPosX = velocityX * sin(azimuth * PI / 180);
					addPosY = velocityX * cos(azimuth * PI / 180);
					ball2.move(-addPosX, -addPosY);
				}
				else
				{
					velocityX = 0;
					hit = 0;
					currtime = 0;
					setForce = 0;
					azimuth = 0;
					ballStop2 = 0;
					player = 0;
					step2 = 1;
				}
			}
			if ((ball2.getPosition().x >= 400.f) || (ball2.getPosition().x < -40.f) || (ball2.getPosition().y < -40.f))
			{
				velocityX = 0;
				hit = 0;
				currtime = 0;
				setForce = 0;
				azimuth = 0;
				ballStop2 = 1;
				player = 0;
				step2 = 1;
			}
		}
		
		//подсчет очков и переход на следующий раунд
		if ((step1 == 1) && (step2 == 1))
		{
			if (sqrtf(pow(ball.getPosition().x + ball.getRadius() - koshonet.getPosition().x + koshonet.getRadius(), 2.f) + pow(ball.getPosition().y + ball.getRadius() - koshonet.getPosition().y + koshonet.getRadius(), 2.f)) < sqrtf(pow(ball2.getPosition().x + ball2.getRadius() - koshonet.getPosition().x + koshonet.getRadius(), 2.f) + pow(ball2.getPosition().y + ball2.getRadius() - koshonet.getPosition().y + koshonet.getRadius(), 2.f)))
			{
				if(ballStop == 0 && ball.getPosition().y < lowline)
				count1++;
			}
			else if (sqrtf(pow(ball.getPosition().x + ball2.getRadius() - koshonet.getPosition().x + koshonet.getRadius(), 2.f) + pow(ball.getPosition().y + ball2.getRadius() - koshonet.getPosition().y + koshonet.getRadius(), 2.f)) > sqrtf(pow(ball2.getPosition().x + +ball2.getRadius() - koshonet.getPosition().x + koshonet.getRadius(), 2.f) + pow(ball2.getPosition().y + +ball2.getRadius() - koshonet.getPosition().y + koshonet.getRadius(), 2.f)))
			{
				if(ballStop2 == 0 && ball2.getPosition().y < lowline)
				count2++;
			}
			else
			{
				if (ballStop == 0 && ballStop2 == 0 && ball.getPosition().y < lowline && ball2.getPosition().y < lowline)
				{
					count1++;
					count2++;
				}
			}

			_itoa_s(count1, str7, 10);
			countB.setString(str7);
			_itoa_s(count2, str8, 10);
			countO.setString(str8);
			step1 = 0;
			step2 = 0;
			ball.setPosition(x, y);
			ball2.setPosition(x, y);
			ballStop = 0;
			ballStop2 = 0;
		}

		if (count1 == 13)
		{
			win.setString("Blue Player win!");
			winner = 1;
		}
		else if(count2 == 13)
		{
			win.setString("Orange Player win!");
			winner = 1;
		}

		_itoa_s(azimuthLine.getRotation() - 270, str, 10);
		txtAngle.setString(str);
		_itoa_s(setForce, str2, 10);
		txtForce.setString(str2);
		txtForce.setPosition(530.f, 773.f - setForce);
		
		// отрисовка объектов
		window.draw(mainArea);
		window.draw(status);
		window.draw(border1);
		window.draw(border2);
		window.draw(koshonet);
		window.draw(border3);
		if (ballStop2 == 0)
		{
			window.draw(ball2);
		}
		if (ballStop == 0)
		{
			window.draw(ball);
		}
		window.draw(txtAngle);
		window.draw(txtForce);
		window.draw(stage);
		window.draw(azimuthLine);
		window.draw(checkplus1);
		window.draw(checkplus2);
		window.draw(checkplus3);
		window.draw(countB);
		window.draw(countO);
		if (winner == 1)
		{
			window.draw(win);	
			stop = 0;
		}


		// задержка обновления экрана
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		window.display();

		// обработка закрытия программы
		if (stop == 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			win.setString("Game is over.\nWait 5 seconds.");
			win.move(0.f, 30.f);
			window.draw(win);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			std::exit(0);
		}
	}
	return 0;
}
