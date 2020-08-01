#include "signalflow/node/stochastic/trigger-noise.h"

#include "signalflow/core/random.h"

#include <limits>

namespace signalflow
{

TriggerNoise::TriggerNoise(NodeRef min, NodeRef max, NodeRef clock)
    : min(min), max(max), clock(clock)
{
    this->name = "trigger-noise";
    this->create_input("min", this->min);
    this->create_input("max", this->max);
    this->create_input("clock", this->clock);

    for (int i = 0; i < SIGNALFLOW_MAX_CHANNELS; i++)
        this->value[i] = std::numeric_limits<float>::max();
}

void TriggerNoise::trigger(std::string name, float value)
{
    for (int channel = 0; channel < SIGNALFLOW_MAX_CHANNELS; channel++)
    {
        this->value[channel] = random_uniform(this->min->out[channel][0], this->max->out[channel][0]);
    }
}

void TriggerNoise::process(sample **out, int num_frames)
{
    for (int channel = 0; channel < this->num_output_channels; channel++)
    {
        if (this->value[channel] == std::numeric_limits<float>::max())
        {
            this->value[channel] = random_uniform(this->min->out[channel][0], this->max->out[channel][0]);
        }

        for (int frame = 0; frame < num_frames; frame++)
        {
            if (SIGNALFLOW_CHECK_TRIGGER(clock, frame))
            {
                this->value[channel] = random_uniform(this->min->out[channel][frame], this->max->out[channel][frame]);
            }

            this->out[channel][frame] = this->value[channel];
        }
    }
}

}
