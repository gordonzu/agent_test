// gordon zuehlke 2/17/20

#include <vector>
#include <memory>
#include <iostream>
#include "environment_object.h"
#include "environment_view.h"
#include "agent/agent.h"

using EnvPtr = std::shared_ptr<EnvironmentObject>;
using ViewPtr= std::shared_ptr<EnvironmentView>;
using EnvVec = std::vector<EnvPtr>;
using ViewVec = std::vector<ViewPtr>;

class Environment { 
public:
    void add_environment_object(EnvPtr eo);
    void add_agent(EnvPtr eo);
    void add_view(ViewPtr view);
    ViewVec& get_views();
    ObjectVec& get_objects();
    ObjectVec& get_agents();

protected:
    ViewVec views;
    EnvVec objects;
    EnvVec agents;
};
#endif


