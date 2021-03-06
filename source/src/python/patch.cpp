#include "signalflow/python/python.h"

void init_python_patch(py::module &m)
{
    /*--------------------------------------------------------------------------------
     * Patch
     *-------------------------------------------------------------------------------*/
    py::class_<Patch, PatchRefTemplate<Patch>>(m, "Patch")
        .def(py::init<PatchSpecRef, std::unordered_map<std::string, NodeRef>>())
        .def(py::init<PatchSpecRef>())
        .def(py::init<PatchRef, std::unordered_map<std::string, NodeRef>>())
        .def(py::init<PatchRef>())
        .def(py::init<>())

        .def("__mul__", [](PatchRef a, NodeRef b) { return a * b; })
        .def("__mul__", [](PatchRef a, float b) { return a * NodeRef(b); })
        .def("__add__", [](PatchRef a, NodeRef b) { return a + b; })
        .def("__add__", [](PatchRef a, float b) { return a + NodeRef(b); })
        .def("__sub__", [](PatchRef a, NodeRef b) { return a - b; })
        .def("__sub__", [](PatchRef a, float b) { return a - NodeRef(b); })
        .def("__truediv__", [](PatchRef a, NodeRef b) { return a / b; })
        .def("__truediv__", [](PatchRef a, float b) { return a / NodeRef(b); })

        // Breaks other properties (auto_free, inputs, etc).
        // Need a policy on this: either *only* inputs should be accessible through properties,
        // or inputs should all only be accessible through set_input(...)
        // .def("__setattr__", [](PatchRef a, std::string attr, NodeRef value) { a->set_input(attr, value); })
        .def("set_input", [](Patch &patch, std::string name, float value) { patch.set_input(name, value); })
        .def("set_input", [](Patch &patch, std::string name, NodeRef node) { patch.set_input(name, node); })
        .def("set_input", [](Patch &patch, std::string name, BufferRef buffer) { patch.set_input(name, buffer); })
        .def("set_auto_free", &Patch::set_auto_free)
        .def("get_auto_free", &Patch::get_auto_free)
        .def_property("auto_free", &Patch::get_auto_free, &Patch::set_auto_free)
        .def_readonly("output", &Patch::output)
        .def_readonly("nodes", &Patch::nodes)
        .def_readonly("inputs", &Patch::inputs)

        .def("play", [](PatchRef patch) { patch->get_graph()->play(patch); })
        .def("stop", [](PatchRef patch) { patch->get_graph()->stop(patch); })

        // template methods
        .def("add_input", [](Patch &patch, std::string name) { return patch.add_input(name); })
        .def("add_input", [](Patch &patch, std::string name, float value) { return patch.add_input(name, value); })
        .def("add_input", &Patch::add_input)
        .def("add_buffer_input", &Patch::add_buffer_input)
        .def("add_node", &Patch::add_node)
        .def("set_output", &Patch::set_output)
        .def("create_spec", &Patch::create_spec);

    py::class_<PatchSpec, PatchSpecRefTemplate<PatchSpec>>(m, "PatchSpec")
        .def(py::init<std::string>())
        .def_property_readonly("name", &PatchSpec::get_name)
        .def("print", [](PatchSpec &patchspec) { patchspec.print(); })
        .def("load", &PatchSpec::load)
        .def("save", &PatchSpec::save)
        .def("to_json", &PatchSpec::to_json)
        .def("from_json", &PatchSpec::from_json);

    py::class_<PatchRegistry>(m, "PatchRegistry")
        .def(py::init(&PatchRegistry::global))
        .def("create", &PatchRegistry::create);
}
