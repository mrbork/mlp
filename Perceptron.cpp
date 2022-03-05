#include "Perceptron.h"

Perceptron::Perceptron()
: value{}, delta{}, x{}, y{}, weights{}
{
    
}

Perceptron::Perceptron(int value)
: value{value}, delta{}, x{}, y{}, weights{}
{
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
    std::vector<float> previousWeights = weights; //For line search
    
    for (int weight = 0; weight < previousInputs.size(); weight++)  
    {
        weights[weight + 1] -= delta * previousInputs[weight] * LEARNING_RATE;
    }
}

void Perceptron::setValue(float value)
{
    this->value = value;
}

void Perceptron::setDelta(float delta)
{
    this->delta = delta;
}

void Perceptron::setWeights(std::vector<float> weights)
{
    this->weights = weights;
}

void Perceptron::setpreviousInputs(std::vector<int> previousInputs)
{
    this->previousInputs = previousInputs;
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

void Perceptron::addWeight(float weight)
{
    weights.push_back(weight);
}