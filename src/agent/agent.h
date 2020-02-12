// gordon zuehlke 2/10/2020
// Agent.h
//

#ifndef AICPP_AGENT_H
#define AICPP_AGENT_H

#include <ostream>
#include "util/xy_location.h"
//#include "action.h"
//#include "percept.h"
//#include "agent_programs/agent_program.h"

class Agent {
public:
    Agent();
    virtual ~Agent();
    virtual bool is_wall() const;
    size_t hash_it();
    bool operator==(const Agent& x) const; 

protected:
    bool iswall{false};
    size_t hashval{0};

};
#endif //AICPP_AGENT_H

