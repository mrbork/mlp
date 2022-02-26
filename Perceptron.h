#include "Globals.h"

class Perceptron
{
public:
    Perceptron();
    Perceptron(int numWeights);
    ~Perceptron() = default;

    void draw(float x, float y, sf::RenderWindow& window, sf::Font& font, float gradient);
    void updateWeights(float delta);

    float getX();
    float getY();

    void setValue(float value);
    void setWeights(std::vector<float> weights);

    float getValue();
    float getDelta();
    float getWeight(int weight);

    void addWeight(float weight);

    std::vector<float> getWeights();

private:
    float value;
    float delta;
    std::vector<float> weights;

    float x;
    float y;
};