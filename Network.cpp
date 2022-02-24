#include "Network.h"

float sigmoid(float val)
{
    return (1 / (1 + std::exp(-val)));
}

float sigmoidDerivative(float val)
{
    return sigmoid(val) * (1 - sigmoid(val));
}

Network::Network(std::vector<int> networkLayout)
{
    neurons = std::vector<std::vector<Perceptron>>(networkLayout.size());
    weights = std::vector<std::vector<std::vector<float>>>(neurons.size() - 1);

    // Initialize neurons
    for (int neuronLayer = 0; neuronLayer < networkLayout.size(); neuronLayer++)
    {
        neurons[neuronLayer] = std::vector<Perceptron>(networkLayout[neuronLayer]);
    }

    // Initialize weights
    for (int neuronLayer = 0; neuronLayer < getLayers() - 1; neuronLayer++)
    {
        for (int neuron = 0; neuron < getLayerSize(neuronLayer); neuron++)
        {
            weights[neuronLayer].push_back(std::vector<float>());
            for (int weight = 0; weight < getLayerSize(neuronLayer + 1); weight++)
            {
                weights[neuronLayer][neuron].push_back(rand() % 3 - 1); //-1, 0, 1
            }
        }
    }
}

float Network::forward_propagation(std::vector<int> inputs)
{
    for (int input = 0; input < inputs.size(); input++)
        neurons[0][input].setValue(inputs[input]);

    for (int layer = 0; layer < getLayers(); layer++)
    {
        for (int neuron = 0; neuron < getLayerSize(layer); neuron++)
        {
            if (layer != 0)
            {
                float sum = 0;
                for (int previousNeuron = 0; previousNeuron < getLayerSize(layer - 1); previousNeuron++)
                    sum += neurons[layer - 1][previousNeuron].getValue() * weights[layer - 1][previousNeuron][neuron];

                neurons[layer][neuron].setValue(sigmoid(sum));
            }
        }
    }

    return neurons[neurons.size() - 1][neurons[neurons.size() - 1].size() - 1].getValue();
};

void Network::backward_propation(std::pair<int,int> input, float output, float target){
    // y - target
    // x2 - input
    // x3 - output
    // dE/dw3 = derivative_Cost/Error * derivative_Activation * Input/previousOutput
    // dE/dw3 = (x3-y)(x3)(1-x3)(x2)
    
    // bias -= deleta (error * activation)
    // weight -= input * delta

    //printf("[ %d : %d ] Error: %f\n", input.first, input.second, error);

    // for (int layer = getLayers()-1; layer >= 0; layer--)
    // {

    //     if (layer == getLayers()-1) //Output layer
    //     {
    //         for (int neuron = 0; neuron < getLayerSize(layer); neuron++)
    //         {
    //             float error = output - target;
    //             float activation = sigmoidDerivative(output);

    //             const float delta = error * 1;

    //             //update output weights
    //         }
    //     }
    //     else
    //     {
    //         for (int neuron = 0; neuron < getLayerSize(layer); neuron++)
    //         {
    //             float error = 0;
                
    //             for (int previousNeuron = 0; previousNeuron < getLayerSize(layer+1); previousNeuron++)
    //                 error += 

    //         }
    //     }

    // }
};

void Network::drawNetwork(sf::RenderWindow &window, sf::Font& font)
{
    sf::Text text("", font, 10);

    float max = neurons[0][0].getValue();
    float min = max;

    for (auto layer : neurons)
    {
        for (Perceptron node : layer)
        {
            float val = node.getValue();
            if (val > max)
                max = val;
            if (val < min)
                min = val;
        }
    }

    for (int layer = 0; layer < getLayers(); layer++)
    {
        float h_dist = NWIDTH / (getLayers() + 1);
        float v_dist = NHEIGHT / (getLayerSize(layer) + 1);

        for (int neuron = 0; neuron < getLayerSize(layer); neuron++)
        {
            Perceptron& node = neurons[layer][neuron];

            float contrib = 1 - (node.getValue() - min) / (max - min);

            float x = h_dist * (1 + layer);
            float y = v_dist * (1 + neuron);

            for (int next_node = 0; next_node < getLayerSize(layer + 1); next_node++)
            {

                float v_dist = NHEIGHT / (getLayerSize(layer + 1) + 1);
                float nx = h_dist * (1 + layer + 1);
                float ny = v_dist * (1 + next_node);

                text.setStyle(sf::Text::Bold);
                text.setOrigin(text.getCharacterSize() / 2, text.getCharacterSize() / 2);
                text.setPosition(node.getX() + ((nx - node.getX()) / 2), node.getY() + ((ny - node.getY()) / 2));
                std::string val = std::to_string(std::abs(weights[layer][neuron][next_node]));
                val.resize(4);
                text.setString(val);

                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].position = sf::Vector2f(node.getX(), node.getY());
                line[0].color = (weights[layer][neuron][next_node] < 0) ? sf::Color::Red : sf::Color::Green; 
                line[1].position = sf::Vector2f(nx, ny);
                line[1].color = line[0].color;

                window.draw(line);
                window.draw(text);
            }

            node.draw(x,y,window,font,contrib);

        }
    }
};

std::vector<std::vector<Perceptron>> Network::getNeurons()
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
    neurons[layer][neuron].setValue(val);
};

void Network::setWeight(int layer, int neuron, int weight, float val)
{
    weights[layer][neuron][weight] = val;
};