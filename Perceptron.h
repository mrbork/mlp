#include "Globals.h"

class Perceptron
{
public:
    Perceptron();
    Perceptron(int value);
    ~Perceptron() = default;

    void draw(float x, float y, sf::RenderWindow& window, sf::Font& font, float gradient);
    void updateWeights(float delta);

    float getX();
    float getY();

    void setValue(float value);
    void setDelta(float delta);
    void setWeights(std::vector<float> weights);
    void setpreviousInputs(std::vector<int> previousInputs);

    float getValue();
    float getDelta();
    float getWeight(int weight);

    void addWeight(float weight);

    std::vector<float> getWeights();

private:
    float value;
    float delta;
    std::vector<float> weights;

    std::vector<int> previousInputs;

    float x;
    float y;
};