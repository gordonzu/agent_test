// gordon zuehlke 2/17/20

#ifndef AICPP_ENVIRONMENT_H
#define AICPP_ENVIRONMENT_H

#include <vector>
#include <memory>
#include <iostream>
#include "environment_obj.h"
#include "environment_view.h"
#include "agent/agent.h"

using EnvPtr = std::shared_ptr<EnvironmentObj>;
using ViewPtr= std::shared_ptr<EnvironmentView>;
using EnvVec = std::vector<EnvPtr>;
using ViewVec = std::vector<ViewPtr>;

// change add functions into a function template? Or keep seperate functions and 
// move the algorithm into a function object passed to each add 

class Environment { 
public:
    void add_environment_object(EnvPtr eo) {
        if (std::find(objects.begin(), objects.end(), eo) == objects.end()) 
            objects.emplace_back(eo);
    }
    
    void add_agent(EnvPtr agent) {
        if (std::find(agents.begin(), agents.end(), agent) == agents.end()) 
            agents.emplace_back(agent);
    }

    void add_view(ViewPtr view) {
        if (std::find(views.begin(), views.end(), view) == views.end()) 
            views.emplace_back(view);  
    }

    size_t get_num_views() {
        return views.size();
    }

    size_t get_num_objects() {
        return objects.size();
    }

    size_t get_num_agents() {
        return agents.size();
    }

protected:
    ViewVec views;
    EnvVec objects;
    EnvVec agents;
};
#endif


