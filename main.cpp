#include "Network.h"
#include "Globals.h"

int main()
{

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	Network network({2,3,1});

	sf::Font font;
	if (!font.loadFromFile("OCRAEXT.TTF"))
		printf("Failed to load font\n");

	sf::Text text("", font, 20);

	while (window.isOpen())
	{

		//------Event Handler------//
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::TextEntered:
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::KeyReleased:
				break;
			case sf::Event::MouseWheelMoved:
				break;
			case sf::Event::MouseWheelScrolled:
				break;
			case sf::Event::MouseButtonPressed:
				break;
			case sf::Event::MouseButtonReleased:
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseEntered:
				break;
			case sf::Event::MouseLeft:
				break;
			case sf::Event::JoystickButtonPressed:
				break;
			case sf::Event::JoystickButtonReleased:
				break;
			case sf::Event::JoystickMoved:
				break;
			case sf::Event::JoystickConnected:
				break;
			case sf::Event::JoystickDisconnected:
				break;
			case sf::Event::TouchBegan:
				break;
			case sf::Event::TouchMoved:
				break;
			case sf::Event::TouchEnded:
				break;
			case sf::Event::SensorChanged:
				break;
			case sf::Event::Count:
				break;
						}
		}
		//------End of Event Handler--------
		window.clear();

		float output = network.forward_propagation({0.5, 0.2});
		network.drawNetwork(window, font);

		window.display();
	}

	return 0;
}
