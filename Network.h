#include "Globals.h"
#include "Perceptron.h"

class Network
{
public:
    Network(std::vector<int> networkLayout);

    ~Network() = default;

    float forward_propagation(std::vector<int> inputs);

    void backward_propation(std::pair<int,int> input, float output, float target);

    void drawNetwork(sf::RenderWindow &window, sf::Font& font);

    std::vector<std::vector<Perceptron>> getNeurons();

    int getLayers();
    int getLayerSize(int layer);

    void setNeuron(int layer, int neuron, float val);

private:
    std::vector<std::vector<Perceptron>> neurons;
    std::vector<std::vector<std::vector<float>>> errors;
};