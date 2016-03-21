#include "sine.h"

#include <math.h>
#include <stdio.h>

namespace libsignal
{

void Sine::next(sample **out, int num_frames)
{
	for (int frame = 0; frame < num_frames; frame++)
	{
		float freq = this->frequency->out[0][frame];
		out[0][frame] = sin(this->phase * M_PI * 2.0);
		this->phase += freq / this->graph->sample_rate;

		while (this->phase > 1.0)
			this->phase -= 1.0;
	}
}

}