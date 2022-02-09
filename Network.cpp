#include "Network.h"

float sigmoid(float val){
    return (val /(1 + abs(val)));
}

Network::Network(std::vector<int> network){

};

Network::Network(std::vector<std::vector<float>> neurons)
{
    this->neurons = neurons;
    weights = std::vector<std::vector<std::vector<float>>>(neurons.size() - 2);

    //Loop through hidden layers and add weights to each hidden neuron
    for (int neuronLayer = 1; neuronLayer < getLayers()-1; neuronLayer++)
    {
        for (int neuron = 0; neuron < getLayerSize(neuronLayer); neuron++)
        {
            weights[neuronLayer-1].push_back(std::vector<float>());
            for (int weight = 0; weight < getLayerSize(neuronLayer-1) ; weight++)
            {
                weights[neuronLayer-1][neuron].push_back(neurons[neuronLayer][neuron]);
            }
        }
    }
}

float Network::forward_propagation(){
    
};

void Network::backward_propation(){

};

void Network::drawNetwork(sf::RenderWindow &window, sf::Font &font, sf::Text &text)
{

    float max = neurons[0][0];
    float min = max;

    for (auto layer : neurons)
    {
        for (float val : layer)
        {
            if (val > max)
                max = val;
            if (val < min)
                min = val;
        }
    }

    for (int layer = 0; layer < getLayers(); layer++)
    {
        float h_dist = WIDTH / (getLayers() + 1);
        float v_dist = HEIGHT / (getLayerSize(layer) + 1);

        for (int node = 0; node < getLayerSize(layer); node++)
        {
            float contrib = 1 - (neurons[layer][node] - min) / (max - min);

            sf::CircleShape circle(35);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setFillColor(sf::Color(255 * contrib, 255 * contrib, 255 * contrib));
            circle.setOutlineThickness(2);
            circle.setOutlineColor(sf::Color::White);

            float x = h_dist * (1 + layer);
            float y = v_dist * (1 + node);

            std::string val = std::to_string(neurons[layer][node]);
            val.resize(4);
            text.setString(val);

            text.setOrigin(22, 13);
            text.setFillColor((contrib > 0.5) ? sf::Color::Black : sf::Color::White);

            text.setPosition(x, y);
            circle.setPosition(x, y);

            // for (int next_node = 0; next_node < getLayerSize(layer + 1); next_node++)
            // {

            //     float v_dist = HEIGHT / (getLayerSize(layer + 1) + 1);
            //     float nx = h_dist * (1 + layer + 1);
            //     float ny = v_dist * (1 + next_node);

            //     sf::Text wtext("", font, 10);
            //     wtext.setStyle(sf::Text::Bold);
            //     wtext.setOrigin(wtext.getCharacterSize() / 2, wtext.getCharacterSize() / 2);
            //     wtext.setPosition(circle.getPosition().x + ((nx - circle.getPosition().x) / 2), circle.getPosition().y + ((ny - circle.getPosition().y) / 2));
            //     std::string val = std::to_string(weights[layer][node]);
            //     val.resize(4);
            //     wtext.setString(val);

            //     sf::VertexArray line(sf::LinesStrip, 2);
            //     line[0].position = circle.getPosition();
            //     line[0].color = sf::Color::White;
            //     line[1].position = sf::Vector2f(nx, ny);
            //     line[1].color = sf::Color::White;

            //     window.draw(line);
            //     window.draw(wtext);
            // }

            window.draw(circle);
            window.draw(text);
        }
    }
};

std::vector<std::vector<float>> Network::getNeurons()
{
    return neurons;
};

std::vector<std::vector<std::vector<float>>> Network::getWeights()
{
    return weights;
};

int Network::getLayers()
{
    return neurons.size();
}

int Network::getLayerSize(int layer)
{
    return neurons[layer].size();
}

void Network::setNeuron(int layer, int neuron, float val)
{
    neurons[layer][neuron] = val;
};

void Network::setWeight(int layer, int neuron, int weight, float val)
{
    weights[layer][neuron][weight] = val;
};