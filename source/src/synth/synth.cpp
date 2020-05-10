#include "signal/synth/synth.h"

#include "signal/core/core.h"
#include "signal/core/graph.h"
#include "signal/node/oscillators/constant.h"
#include "signal/synth/synthregistry.h"

#include <iostream>
#include <memory>

namespace libsignal
{

extern AudioGraph *shared_graph;

Synth::Synth()
{
    this->graph = shared_graph;
    this->auto_free = false;
}

Synth::Synth(SynthSpecRef synthspec)
    : Synth()
{
    NodeDefinition nodedef = synthspec->get_root();
    this->output = this->instantiate(&nodedef);
}

Synth::Synth(SynthTemplateRef synthtemplate)
    : Synth(synthtemplate->parse())
{
}

Synth::Synth(std::string name)
    : Synth()
{
    SynthSpecRef synthspec = SynthRegistry::global()->get(name);
    if (synthspec)
    {
        NodeDefinition nodedef = synthspec->get_root();
        this->output = this->instantiate(&nodedef);
    }
}

Synth::~Synth()
{
}

signal_synth_state_t Synth::get_state()
{
    return this->state;
}

void Synth::set_state(signal_synth_state_t state)
{
    this->state = state;
}

NodeRef Synth::instantiate(NodeDefinition *nodedef)
{
    /*------------------------------------------------------------------------
     * Recursively instantiate the subgraph specified in NodeDefinition.
     * Does not currently support graphs that route one node to multiple
     * inputs.
     *-----------------------------------------------------------------------*/
    NodeRegistry *registry = NodeRegistry::global();

    NodeRef noderef;

    if (!nodedef->input_name.empty() && this->inputs[nodedef->input_name])
    {
        noderef = this->inputs[nodedef->input_name];
    }
    else
    {
        Node *node = registry->create(nodedef->name);
        noderef = NodeRef(node);

        /*------------------------------------------------------------------------
         * Update the synth's internal collection of node refs.
         *-----------------------------------------------------------------------*/
        this->nodes.insert(noderef);

        for (auto param : nodedef->params)
        {
            std::string param_name = param.first;
            NodeRef param_node = this->instantiate(param.second);
            noderef->set_input(param_name, param_node);
        }

        if (nodedef->is_constant)
        {
            Constant *constant = (Constant *) node;
            constant->value = nodedef->value;
        }

        if (!nodedef->input_name.empty())
        {
            this->inputs[nodedef->input_name] = noderef;
        }

        noderef->set_synth(this);
    }

    return noderef;
}

void Synth::set_input(std::string name, float value)
{
    NodeRef current = this->inputs[name];
    signal_assert(this->inputs[name] != nullptr, "Synth has no such parameter: %s", name.c_str());
    NodeRef input = this->inputs[name];
    Constant *constant = (Constant *) input.get();
    constant->value = value;
}

void Synth::set_input(std::string name, NodeRef value)
{
    /*------------------------------------------------------------------------
     * Replace a named input with another node.
     * Iterate over this synth's nodes, replacing the prior input with
     * the new node. (Inefficient, should be rethought.)
     *-----------------------------------------------------------------------*/
    signal_assert(this->inputs[name] != nullptr, "Synth has no such parameter: %s", name.c_str());
    NodeRef current = this->inputs[name];
    for (NodeRef node : this->nodes)
    {
        for (auto param : node->inputs)
        {
            if ((param.second)->get() == current.get())
            {
                // Update routing
                node->set_input(param.first, value);
            }
        }
    }
    this->inputs[name] = value;
}

void Synth::disconnect()
{
    this->graph->remove_output(this);
}

bool Synth::get_auto_free()
{
    return this->auto_free;
}
void Synth::set_auto_free(bool value)
{
    this->auto_free = value;
}

void Synth::node_state_changed(Node *node)
{
    if (node->get_state() == SIGNAL_NODE_STATE_FINISHED && this->auto_free)
    {
        this->set_state(SIGNAL_SYNTH_STATE_FINISHED);
        this->disconnect();
    }
}

}