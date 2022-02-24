#include "Perceptron.h"

Perceptron::Perceptron()
{

}

Perceptron::Perceptron(int numWeights)
{
    for (int weight = 0; weight < numWeights; weight++)
    {
        weights.push_back(rand() % 2 - 1);
    }
}

void Perceptron::draw(float x, float y, sf::RenderWindow &window, sf::Font& font, float gradient)
{
    sf::Text text("", font, 20);

    sf::CircleShape circle(35);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color(255 * gradient, 255 * gradient, 255 * gradient));
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::White);

    std::string s_val = std::to_string(value);
    s_val.resize(4);
    text.setString(s_val);

    text.setOrigin(22, 13);
    text.setFillColor((gradient > 0.5) ? sf::Color::Black : sf::Color::White);

    text.setPosition(x, y);
    circle.setPosition(x, y);

    window.draw(circle);
    window.draw(text);

    this->x = x;
    this->y = y;
}

void Perceptron::updateWeights(float delta)
{
}

void Perceptron::setValue(float value)
{
    this->value = value;
}

void Perceptron::setWeights(std::vector<float> weights)
{
    this->weights = weights;
}

float Perceptron::getValue()
{
    return value;
}

float Perceptron::getDelta()
{
    return delta;
}

float Perceptron::getWeight(int weight)
{
    return weights[weight];
}

std::vector<float> Perceptron::getWeights()
{
    return weights;
}

float Perceptron::getX()
{
    return x;
}

float Perceptron::getY()
{
    return y;
}