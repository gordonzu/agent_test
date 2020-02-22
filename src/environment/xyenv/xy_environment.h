// gordon zuehlke 2/11/20
// class representation of a 2D matrix
// TODO: 
// How many functions can be private? How many free functions? How many const? 
// How many static?
// How many parameters can be const? How many for loops can be STL loops?
// Non-base classes are to be made final
// List all out parameters from functions... make wrapper objects containing a 
// pointer to the value

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>                        
#include "environment/environment.h"               
#include "util/xy_location.h"

class Wall;

using EnvPtr = std::shared_ptr<EnvironmentObj>;
using EnvVec = std::vector<EnvPtr>;
using Map = std::vector<std::pair<XYLocation, EnvVec>>;

class XYEnvironment : public Environment {
public:
    XYEnvironment(int w, int h) {
        if (w < 1 || h < 1)
            throw std::runtime_error("Invalid parameter values");

        width = w;
        height = h;

        for (int x = 1; x <= width; ++x) {
            for (int y = 1; y <= height; ++y) {
                agent_map.emplace_back(
                    XYLocation{x,y}, EnvVec());
            }
        }
        binary_sort_map();
    }

    XYLocation& get_location(const EnvPtr obj) {
        for (auto& x : get_map()) {
            if (std::find(x.second.begin(), 
                          x.second.end(), obj) 
                          != x.second.end()) { 
                          return x.first;
            }
        }
        return xyNull;
    }

    void add_to(const EnvPtr obj, const XYLocation& xy) {
        check_object(obj);
        check_map_for_location(xy).emplace_back(obj);
        if (!obj->is_wall()) 
            add_agent(obj);
        add_environment_object(obj);
    }

    size_t objects_at_location(const XYLocation& xy) {
        return has_xy(xy)->second.size();
    }

    size_t matrix_size() {
        return agent_map.size();
    }

    void move_to_absolute_location(const EnvPtr obj, const XYLocation& xy) {
        add_to(obj, xy);
    }

    void move_object(const EnvPtr obj, const XYLocation::Direction& dir) {
        XYLocation tmp = get_location(obj);
        if (tmp != xyNull) {
            tmp = tmp.location_at(dir);
            if (!(is_blocked(tmp))) {
                add_to(obj, tmp);
            }
        }
    }

    bool blocked(const XYLocation& xy) {
        return is_blocked(xy);
    }

    EnvVec& get_objects_near(const EnvPtr obj, unsigned rad) {
        nearObjs.clear();
        auto xy = get_location(obj);

        for (auto& v : get_map()) {
            if( in_radius(rad, xy, v.first)) {
                nearObjs.insert(nearObjs.end(), 
                                v.second.begin(), 
                                v.second.end());
            }
        }

        auto it = std::find(nearObjs.begin(), nearObjs.end(), obj);
        if (it != nearObjs.end()) nearObjs.erase(it);
        return nearObjs;
    }

    void make_perimeter(int x) {
        EnvVec walls;
        std::vector<XYLocation> locations;

        for (int i = 1; i <=x; ++i) {
            walls.emplace_back(std::make_unique<Wall>());
            locations.emplace_back(XYLocation{1,i});
            walls.emplace_back(std::make_unique<Wall>());
            locations.emplace_back(XYLocation{i,1});
        }

        for (int i = 1; i <=x; ++i) {
            walls.emplace_back(std::make_unique<Wall>());
            locations.emplace_back(XYLocation{i,x});
            walls.emplace_back(std::make_unique<Wall>());
            locations.emplace_back(XYLocation{x,i});
        }

        int i = 0;
        for (auto& w : walls) {
            add_to(walls[i], locations[i]);
            ++i;
        } 
    }

private:
    void binary_sort_map() {
        std::sort(get_map().begin(),
                  get_map().end(),
                  [](auto& left, auto& right) {
                      return left.first < right.first;
                  });  
    }

    bool is_blocked(const XYLocation& xy) {
        for (auto& eo : check_map_for_location(xy)) {
            if (eo->is_wall()) 
                return true;
        }
        return false;
    }

    bool in_radius(unsigned rad, const XYLocation& a, const XYLocation& b) {
        int xdiff = a.getx() - b.getx();
        int ydiff = a.gety() - b.gety();
        return std::sqrt((xdiff * xdiff) + (ydiff * ydiff)) <= rad;
    }

    Map::iterator has_xy(const XYLocation& loc) {
        itv = std::find_if(
                get_map().begin(),
                get_map().end(),
                [loc](std::pair<XYLocation, EnvVec>& mypair) {
                    return (mypair.first == loc);
                });
        return itv;
    }

    Map& get_map() {
        return agent_map;
    }

    void check_object(const EnvPtr obj) {
        for (auto& x : agent_map) {  
            if (its = x.second.begin(); its != x.second.end()) {
                if (**its == *obj) {
                    x.second.erase(its);
                    break;
                }
                ++its;
            }
        }
    }

    EnvVec& check_map_for_location(const XYLocation& xy) {
        if (has_xy(xy) != get_map().end()) {
            return itv->second;
        }

        if(check_matrix_dimensions(xy)) {
            agent_map.emplace_back(xy, EnvVec());
        } else {
            flag = true;
        }

        binary_sort_map();
        return has_xy(xy)->second;
    }

    bool check_matrix_dimensions(const XYLocation& xy) {
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
                agent_map.emplace_back(XYLocation{i,ii}, EnvVec());
            }
        }
        width = new_width;
    }

    void add_columns(unsigned new_height) {
        // extend new columns to all rows
        for (int i = 1; i <= width; ++i) {
            for (int ii = (height + 1); ii <= new_height; ++ii) {
                agent_map.emplace_back(XYLocation{i,ii}, EnvVec());
            }
        }
        height = new_height;
    }

    void print_map_locations() {
        for (const std::pair<XYLocation, EnvVec>& p : agent_map)
            std::cout << "Location: " << p.first << std::endl; 
    }

    unsigned get_width() {
        return width;
    }

    unsigned get_height() {
        return height;
    }

    Map agent_map;
    Map::iterator itv;
    EnvVec::iterator its;
    EnvVec nearObjs;
    unsigned width{0};
    unsigned height{0}; 
    XYLocation xyNull{0,0};
    bool flag{true};
};
#endif

