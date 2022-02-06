#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <algorithm>


#define WIDTH 500
#define HEIGHT 500

class Entity : public sf::RectangleShape{
public:
	Entity(sf::Vector2f size, float pushForce, sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Color outlineColor = sf::Color::Cyan, sf::Color fillColor = sf::Color(255, 255, 255))
	{
		this->setSize( size );
		this->setOutlineColor( outlineColor );
		this->setPosition( pos );
		this->setFillColor( fillColor );
		this->pushForce = pushForce;

	printf( "Created entity\n" );
	};

	~Entity()
	{
		printf("Deleting entity\n");
	};

	void Update(sf::Vector2f origin, sf::Vector2f pos)
	{
		this->setOrigin(origin);
		this->setPosition(pos);
	};

	void isTouching( sf::Vector2f mousePos )
	{
		sf::Vector2f entPos = static_cast< sf::Vector2f >( this->getPosition() );
		sf::Vector2f entOrigin = this->getOrigin( );

		if (mousePos.x < (entPos.x + this->getSize( ).x - entOrigin.x) &&
			mousePos.x >(entPos.x - entOrigin.x) &&
			mousePos.y < (entPos.y + this->getSize().y - entOrigin.y) &&
			mousePos.y >(entPos.y - entOrigin.y)) {

			this->onSquare = true;
		}
	};

	void Limit( float width, float height )
	{
		if (this->getPosition().x < 0)
			this->setPosition(0.f, this->getPosition().y);
		if (this->getPosition().y < 0)
			this->setPosition(this->getPosition().x, 0.f);
		if (this->getPosition().x > width - this->getSize().x)
			this->setPosition(width - this->getSize().x, this->getPosition().y);
		if (this->getPosition().y > height - this->getSize().y)
			this->setPosition(this->getPosition().x, height - this->getSize().y);
	};

	sf::Vector2f desiredOrigin;
	bool onSquare = false;
	bool selected = false;
	float pushForce{ };

};

sf::Vector2f delta;

bool CheckCollision(sf::RectangleShape& ent1, sf::RectangleShape& ent2) {
	delta.x = abs( ( ent1.getPosition( ).x - ent1.getOrigin( ).x + ( ent1.getSize( ).x / 2 ) ) - ( ent2.getPosition( ).x - ent2.getOrigin( ).x + ( ent2.getSize( ).x / 2 ) ) ) - ( ent1.getSize( ).x + ent2.getSize( ).x ) / 2;
	delta.y = abs( ( ent1.getPosition( ).y - ent1.getOrigin( ).y + ( ent1.getSize( ).y / 2 ) ) - ( ent2.getPosition( ).y - ent2.getOrigin( ).y + ( ent2.getSize( ).y / 2 ) ) ) - ( ent1.getSize( ).y + ent2.getSize( ).y ) / 2;

	if ( delta.x <= 0.f && delta.y <= 0.f )
		return true;
	else
		return false;
}


int main() {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "render test", sf::Style::Close);

	window.setVerticalSyncEnabled(true);

	sf::Color color{ 255, 0, 0 };

	Entity ent(sf::Vector2f(100.f, 100.f), 1.f, sf::Vector2f(145.f, 200.f));
	Entity ent2(sf::Vector2f(100.f, 100.f), 1.f, sf::Vector2f(255.f, 200.f));

	sf::RectangleShape rect(sf::Vector2f(50.f,50.f));
	rect.setPosition(sf::Vector2f(0.f, 0.f));
	rect.setFillColor(sf::Color(255, 255, 255, 10));
	rect.setOutlineThickness(1.25f);

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f entPos = ent.getPosition();
	sf::Vector2f entSize = ent.getSize();
	sf::Vector2f clickPos;
	sf::Vector2f relativeDistance;

	bool mouseDown = false;

	while (window.isOpen()) {

		mousePos = sf::Mouse::getPosition(window);
		entPos = ent.getPosition();
		entSize = ent.getSize();

		sf::Event event;
		//------Event Handler------//
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::GainedFocus:
					printf("Gained Focus\n");
					break;
				case sf::Event::LostFocus:
					printf("Lost Focus\n");
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) {

						ent.isTouching( static_cast< sf::Vector2f >( mousePos ));
						ent2.isTouching( static_cast< sf::Vector2f >( mousePos ));

						mouseDown = true;
						clickPos = static_cast<sf::Vector2f>(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));

						ent.desiredOrigin = static_cast<sf::Vector2f>( sf::Mouse::getPosition( window ) ) - ent.getPosition();
						ent2.desiredOrigin = static_cast<sf::Vector2f>( sf::Mouse::getPosition( window ) ) - ent2.getPosition();

						if ( ent.onSquare )
							relativeDistance = ent2.getPosition( ) - static_cast< sf::Vector2f >( sf::Mouse::getPosition( window ) );
						if ( ent2.onSquare )
							relativeDistance = ent.getPosition( ) - static_cast< sf::Vector2f >( sf::Mouse::getPosition( window ) );

					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left) {
						mouseDown = false;

						ent.onSquare = false;
						ent2.onSquare = false;

						ent.move( -ent.getOrigin().x , -ent.getOrigin().y );
						ent2.move( -ent2.getOrigin().x , -ent2.getOrigin().y );

						ent.setOrigin(0.f, 0.f);
						ent2.setOrigin(0.f, 0.f);
					}
					break;
			}

		}
		//------End of Event Handler--------

		if (CheckCollision(ent, ent2))
		{
			if (delta.x > delta.y) {

				if (ent2.getPosition().x - ent.getPosition().x > 0.f) {
					ent.move(delta.x * ent.pushForce, 0.f);
					ent2.move(-delta.x * ent.pushForce, 0.f);
				}
				else
				{
					ent.move(-delta.x * ent.pushForce, 0.f);
					ent2.move(delta.x * ent.pushForce, 0.f);
				}

			}
			else
			{

				if (ent2.getPosition().y - ent.getPosition().y > 0.f) {
					ent.move(0.f, delta.y * ent.pushForce);
					ent2.move(0.f, -delta.y * ent.pushForce);
				}
				else
				{
					ent.move(0.f, -delta.y * ent.pushForce);
					ent2.move(0.f, delta.y * ent.pushForce);
				}

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		ent.Limit(WIDTH, HEIGHT);
		ent2.Limit(WIDTH, HEIGHT);
	
		if ( ent.onSquare ) {
			ent.Update( ent.desiredOrigin , static_cast< sf::Vector2f >( sf::Mouse::getPosition( window ) ) );

			if ( ent.selected && ent2.selected ) 
				ent2.setPosition( static_cast< sf::Vector2f >( sf::Mouse::getPosition( window ) ) + relativeDistance );
		}

	
		if ( ent2.onSquare ) {
			ent2.Update( ent2.desiredOrigin , static_cast< sf::Vector2f >( sf::Mouse::getPosition( window ) ) );

			if ( ent.selected && ent2.selected )
				ent.setPosition( static_cast< sf::Vector2f >( sf::Mouse::getPosition( window ) ) + relativeDistance );
		}


		if ( color.r > 0 && color.b == 0 ) {
			color.r--;
			color.g++;
		}else
		if ( color.g > 0 && color.r == 0 ) {
			color.g--;
			color.b++;
		}else
		if ( color.b > 0 && color.g == 0 ) {
			color.r++;
			color.b--;
		}

		ent.setFillColor(sf::Color(color.b, color.g, color.r));
		ent2.setFillColor(color);
		rect.setOutlineColor(color);

		float thickness = ( ent.selected ) ? 2.f : 0.f;
		ent.setOutlineThickness( thickness );
		thickness = ( ent2.selected ) ? 2.f : 0.f;
		ent2.setOutlineThickness( thickness );

		window.clear();
		window.draw( ent );
		window.draw( ent2 );

		if ( mouseDown && !ent.onSquare && !ent2.onSquare) {

			float deltaX = std::abs((float)sf::Mouse::getPosition(window).x - clickPos.x);
			float deltaY = std::abs((float)sf::Mouse::getPosition(window).y - clickPos.y);
			
			static sf::Vector2f origin;

			if (clickPos.x > sf::Mouse::getPosition(window).x) 
			{
				if (clickPos.y > sf::Mouse::getPosition(window).y) 
				{ origin = sf::Vector2f(deltaX, deltaY); }
				else 
				{ origin = sf::Vector2f(deltaX, 0); }
			}
			else 
			{
				if (clickPos.y > sf::Mouse::getPosition(window).y) 
				{ origin = sf::Vector2f(0, deltaY); }
				else 
				{ origin = sf::Vector2f(0, 0); }

			}

			rect.setOrigin( origin );
			rect.setSize( sf::Vector2f(deltaX, deltaY) );
			rect.setPosition( clickPos );
			window.draw( rect );

			//do something about rec origin
			ent.selected  = CheckCollision( ent , rect );
			ent2.selected = CheckCollision( ent2 , rect );
		}
		window.display();

	}

	return 0;
}
