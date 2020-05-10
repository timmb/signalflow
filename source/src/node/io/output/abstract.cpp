#include "signal/node/io/output/abstract.h"

namespace libsignal
{

AudioOut_Abstract::AudioOut_Abstract(AudioGraph *graph)
{
    this->graph = graph;

    this->name = "audioout";
    // this->num_input_channels = 2;
    this->num_output_channels = 2;
    this->no_input_upmix = true;
    this->min_output_channels = 2;
    this->max_output_channels = 2;
    this->input_index = 0;
}

void AudioOut_Abstract::process(sample **out, int num_frames)
{
    this->zero_output();

    for (NodeRef input : this->audio_inputs)
    {
        for (int channel = 0; channel < input->num_output_channels; channel++)
        {
#ifdef __APPLE__

            vDSP_vadd(input->out[channel], 1, out[channel], 1, out[channel], 1, num_frames);

#else

            for (int frame = 0; frame < num_frames; frame++)
            {
                out[channel][frame] += input->out[channel][frame];
            }

#endif
        }
    }
}

void AudioOut_Abstract::add_input(NodeRef node)
{
    audio_inputs.push_back(node);
    std::string input_name = "input" + std::to_string(input_index);
    this->input_index++;
    this->Node::add_input(input_name, audio_inputs.back());
}

void AudioOut_Abstract::remove_input(NodeRef node)
{
    bool removed = false;
    for (auto param : this->inputs)
    {
        if (*(param.second) == node)
        {
            this->Node::remove_input(param.first);
            removed = true;
            break;
        }
    }
    if (!removed)
    {
        throw std::runtime_error("Couldn't find node to remove");
    }
    audio_inputs.remove(node);
}

} // namespace libsignal