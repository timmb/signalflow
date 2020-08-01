#pragma once

#include "signalflow/core/constants.h"
#include "signalflow/node/node.h"

namespace signalflow
{
class EQ : public UnaryOpNode
{
public:
    EQ(NodeRef input = 0.0, NodeRef low_gain = 1.0, NodeRef mid_gain = 1.0, NodeRef high_gain = 1.0,
       NodeRef low_freq = 500, NodeRef high_freq = 5000);

    NodeRef low_gain;
    NodeRef mid_gain;
    NodeRef high_gain;
    NodeRef low_freq;
    NodeRef high_freq;

    virtual void process(sample **out, int num_frames);

private:
    float f1p0[SIGNALFLOW_MAX_CHANNELS], f1p1[SIGNALFLOW_MAX_CHANNELS], f1p2[SIGNALFLOW_MAX_CHANNELS], f1p3[SIGNALFLOW_MAX_CHANNELS];
    float f2p0[SIGNALFLOW_MAX_CHANNELS], f2p1[SIGNALFLOW_MAX_CHANNELS], f2p2[SIGNALFLOW_MAX_CHANNELS], f2p3[SIGNALFLOW_MAX_CHANNELS];
    float sdm1[SIGNALFLOW_MAX_CHANNELS], sdm2[SIGNALFLOW_MAX_CHANNELS], sdm3[SIGNALFLOW_MAX_CHANNELS];
};

REGISTER(EQ, "eq")
}
