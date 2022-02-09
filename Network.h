#include "Globals.h"

class Network
{
public:
    Network(std::vector<int> network);
    Network(std::vector<std::vector<float>> neurons);

    ~Network() = default;

    float forward_propagation();

    void backward_propation();

    void drawNetwork(sf::RenderWindow &window, sf::Font &font, sf::Text &text);

    std::vector<std::vector<float>> getNeurons();
    std::vector<std::vector<std::vector<float>>> getWeights();

    int getLayers();
    int getLayerSize(int layer);

    void setNeuron(int layer, int neuron, float val);
    void setWeight(int layer, int neuron, int weight, float val);

private:
    std::vector<std::vector<float>> neurons;
    std::vector<std::vector<std::vector<float>>> weights;
};