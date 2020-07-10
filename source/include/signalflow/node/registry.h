#pragma once

#include <functional>
#include <unordered_map>

#include "signalflow/patch/nodespec.h"

#define REGISTER(CLASS, NAME) static bool CLASS##OK = NodeRegistry::global()->add<CLASS>(NAME);

namespace signalflow
{

class Node;
class Patch;

template <typename T>
Node *create()
{
    return new T;
}

class NodeRegistry
{
public:
    NodeRegistry();

    static NodeRegistry *global();

    Node *create(std::string name);
    Node *create(NodeSpec definition);

    /*------------------------------------------------------------------------
     * (Function template implementations must be in .h file.)
     * http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
     *-----------------------------------------------------------------------*/
    template <class T>
    bool add(std::string name)
    {
        classes[name] = &::signalflow::create<T>;
        return true;
    }

    /*------------------------------------------------------------------------
     * Maps node names to constructors
     *-----------------------------------------------------------------------*/
    std::unordered_map<std::string, std::function<Node *()>> classes;
};

}