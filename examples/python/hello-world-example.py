#!/usr/bin/env python3

#------------------------------------------------------------------------
# SignalFlow: Hello World example.
#
# Play a sine tone.
#------------------------------------------------------------------------
from signalflow import *

#------------------------------------------------------------------------
# Create the global processing graph.
#------------------------------------------------------------------------
graph = AudioGraph()

#------------------------------------------------------------------------
# Create a sine oscillator, attenuate by 12dB, and pan to stereo.
#------------------------------------------------------------------------
sine = Sine(440)
sine = sine * db_to_amplitude(-12)
stereo = LinearPanner(2, sine)

#------------------------------------------------------------------------
# Play the
#------------------------------------------------------------------------
graph.play(stereo)
graph.start()
graph.wait()