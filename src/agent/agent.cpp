// gordon zuehlke 2/12/20

#include "agent.h"
//#include "environment/environment.h"

Agent::Agent() { 
    hashval = hash_it();
}

Agent::~Agent() {}

bool Agent::is_wall() const {
    return iswall;
}

bool Agent::operator==(const Agent& x) const {
    return hashval == x.hashval; 
}

size_t Agent::hash_it() {
    hashval = reinterpret_cast<uint64_t>(this);
    return hashval;
}




