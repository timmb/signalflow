#pragma once

/**----------------------------------------------------------------------------------
 * @file patch-spec.h
 * @brief PatchSpec describes the structure of a Patch.
 *
 *---------------------------------------------------------------------------------*/

#include "signalflow/node/node.h"
#include "signalflow/patch/patch-node-spec.h"
#include <map>

namespace signalflow
{

class PatchSpec
{
public:
    /**----------------------------------------------------------------------------------
     * Create a new PatchSpec with the given name. The name is used to uniquely
     * identify the patch in the global PatchRegistry.
     *
     * @param name A human-readable name, used to uniquely identify
     *
     *---------------------------------------------------------------------------------*/
    PatchSpec(std::string name);

    /**----------------------------------------------------------------------------------
     * Methods for creating a PatchSpec from NodeSpecs.
     *
     *---------------------------------------------------------------------------------*/
    void add_node_spec(PatchNodeSpec node);
    void set_output(PatchNodeSpec node);
    PatchNodeSpec *get_node_spec(int id);
    PatchNodeSpec get_root();

    /**----------------------------------------------------------------------------------
     * Query a PatchSpec's name.
     * @returns The human-readable name.
     *
     *---------------------------------------------------------------------------------*/
    std::string get_name();

    /*----------------------------------------------------------------------------------
     * Load a PatchSpec from disk.
     *---------------------------------------------------------------------------------*/
    void load(std::string filename);

    /*----------------------------------------------------------------------------------
     * Save a PatchSpec to disk.
     *---------------------------------------------------------------------------------*/
    void save(std::string filename);

    /*----------------------------------------------------------------------------------
     * Load a PatchSpec from json text.
     *---------------------------------------------------------------------------------*/
    void from_json(std::string json);

    /*----------------------------------------------------------------------------------
     * Export a PatchSpec to json.
     *---------------------------------------------------------------------------------*/
    std::string to_json();

    /*----------------------------------------------------------------------------------
     * Store a PatchSpec to the global PatchRegistry so that it can be
     * instantiated by name.
     *---------------------------------------------------------------------------------*/
    void store();

    /**----------------------------------------------------------------------------------
     * Print a representation to stdout
     *---------------------------------------------------------------------------------*/
    void print();

protected:
    friend class Patch;

    PatchNodeSpec output;
    std::map<int, PatchNodeSpec> nodespecs;

private:
    std::string name;

    int last_id = 0;
    void print(PatchNodeSpec *root, int depth);
};

template <class T>
class PatchSpecRefTemplate : public std::shared_ptr<T>
{
public:
    PatchSpecRefTemplate()
        : std::shared_ptr<T>(nullptr) {}
    PatchSpecRefTemplate(PatchSpec *ptr)
        : std::shared_ptr<T>(ptr) {}
};

typedef PatchSpecRefTemplate<PatchSpec> PatchSpecRef;

}
