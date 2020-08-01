#pragma once

#include "signalflow/node/node.h"

namespace signalflow
{
class TriggerNoise : public Node
{
public:
    TriggerNoise(NodeRef min = 0.0, NodeRef max = 1.0, NodeRef clock = 0.0);

    NodeRef min;
    NodeRef max;
    NodeRef clock;

    sample value[SIGNALFLOW_MAX_CHANNELS];

    virtual void process(sample **out, int num_frames);
    virtual void trigger(std::string = SIGNALFLOW_DEFAULT_TRIGGER, float value = 0.0);
};

REGISTER(TriggerNoise, "trigger-noise")
}
