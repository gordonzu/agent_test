// gordon zuehlke 2/10/2020

#ifndef AICPP_MOCKAGENT_H
#define AICPP_MOCKAGENT_H

#include <ostream>
#include "agent.h"
#include "util/xy_location.h"
//#include "action.h"
//#include "percept.h"
//#include "agent_programs/agent_program.h"

class MockAgent : public Agent {
public:

    MockAgent() { 
        hashval = hash_it();
    }

    virtual ~MockAgent() {}

    bool is_wall() const {
        return iswall;
    }

    bool operator==(const EnvironmentObj& other) const {
        if (!EnvironmentObj::operator==(other))
            return false;

        auto p = dynamic_cast<const MockAgent*>(&other);
        if (!p) return false;

        return hashval == p->hashval;
    }

    size_t hash_it() {
        hashval = reinterpret_cast<uint64_t>(this);
        return hashval;
    }

    bool is_alive() {
        return alive;
    }

    void set_alive(bool a) {
        alive = a;
    }

protected:
    bool alive;
    bool iswall{false};
    size_t hashval{0};

};
#endif //AICPP_MOCKAGENT_H

