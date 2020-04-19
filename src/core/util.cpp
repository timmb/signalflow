/*--------------------------------------------------------------------*
 * util.cpp: Helper utilities.
 *--------------------------------------------------------------------*/

#include "signal/core/util.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

namespace libsignal
{

/*--------------------------------------------------------------------*
 * timestamp(): Return microsecond-accurate timestamp.
 * Useful for monitoring function runtimes.
 *--------------------------------------------------------------------*/
double timestamp()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);    
}

/*--------------------------------------------------------------------*
 * clip(): Constrain a value within two bounds.
 *--------------------------------------------------------------------*/
double clip(double value, double min, double max)
{
    if (value < min) value = min;
    if (value > max) value = max;
    return value;
}

/*--------------------------------------------------------------------*
 * map(): Map a value onto a linear range.
 *--------------------------------------------------------------------*/
double map(double value, double fromA, double fromB, double toA, double toB)
{
    double norm = (value - fromA) / (fromB - fromA);
    return toA + norm * (toB - toA);
}

/*--------------------------------------------------------------------*
 * linexp(): Map a value onto an exponential range.
 *--------------------------------------------------------------------*/
double linexp (double value, double a, double b, double c, double d)
{
    if (value <= a) return c;
    if (value >= b) return d;
    return pow(d/c, (value-a)/(b-a)) * c;
}

/*--------------------------------------------------------------------*
 * explin(): Map a value from an exponential to linear range.
 *--------------------------------------------------------------------*/
double explin (double value, double a, double b, double c, double d)
{
    if (value <= a) return c;
    if (value >= b) return d;
    return (log(value / a)) / (log(b / a)) * (d - c) + c;
}


float freq_to_midi(float frequency)
{
    /*--------------------------------------------------------------------*
     * freq_to_midi(): Map a frequency value onto a MIDI note index.
     * 440 = A4 = 69
     *--------------------------------------------------------------------*/
    return 69.0 + 12 * log2(frequency / 440.0);
}


float midi_to_freq(float midi)
{
    /*--------------------------------------------------------------------*
     * midi_to_freq(): Map a MIDI note to a frequency value.
     * 440 = A4 = 69
     *--------------------------------------------------------------------*/
    return 440.0 * powf(2, (midi - 69) / 12.0);
}

} /* namespace libsignal */