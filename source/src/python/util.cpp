#include "signalflow/python/python.h"

void init_python_util(py::module &m)
{
    /*--------------------------------------------------------------------------------
     * Utils
     *-------------------------------------------------------------------------------*/
    m.def("clip", signalflow_clip, R"pbdoc(Clip arg0 between [arg1..arg2])pbdoc");
    m.def("scale_lin_lin", signalflow_scale_lin_lin, R"pbdoc(Scale arg0, from linear range [arg1..arg2] to linear range [arg3..arg4])pbdoc");
    m.def("scale_lin_exp", signalflow_scale_lin_exp, R"pbdoc(Scale arg0, from linear range [arg1..arg2] to exponential range [arg3..arg4])pbdoc");
    m.def("scale_exp_lin", signalflow_scale_exp_lin, R"pbdoc(Scale arg0, from exponential range [arg1..arg2] to linear range [arg3..arg4])pbdoc");

    m.def("frequency_to_midi_note", signalflow_frequency_to_midi_note, R"pbdoc(Map frequency in Hz to a MIDI note value)pbdoc");
    m.def("midi_note_to_frequency", signalflow_midi_note_to_frequency, R"pbdoc(Map MIDI note value to a frequency in Hz)pbdoc");

    m.def("db_to_amp", signalflow_db_to_amp, R"pbdoc(Map decibels to linear amplitude)pbdoc");
    m.def("amp_to_db", signalflow_amp_to_db, R"pbdoc(Map linear amplitude to decibels)pbdoc");

    m.def("save_block_to_text_file", signalflow_save_block_to_text_file, R"pbdoc(Write a block of PCM float samples to a .csv-style text file)pbdoc");
    m.def("save_block_to_wav_file", signalflow_save_block_to_wav_file, R"pbdoc(Write a block of PCM float samples to a .wav file)pbdoc");
}
