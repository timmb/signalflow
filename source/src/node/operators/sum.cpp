#include "signalflow/core/core.h"
#include "signalflow/node/operators/sum.h"
#include "signalflow/node/oscillators/constant.h"

namespace signalflow
{

Sum::Sum()
{
    this->name = "sum";
}

Sum::Sum(std::initializer_list<NodeRef> inputs)
    : Sum()
{
    for (NodeRef input : inputs)
    {
        this->add_input(input);
    }
}

Sum::Sum(std::vector<NodeRef> inputs)
    : Sum()
{
    for (NodeRef input : inputs)
    {
        this->add_input(input);
    }
}

Sum::Sum(std::vector<float> inputs)
    : Sum()
{
    for (float input : inputs)
    {
        this->add_input(new Constant(input));
    }
}

Sum::Sum(std::vector<int> inputs)
    : Sum()
{
    for (int input : inputs)
    {
        this->add_input(new Constant(input));
    }
}

void Sum::process(sample **out, int num_frames)
{
    for (int channel = 0; channel < this->num_output_channels; channel++)
    {
        memset(this->out[channel], 0, sizeof(sample) * num_frames);
        for (NodeRef input : this->input_list)
        {
            for (int frame = 0; frame < num_frames; frame++)
            {
                this->out[channel][frame] += input->out[channel][frame];
            }
        }
    }
}

void Sum::add_input(NodeRef input)
{
    this->input_list.push_back(input);
    std::string input_name = "input" + std::to_string(this->inputs.size());
    this->Node::add_input(input_name, input_list.back());
}

void Sum::set_input(std::string name, const NodeRef &node)
{
    if (this->inputs.find(name) == this->inputs.end())
    {
        this->input_list.push_back(node);
        this->Node::add_input(name, input_list.back());
    }

    this->Node::set_input(name, node);
}

}
