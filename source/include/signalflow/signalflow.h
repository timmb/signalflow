/*------------------------------------------------------------------------
 * Core
 *-----------------------------------------------------------------------*/
#include <signalflow/buffer/ringbuffer.h>
#include <signalflow/core/constants.h>
#include <signalflow/core/core.h>
#include <signalflow/core/exceptions.h>
#include <signalflow/core/graph.h>
#include <signalflow/core/property.h>
#include <signalflow/core/random.h>
#include <signalflow/core/util.h>
#include <signalflow/core/version.h>

#include <signalflow/buffer/buffer.h>

#include <signalflow/patch/nodespec.h>
#include <signalflow/patch/patch.h>
#include <signalflow/patch/patchspec.h>

#include <signalflow/node/node.h>
#include <signalflow/node/registry.h>

/*------------------------------------------------------------------------
 * Operators
 *-----------------------------------------------------------------------*/
#include <signalflow/node/operators/add.h>
#include <signalflow/node/operators/channel-array.h>
#include <signalflow/node/operators/channel-mixer.h>
#include <signalflow/node/operators/channel-select.h>
#include <signalflow/node/operators/divide.h>
#include <signalflow/node/operators/multiply.h>
#include <signalflow/node/operators/pow.h>
#include <signalflow/node/operators/round.h>
#include <signalflow/node/operators/scale.h>
#include <signalflow/node/operators/subtract.h>

/*------------------------------------------------------------------------
 * I/O
 *-----------------------------------------------------------------------*/
#include <signalflow/node/io/output/abstract.h>
#include <signalflow/node/io/output/ios.h>
#include <signalflow/node/io/output/soundio.h>

#include <signalflow/node/io/input/abstract.h>
#include <signalflow/node/io/input/soundio.h>

/*------------------------------------------------------------------------
 * Oscillators
 *-----------------------------------------------------------------------*/
#include <signalflow/node/oscillators/constant.h>
#include <signalflow/node/oscillators/impulse.h>
#include <signalflow/node/oscillators/line.h>
#include <signalflow/node/oscillators/saw.h>
#include <signalflow/node/oscillators/sine.h>
#include <signalflow/node/oscillators/square.h>
#include <signalflow/node/oscillators/triangle.h>
#include <signalflow/node/oscillators/wavetable.h>

/*------------------------------------------------------------------------
 * Buffer players
 *-----------------------------------------------------------------------*/
#include <signalflow/node/buffer/buffer-player.h>
#include <signalflow/node/buffer/buffer-recorder.h>
#include <signalflow/node/buffer/granulator.h>

/*------------------------------------------------------------------------
 * Random processes
 *-----------------------------------------------------------------------*/
#include <signalflow/node/stochastic/logistic.h>
#include <signalflow/node/stochastic/noise.h>
#include <signalflow/node/stochastic/random-impulse.h>
#include <signalflow/node/stochastic/trigger-noise.h>

/*------------------------------------------------------------------------
 * Envelopes
 *-----------------------------------------------------------------------*/
#include <signalflow/node/envelope/adsr.h>
#include <signalflow/node/envelope/asr.h>

/*------------------------------------------------------------------------
 * Effects
 *-----------------------------------------------------------------------*/
#include <signalflow/node/filters/biquad.h>
#include <signalflow/node/filters/delays/allpass.h>
#include <signalflow/node/filters/delays/comb.h>
#include <signalflow/node/filters/delays/onetap.h>
#include <signalflow/node/filters/delays/stutter.h>
#include <signalflow/node/filters/eq.h>
#include <signalflow/node/filters/gate.h>
#include <signalflow/node/filters/maximiser.h>
#include <signalflow/node/filters/moog.h>
#include <signalflow/node/filters/pan.h>
#include <signalflow/node/filters/resample.h>
#include <signalflow/node/filters/rms.h>
#include <signalflow/node/filters/sample-and-hold.h>
#include <signalflow/node/filters/smooth.h>
#include <signalflow/node/filters/squiz.h>
#include <signalflow/node/filters/waveshaper.h>
#include <signalflow/node/filters/width.h>

/*------------------------------------------------------------------------
 * Sequencing
 *-----------------------------------------------------------------------*/
#include <signalflow/node/sequencing/counter.h>
#include <signalflow/node/sequencing/index.h>

/*------------------------------------------------------------------------
 * Analysis and MIR
 * (In development)
 *-----------------------------------------------------------------------*/
// #include <signalflow/node/analysis/vamp.h>

/*------------------------------------------------------------------------
 * Control interfaces
 *-----------------------------------------------------------------------*/
#include <signalflow/node/control/mouse.h>

/*------------------------------------------------------------------------
 * FFT
 *-----------------------------------------------------------------------*/
#include <signalflow/node/fft/continuous-pv.h>
#include <signalflow/node/fft/fft.h>
#include <signalflow/node/fft/find-peaks.h>
#include <signalflow/node/fft/ifft.h>
#include <signalflow/node/fft/lpf.h>
#include <signalflow/node/fft/noise-gate.h>
#include <signalflow/node/fft/phase-vocoder.h>
#include <signalflow/node/fft/tonality.h>

#ifdef __APPLE__
#include <signalflow/node/fft/convolve.h>
#endif