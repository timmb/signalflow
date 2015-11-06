#include "env.h"

namespace signum::env
{

ASR::ASR(float attack, float sustain, float release)
{
	this->attack = attack;
	this->sustain = sustain;
	this->release = release;
	this->phase = 0.0;
}

void ASR::trigger()
{
	this->phase = 0.0;
}

void ASR::next(int count)
{
	sample *ptr = this->output->data[0];

	for (int i = 0; i < count; i++)
	{
		if (this->phase < this->attack)
		{
			*ptr = (this->phase / this->attack);
		}
		else if (this->phase <= this->attack + this->sustain)
		{
			*ptr = 1.0;
		}
		else if (this->phase < this->attack + this->sustain + this->release)
		{
			*ptr = 1.0 - (this->phase - (this->attack + this->sustain)) / this->release;
		}
		else
		{
			*ptr = 0.0;
		}

		this->phase += 1.0 / 44100.0;
		ptr++;
	}
}

}