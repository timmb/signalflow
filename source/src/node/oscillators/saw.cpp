#include "signalflow/core/graph.h"
#include "signalflow/node/oscillators/saw.h"

namespace signalflow
{

Saw::Saw(NodeRef frequency)
    : frequency(frequency)
{
    SIGNALFLOW_CHECK_GRAPH();

    this->name = "saw";
    this->create_input("frequency", this->frequency);
    memset(this->phase, 0, sizeof(this->phase));
}

void Saw::process(sample **out, int num_frames)
{
    for (int channel = 0; channel < this->num_output_channels; channel++)
    {
        for (int frame = 0; frame < num_frames; frame++)
        {
            float rv = (this->phase[channel] * 2.0) - 1.0;

            out[channel][frame] = rv;

            this->phase[channel] += this->frequency->out[channel][frame] / this->graph->get_sample_rate();
            while (this->phase[channel] >= 1.0)
                this->phase[channel] -= 1.0;
        }
    }
}

}
