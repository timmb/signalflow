#pragma once

#ifdef HAVE_SOUNDIO

#define AudioOut AudioOut_SoundIO

#include <soundio/soundio.h>
#include <vector>

#include "abstract.h"

#include "signalflow/core/graph.h"
#include "signalflow/node/node.h"

namespace signalflow
{

class AudioOut_SoundIO : public AudioOut_Abstract
{
public:
    AudioOut_SoundIO(const std::string &device_name = "",
                     unsigned int sample_rate = 0,
                     unsigned int buffer_size = 0);

    virtual int init() override;
    virtual int start() override;
    virtual int stop() override;
    virtual int destroy() override;

    struct SoundIo *soundio;
    struct SoundIoDevice *device;
    struct SoundIoOutStream *outstream;

private:
    std::string device_name;
};

REGISTER(AudioOut_SoundIO, "audioout-soundio")

} // namespace signalflow

#endif
