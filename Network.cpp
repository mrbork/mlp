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

    // Initialize neurons
    for (int neuronLayer = 0; neuronLayer < networkLayout.size(); neuronLayer++)
    {
        neurons[neuronLayer] = std::vector<Perceptron>(networkLayout[neuronLayer]);

        if(neuronLayer != networkLayout.size() - 1)
            neurons[neuronLayer].insert(neurons[neuronLayer].begin(), Perceptron(1)); // Add a bias neuron to the beginning of vector
    }

    // Initialize weights
    for (int neuronLayer = neurons.size() - 1; neuronLayer > 0; neuronLayer--)
    {
        for (Perceptron &neuron : neurons[neuronLayer])
        {
            for (int input = 0; input < getLayerSize(neuronLayer - 1); input++)
            {
                if (neuron.getValue() != 1 ) // Not a bias neuron
                    neuron.addWeight( (rand() % 2) ? 1 : -1); //-1, 1
            }
        }
    }
}

float Network::forward_propagation(std::vector<int> inputs)
{
    for (int input = 0; input < inputs.size(); input++)
        neurons[0][input + 1].setValue(inputs[input]);

    for (int layer = 1; layer < getLayers(); layer++)
    {
        for (int neuronIndex = 0; neuronIndex < getLayerSize(layer); neuronIndex++)
        {
            if (neuronIndex == 0 && layer < getLayers() - 1)
                continue;

            Perceptron &neuron = neurons[layer][neuronIndex];
            std::vector<int> inputs;

            float sum = 0;
            for (int previousNeuron = 0; previousNeuron < getLayerSize(layer - 1); previousNeuron++)
            {
                if (previousNeuron == 0 && layer < getLayers() - 1)
                {
                    sum += 1;
                    continue;
                }

                sum += neurons[layer - 1][previousNeuron].getValue() * neuron.getWeight(previousNeuron);
                inputs.push_back(neurons[layer - 1][previousNeuron].getValue());
            }

            neuron.setpreviousInputs(inputs);

            neurons[layer][neuronIndex].setValue(sigmoid(sum));
        }
    }

    return neurons[neurons.size() - 1][neurons[neurons.size() - 1].size() - 1].getValue();
}

void Network::backward_propation(std::pair<int, int> input, float output, float target)
{
    // y - target
    // x2 - input
    // x3 - output
    // dE/dw3 = derivative_Cost/Error * derivative_Activation * Input/previousOutput
    // dE/dw3 = (x3-y)(x3)(1-x3)(x2)

    // bias -= deleta (error * activation)
    // weight -= input * delta

    // printf("[ %d : %d ] Error: %f\n", input.first, input.second, error);

    for (int layer = getLayers() - 1; layer > 0; layer--)
    {

        if (layer == getLayers() - 1) // Output layer
        {
            for (int neuronIndex = 0; neuronIndex < getLayerSize(layer); neuronIndex++)
            {
                Perceptron &neuron = neurons[layer][neuronIndex];

                float error = output - target;
                float activation = sigmoidDerivative(output);

                float delta = error * 1;

                neuron.setDelta(delta);

                neuron.updateWeights(delta);
            }
        }
        else
        {// Need to correct weight for bias
            for (int neuronIndex = 1; neuronIndex < getLayerSize(layer); neuronIndex++)
            {
                Perceptron &neuron = neurons[layer][neuronIndex];

                float error = 0;
                for (int previousNeuronIndex = 0; previousNeuronIndex < getLayerSize(layer + 1); previousNeuronIndex++){
                    if (previousNeuronIndex == 0  && layer + 1 < getLayers() - 1) 
                        continue;

                    Perceptron& previousNeuron = neurons[layer + 1][previousNeuronIndex];
                    error += previousNeuron.getDelta() * previousNeuron.getWeight(neuronIndex);
                }

                float activation = sigmoidDerivative(output);
                
                float delta = error * activation;

                neuron.setDelta(delta);

                neuron.updateWeights(delta);
            }
        }
    }
};

void Network::drawNetwork(sf::RenderWindow &window, sf::Font &font)
{
    sf::Text text("", font, 10);

    float max = getMaxMin().first;
    float min = getMaxMin().second;

    for (int layer = 0; layer < getLayers(); layer++)
    {
        float h_dist = NWIDTH / (getLayers() + 1);
        float v_dist = NHEIGHT / (getLayerSize(layer) + 1);

        for (int neuronIndex = 0; neuronIndex < getLayerSize(layer); neuronIndex++)
        {
            Perceptron &neuron = neurons[layer][neuronIndex];

            float contrib = 1 - (neuron.getValue() - min) / (max - min);

            float x = h_dist * (1 + layer);
            float y = v_dist * (1 + neuronIndex);

            for (int next_node = 0; next_node < getLayerSize(layer + 1); next_node++)
            {
                if (next_node == 0 && layer < getLayers() - 2) // Ignore bias neurons
                    continue;

                Perceptron &nextNeuron = neurons[layer + 1][next_node];

                float v_dist = NHEIGHT / (getLayerSize(layer + 1) + 1);
                float nx = h_dist * (1 + layer + 1);
                float ny = v_dist * (1 + next_node);

                text.setStyle(sf::Text::Bold);
                text.setOrigin(text.getCharacterSize() / 2, text.getCharacterSize() / 2);
                text.setPosition(neuron.getX() + ((nx - neuron.getX()) / 2), neuron.getY() + ((ny - neuron.getY()) / 2));
                std::string val = std::to_string(std::abs(nextNeuron.getWeight(neuronIndex)));
                val.resize(4);
                text.setString(val);

                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].position = sf::Vector2f(neuron.getX(), neuron.getY());
                line[0].color = (nextNeuron.getWeight(neuronIndex) < 0) ? sf::Color::Red : sf::Color::Green;
                line[1].position = sf::Vector2f(nx, ny);
                line[1].color = line[0].color;

                window.draw(line);
                window.draw(text);
            }

            neuron.draw(x, y, window, font, contrib);
        }
    }
};

std::vector<std::vector<Perceptron>> Network::getNeurons()
{
    return neurons;
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
}

std::pair<float, float> Network::getMaxMin()
{
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

    return std::pair<float, float>(max, min);
}