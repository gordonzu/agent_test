// gordonzu 2/11/20

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <algorithm>
#include "xy_environment.h"

int XYEnvironment::vsize = 0;

XYEnvironment::XYEnvironment(int w, int h) : width(w), height(h) {
    assert (width > 0);
    assert (height > 0);

    for (int x = 1; x <= w; ++x) {
        for (int y = 1; y <= h; ++y) {
            agent_map.emplace_back(XYLocation{x,y}, std::vector<Agent>());
        }
    }
}

size_t XYEnvironment::map_size() {
    return agent_map.size();
}

size_t XYEnvironment::inner_vector_size(const XYLocation& xy) {
    return has_xy(xy)->second.size();
}

Map::iterator XYEnvironment::has_xy(const XYLocation& loc) {
    itv = std::find_if(
            get_map().begin(),
            get_map().end(),
            [loc](std::pair<XYLocation, std::vector<Agent>>& mypair) {
                return (mypair.first == loc);
            });
    return itv;
}

Map& XYEnvironment::get_map() {
    return agent_map;
}

void XYEnvironment::add_agent(const Agent& obj, const XYLocation& xy) {
    check_object(obj);
    check_vector(xy).emplace_back(obj);
}

// Get the agent_map and iterate. For each pair, assign an agent vector iterator to each 
// agent vector. Iterate through, checking each agent for equality to the agent parameter 
// passed in to the function. If found, delete it.
void XYEnvironment::check_object(const Agent& obj) {
    for (auto& x : agent_map) {  
        if (its = x.second.begin(); its != x.second.end()) {
            if (*its == obj) {
                x.second.erase(its);
                break;
            }
            ++its;
        }
    }
}

// Check the agent map for the xy_location paramter passed in. If found, return the corresponding 
// agent vector. If not found, insert the xy_location and a new agent vector into the map. Call  
// the has_xy lookup function to return a reference to the agent vector of the just inserted pair 
// to the add_agent function, which will insert the new agent.  
std::vector<Agent>& XYEnvironment::check_vector(const XYLocation& xy) {
    if (has_xy(xy) != get_map().end()) {
        return itv->second;
    }
    agent_map.emplace_back(xy, std::vector<Agent>());
    return has_xy(xy)->second;
}





