#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <iostream>

using namespace std;

int main()
{
	int order = 0;
	int pointcount = 0;
	int row = 0;
	int column = 0;
	int click = 0;
	bool done = false;
	bool select = false;
	float mowerWidth = 25;
	float mowerLength = 25;

	float point1x = 0, point1y = 0, point2x = 0, point2y = 0, point3x = 0, point3y = 0;
	float slope1 = 0;
	float slope2 = 0;
	float slope3 = 0;
	float y1 = 0;
	float y2 = 0;
	float y3 = 0;
	float angle = 0;
	
	
	float speed = .25;
		float pointarray[99][99] = {
			{ 0, 0 },
			{ 0, 0 },
			
		};
	
	sf::RenderWindow window(sf::VideoMode(1750, 1000), "Lawn Mower Simulator");
	sf::Texture mowertexture;
	sf::Texture background;
	if (!mowertexture.loadFromFile("C:\\Programming\\Visual Studios Code\\Lawn Mower Simulation\\mower.png"))
	{
		//error
	}
	if (!background.loadFromFile("C:\\Programming\\Visual Studios Code\\Lawn Mower Simulation\\lawn.png"))
	{
		//error
	}
	
	//sf::Sprite mower;
	//mower.setTexture(mowertexture);

	sf::Sprite lawn;
	lawn.setTexture(background);
	sf::RectangleShape mower(sf::Vector2f(25, 25));
	mower.setFillColor(sf::Color::Red);
	
	
	sf::VertexArray Line1(sf::PrimitiveType::Lines, 2);
	sf::VertexArray Line2(sf::PrimitiveType::Lines, 2);
	sf::VertexArray Line3(sf::PrimitiveType::Lines, 2);
	
	sf::VertexArray lines(sf::PrimitiveType::LinesStrip, 5);
	
	while (select == false)
	{
		window.clear(sf::Color::Green);

		window.draw(lawn);

	
		
		
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		
		cout << "X: " << mousePosition.x << " Y: " << mousePosition.y << "   " << "Point Count: " << pointcount << "   Point 1: " << point1x << "," << point1y << 
			 "  slope:" << slope1 << " " << pointarray[0][0] << "," << pointarray[0][1] << '\n';
		cout << "point 2: " << point2x << "," << point2y << '\n';

		slope1 = (point2y - point1y) / (point2x - point1x);
		slope2 = (point3y - point2y) / (point3x - point2x);
		slope3 = (point3y - point1y) / (point3x - point1x);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			pointarray[row][column] = mousePosition.x;
			pointarray[row][column + 1] = mousePosition.y;

			row = row + 1;
			click = click + 1;
			lines[click].position = sf::Vector2f(pointarray[row][column], pointarray[row][column + 1]);
			window.draw(lines);

		}

		while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

		}
		
 
		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			
			select = true;
		}
		
		
		
			

		if (pointarray[0][0] != 0 && pointarray[0][1] != 0 && pointarray[1][0] != 0 && pointarray[1][1] != 0)
		{
			Line1[0].position = sf::Vector2f(pointarray[0][0], pointarray[0][1]);
			Line1[1].position = sf::Vector2f(pointarray[1][0], pointarray[1][1]);


			Line1[0].color = sf::Color::Black;
			Line1[1].color = sf::Color::Black;

			window.draw(Line1);
		}

		if (pointarray[1][0] != 0 && pointarray[1][1] != 0 && pointarray[2][0] != 0 && pointarray[2][1] != 0)
		{
			Line2[0].position = sf::Vector2f(pointarray[1][0], pointarray[1][1]);
			Line2[1].position = sf::Vector2f(pointarray[2][0], pointarray[2][1]);


			Line2[0].color = sf::Color::Black;
			Line2[1].color = sf::Color::Black;

			window.draw(Line2);
		}

		if (pointarray[2][0] != 0 && pointarray[2][1] != 0 && pointarray[0][0] != 0 && pointarray[0][1] != 0)
		{
			Line3[0].position = sf::Vector2f(pointarray[2][0], pointarray[2][1]);
			Line3[1].position = sf::Vector2f(pointarray[0][0], pointarray[0][1]);


			Line3[0].color = sf::Color::Black;
			Line3[1].color = sf::Color::Black;

			window.draw(Line3);
		}
		 
	

		//pointarray[row][column], pointarray[row][column + 1]
		
			window.display();
	}
	
	
	
	
	
	
	//mower.setOrigin(mowerWidth, mowerLength);
	mower.setPosition(point1x, point1y);
	
	

	float mowerXPos = point1x;

	while (window.isOpen())
	{

		slope1 = (point2y - point1y) / (point2x - point1x);
		y1 = slope1*(mowerXPos - point1x) + point1y;
		y2 = slope2*(mowerXPos - point2x) + point2y;
		y3 = slope3*(mowerXPos - point3x) + point3y;
		
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Green);
	
		window.draw(Line1);
		window.draw(Line2);
		window.draw(Line3);
		window.draw(mower);
		window.draw(lawn);
		window.display();

		if (order == 0 && mowerXPos >= point1x && mowerXPos <= point2x) //if in Line1
		{
			if (order == 0 && mower.getPosition().y + mowerLength > y1) //move up
			{
				mower.move(1, slope1);
			}
			if (mower.getPosition().y + mowerLength <= y1)
			{
				order = 1;
			}
		}
		if (order == 0 && mowerXPos >= point2x && mowerXPos <= point3x) //if in Line2
		{
			if (order == 0 && mower.getPosition().y + mowerLength > y2) //move up
			{
				mower.move(0, -speed);
			}
			if (mower.getPosition().y + mowerLength <= y2)
			{
				order = 1;
			}
		}
		
		
		if (order == 1 && mower.getPosition().x < mowerXPos + mowerWidth ) //turn
		{
			mower.move(speed, 0);
			//mower.rotate(speed);
			//angle = angle + 1;     angle <= 180
		}
		if (order == 1 && mower.getPosition().x == mowerXPos + mowerWidth)
		{
			order = 2;
			mowerXPos = mowerXPos + mowerWidth;
			//mower.setOrigin(0, mowerLength);      angle == 180
		}

			
		
		if (order == 2 && mowerXPos >= point1x && mowerXPos <= point3x) //if in Line3
		{
			if (order == 2 && mower.getPosition().y + mowerLength < y3) //move down
			{
				mower.move(0, speed);
			}
			if (mower.getPosition().y + mowerLength >= y3)
			{
				order = 3;
			}
		}
		
		if (order == 3 && mower.getPosition().x < mowerXPos + mowerWidth) //turn
		{
			mower.move(speed, 0);
			//mower.rotate(-speed);
			//angle = angle - 1;     angle >= 0
		}
		if (order == 3 && mower.getPosition().x == mowerXPos + mowerWidth)
		{
			order = 0;
			mowerXPos = mowerXPos + mowerWidth;
			//mower.setOrigin(mowerWidth, mowerLength);    angle == 0
		}
		
		cout << mowerXPos << "Order: " << order << '\n';
		
		
		
	}
	
	cout << "Order: " << order << '\n';
	cout << "slope" << slope1 << '\n';
	cout << "Equation of Line1: " << "y - " << point1y << " = " << slope1 << "( x - " << point1x << ")" << '\n';
	cout << "y = " << y1 << '\n';
	cout << "pointarray: " << '\n' << pointarray[0][0] << "," << pointarray[0][1] << '\n' << pointarray[1][0] << "," << pointarray[1][1] << '\n';
	cout << "Press Enter to Exit";
	while (done==false)
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			done = true;
		}
	}
}