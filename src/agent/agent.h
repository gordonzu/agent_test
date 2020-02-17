// gordon zuehlke 2/16/20

#ifndef AICPP_AGENT_H
#define AICPP_AGENT_H

#include "environment/environment_object.h"

class Agent : public EnvironmentObject { 
public:
    virtual ~Agent() {}
    virtual bool is_alive() = 0;
    virtual void set_alive(bool a) = 0;
};
#endif

//Agent::~Agent() {}


