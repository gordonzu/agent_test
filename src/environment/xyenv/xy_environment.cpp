// gordon zuehlke 2/12/20

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <algorithm>
#include "xy_environment.h"

unsigned XYEnvironment::width = 0;
unsigned XYEnvironment::height = 0;

XYEnvironment::XYEnvironment(int w, int h) {
    if (w < 1 || h < 1)
        throw std::runtime_error("Invalid parameter values");

    width = w;
    height = h;

    for (int x = 1; x <= width; ++x) {
        for (int y = 1; y <= height; ++y) {
            agent_map.emplace_back(XYLocation{x,y}, std::vector<Agent>());
        }
    }
    binary_sort_map();
}

void XYEnvironment::binary_sort_map() {
    std::sort(get_map().begin(),
              get_map().end(),
              [](auto& left, auto& right) {
                  return left.first < right.first;
              });  
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

std::vector<Agent>& XYEnvironment::check_vector(const XYLocation& xy) {
    if (has_xy(xy) != get_map().end()) {
        return itv->second;
    }

    if(check_matrix(xy)) {
        agent_map.emplace_back(xy, std::vector<Agent>());
    } else {
        flag = true;
    }

    binary_sort_map();
    return has_xy(xy)->second;
}

bool XYEnvironment::check_matrix(const XYLocation& xy) {
    itv = std::prev(get_map().end());

    if (!(xy < itv->first)) {
        flag = false;
        for (int i = width + 1; i <= xy.getx(); ++i) {
            for (int ii = 1; ii <= xy.gety(); ++ii) {
                agent_map.emplace_back(XYLocation{i,ii}, std::vector<Agent>());
            }
        }        

        for (int i = 1; i <= width; ++i) {
            for (int ii = (height + 1); ii <= xy.gety(); ++ii) {
                agent_map.emplace_back(XYLocation{i,ii}, std::vector<Agent>());
            }
        }
        width += xy.getx();
        height += xy.gety();
    }
    return flag;
}

void XYEnvironment::print_map() {
    for (const std::pair<XYLocation, std::vector<Agent>>& p : agent_map)
        std::cout << "Location: " << p.first << std::endl; 
}


    






















    /*itv = std::prev(get_map().end());
    std::cout << "XY location is: " << itv->first << std::endl;
    if (!(xy < itv->first)) std::cout << "xy is not less than the last entry." << std::endl;
    
    XYLocation loc2{5,14};
    XYLocation loc3{6,1};
    XYLocation loc4{10,12};

    if ((loc2 < loc3)) std::cout << "It's less!!!" << std::endl;
    if ((loc2 < loc4)) std::cout << "It's less!!!" << std::endl;
    */



// Get the agent_map and iterate. For each pair, assign an iterator to each 
// agent vector. Iterate through, checking each agent for equality to the agent parameter 
// passed in to the function. If found, delete.

// Check the agent map for the xy_location passed in. If found, return the corresponding 
// agent vector. If not found, insert the xy_location and a new agent vector into the map. Call  
// the has_xy lookup function to get a reference to the agent vector of the just inserted pair and 
// return it to the add_agent function, which will insert the new agent.  























