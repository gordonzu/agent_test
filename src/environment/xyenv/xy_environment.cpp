// gordonzu 2/11/20

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <algorithm>
#include "xy_environment.h"

XYEnvironment::XYEnvironment(int w, int h) : width(w), height(h) {
    assert (width > 0);
    assert (height > 0);
    vector_cache.resize(vsize);

    for (int x = 1; x <= w; ++x) {
        for (int y = 1; y <= h; ++y) {
            agent_map.emplace_back(XYLocation{x,y}, std::vector<Agent>());
        }
    }
}

size_t XYEnvironment::map_size() {
    return agent_map.size();
}


