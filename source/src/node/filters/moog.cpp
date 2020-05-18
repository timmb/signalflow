#include "signal/node/filters/moog.h"
#include "signal/core/graph.h"

#include <stdlib.h>

namespace libsignal
{

MoogVCF::MoogVCF(NodeRef input, NodeRef cutoff, NodeRef resonance)
    : UnaryOpNode(input), cutoff(cutoff), resonance(resonance)
{
    this->name = "moog";
    this->add_input("cutoff", this->cutoff);
    this->add_input("resonance", this->resonance);

    int int_buf_size = SIGNAL_MAX_CHANNELS * sizeof(int);
    memset(out1, 0, int_buf_size);
    memset(out2, 0, int_buf_size);
    memset(out3, 0, int_buf_size);
    memset(out4, 0, int_buf_size);
    memset(in1, 0, int_buf_size);
    memset(in2, 0, int_buf_size);
    memset(in3, 0, int_buf_size);
    memset(in4, 0, int_buf_size);
}

void MoogVCF::process(sample **out, int num_frames)
{
    for (int channel = 0; channel < num_output_channels; channel++)
    {
        for (int frame = 0; frame < num_frames; frame++)
        {
            float cutoff = map(this->cutoff->out[channel][frame], 0, this->graph->get_sample_rate() / 2, 0.005, 1);
            float resonance = this->resonance->out[channel][frame];
            float f = cutoff * 1.16;
            float fb = resonance * (1.0 - 0.15 * f * f);

            /*------------------------------------------------------------------------
             * Calculate filter
             *-----------------------------------------------------------------------*/
            float input = this->input->out[channel][frame];

            input -= out4[channel] * fb;
            input *= 0.35013 * f * f * f * f;

            /*------------------------------------------------------------------------
             * Pole 1
             *-----------------------------------------------------------------------*/
            out1[channel] = input + 0.3 * in1[channel] + (1 - f) * out1[channel];
            in1[channel] = input;

            /*------------------------------------------------------------------------
             * Pole 2
             *-----------------------------------------------------------------------*/
            out2[channel] = out1[channel] + 0.3 * in2[channel] + (1 - f) * out2[channel];
            in2[channel] = out1[channel];

            /*------------------------------------------------------------------------
             * Pole 3
             *-----------------------------------------------------------------------*/
            out3[channel] = out2[channel] + 0.3 * in3[channel] + (1 - f) * out3[channel];
            in3[channel] = out2[channel];

            /*------------------------------------------------------------------------
             * Pole 4
             *-----------------------------------------------------------------------*/
            out4[channel] = out3[channel] + 0.3 * in4[channel] + (1 - f) * out4[channel];
            in4[channel] = out3[channel];

            out[channel][frame] = out4[channel];
        }
    }
}

}
