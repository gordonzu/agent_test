// gordon zuehlke 2/11/20
// class representation of a 2D matrix
// TODO: 
// How many functions can be private? How many free functions? How many const? How many static?
// How many parameters can be const? How many for loops can be STL loops?
// Non-base classes are to be made final
// List all out parameters from functions... make wrapper objects containing a pointer to the value

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>                                       
#include "agent/mock_agent.h"
#include "util/xy_location.h"

using Map = std::vector<std::pair<XYLocation, std::vector<MockAgent>>>;

class XYEnvironment {
public:

    XYEnvironment(int w, int h) {
        if (w < 1 || h < 1)
            throw std::runtime_error("Invalid parameter values");

        width = w;
        height = h;

        for (int x = 1; x <= width; ++x) {
            for (int y = 1; y <= height; ++y) {
                agent_map.emplace_back(XYLocation{x,y}, std::vector<MockAgent>());
            }
        }
        binary_sort_map();
    }

    void binary_sort_map() {
        std::sort(get_map().begin(),
                  get_map().end(),
                  [](auto& left, auto& right) {
                      return left.first < right.first;
                  });  
    }

    size_t matrix_size() {
        return agent_map.size();
    }

    size_t inner_vector_size(const XYLocation& xy) {
        return has_xy(xy)->second.size();
    }

    Map::iterator has_xy(const XYLocation& loc) {
        itv = std::find_if(
                get_map().begin(),
                get_map().end(),
                [loc](std::pair<XYLocation, std::vector<MockAgent>>& mypair) {
                    return (mypair.first == loc);
                });
        return itv;
    }

    Map& get_map() {
        return agent_map;
    }

    void add_to(const MockAgent& obj, const XYLocation& xy) {
        check_object(obj);
        check_vector(xy).emplace_back(obj);
    }

    void check_object(const MockAgent& obj) {
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

    std::vector<MockAgent>& check_vector(const XYLocation& xy) {
        if (has_xy(xy) != get_map().end()) {
            return itv->second;
        }

        if(check_matrix(xy)) {
            agent_map.emplace_back(xy, std::vector<MockAgent>());
        } else {
            flag = true;
        }

        binary_sort_map();
        return has_xy(xy)->second;
    }

    bool check_matrix(const XYLocation& xy) {
        itv = std::prev(get_map().end());

        if (itv->first < xy) {
            flag = false;
            grow_matrix(xy);
        }
        return flag;
    }

    void grow_matrix(const XYLocation& xy) {
        unsigned new_width = 0;
        unsigned new_height = 0;

        if ((xy.getx() - itv->first.getx()) > 0)
            new_width = xy.getx();

        if (( xy.gety() - itv->first.gety()) > 0)
            new_height = xy.gety();

        if (new_width) 
            add_rows(new_width);
        
        if (new_height) 
            add_columns(new_height);
    }

    void add_rows(unsigned new_width) {
        // add new rows within existing columns 
        for (int i = (width + 1); i <= new_width; ++i) {
            for (int ii = 1; ii <= height; ++ii) {
                agent_map.emplace_back(XYLocation{i,ii}, std::vector<MockAgent>());
            }
        }
        width = new_width;
    }

    void add_columns(unsigned new_height) {
        // extend new columns to all rows
        for (int i = 1; i <= width; ++i) {
            for (int ii = (height + 1); ii <= new_height; ++ii) {
                agent_map.emplace_back(XYLocation{i,ii}, std::vector<MockAgent>());
            }
        }
        height = new_height;
    }

    void print_map() {
        for (const std::pair<XYLocation, std::vector<MockAgent>>& p : agent_map)
            std::cout << "Location: " << p.first << std::endl; 
    }

    unsigned get_width() {
        return width;
    }

    unsigned get_height() {
        return height;
    }

private:
    Map agent_map;
    Map::iterator itv;
    std::vector<MockAgent>::iterator its;
    std::vector<std::vector<MockAgent>> vector_cache;
    static unsigned width;
    static unsigned height;
    bool flag{true};
};
#endif

unsigned XYEnvironment::width = 0;
unsigned XYEnvironment::height = 0;







/*
    XYEnvironment() = delete;
    XYEnvironment(int w, int h);
    virtual ~XYEnvironment() = default;
    size_t matrix_size();
    Map::iterator has_xy(const XYLocation& loc);
    Map& get_map();
    size_t inner_vector_size(const XYLocation& xy);
    void add_agent(const MockAgent& obj, const XYLocation& xy);
    void check_object(const MockAgent& obj);
    std::vector<MockAgent>& check_vector(const XYLocation& xy);
    bool check_matrix(const XYLocation& xy);
    void binary_sort_map();
    void print_map();
    unsigned get_width();
    unsigned get_height();
    void grow_matrix(const XYLocation& xy);
    void add_rows(unsigned new_width);
    void add_columns(unsigned new_height);
*/

