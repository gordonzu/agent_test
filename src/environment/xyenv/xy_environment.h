// gordon zuehlke 2/11/20
// class representation of a 2D matrix

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include "agent/agent.h"

class XYEnvironment {
public:
    XYEnvironment() = delete;
    XYEnvironment(int w, int h);
    virtual ~XYEnvironment() = default;
    size_t map_size();

private:
    std::vector<std::pair<XYLocation, std::vector<Agent>>> agent_map;
    std::vector<std::vector<Agent>> vector_cache;
    unsigned width;
    unsigned height;
    static const int vsize{10};
};
#endif

