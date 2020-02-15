// gordon zuehlke 2/11/20
// class representation of a 2D matrix

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include "agent/agent.h"

using Map = std::vector<std::pair<XYLocation, std::vector<Agent>>>;

// TODO: 
// How many functions can be private? How many free functions? How many const? How many static?
// How many parameters can be const? How many for loops and be STL loops?
// Non-base classes are to be made final
// List all out parameters from functions... make wrapper objects containing a pointer to the value
//

class XYEnvironment {
public:
    XYEnvironment() = delete;
    XYEnvironment(int w, int h);
    virtual ~XYEnvironment() = default;
    size_t map_size();
    Map::iterator has_xy(const XYLocation& loc);
    Map& get_map();
    size_t inner_vector_size(const XYLocation& xy);
    void add_agent(const Agent& obj, const XYLocation& xy);
    void check_object(const Agent& obj);
    std::vector<Agent>& check_vector(const XYLocation& xy);
    bool check_matrix(const XYLocation& xy);
    void binary_sort_map();
    void print_map();

private:
    Map agent_map;
    Map::iterator itv;
    std::vector<Agent>::iterator its;
    std::vector<std::vector<Agent>> vector_cache;
    static unsigned width;
    static unsigned height;
    bool flag{true};
    //std::vector<std::vector<Agent>> a;
    //std::vector<std::vector<Agent>> aa;
};
#endif

