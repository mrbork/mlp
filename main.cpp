#include "Globals.h"
#include "Network.h"

float costFunction(float target, float output)
{
	return 0.5 * pow(target - output, 2);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(510 + NWIDTH, 400), "SFML", sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	Network network({2, 2, 1});

	sf::Font font;
	sf::Text text("", font, 15);
	text.setString("Error: ");

	if (!font.loadFromFile("OCRAEXT.TTF"))
		printf("Failed to load font\n");

	sf::Image image;
	image.create(OUTPUT_WIDTH, OUTPUT_HEIGHT);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite pixels;
	pixels.setPosition(NWIDTH, 0);
	pixels.setScale(CWIDTH / OUTPUT_WIDTH, CHEIGHT / OUTPUT_HEIGHT);
	pixels.setTexture(texture);

	std::vector<std::pair<int, int>> inputs;

	for (int i = 0; i < OUTPUT_WIDTH; i++)
		for (int j = 0; j < OUTPUT_HEIGHT; j++)
			inputs.push_back(std::pair<int, int>(i, j));

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

		network.drawNetwork(window, font); 

		float error = 0;

		std::random_shuffle(inputs.begin(), inputs.end());
		for (auto input : inputs)
		{
			float output = network.forward_propagation({input.first, input.second});
			image.setPixel(input.first, input.second, sf::Color(255 * output, 255 * output, 255 * output));

			float target = (input.first < input.second) ? 1.0f : 0.0f;
			//float target = (input.first < input.second + 10 && input.first > input.second -10) ? 1.0f : 0.0f;

			network.backward_propation(input, output, target);

			//Reference 
			//image.setPixel(input.first, input.second, sf::Color(255 * target, 255 * target, 255 * target));


			error += std::abs( output - target );
		}

		text.setString(std::to_string(error));

		texture.update(image);

		window.draw(pixels);
		window.draw(text);

		window.display();
	}

	return 0;
}
