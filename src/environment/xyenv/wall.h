// gordon zuehlke

#ifndef AICPP_WALL_H
#define AICPP_WALL_H

#include "environment/environment_obj.h"

class Wall : public EnvironmentObj {
public:
    Wall() { 
        hashval = hash_it();
    }

    virtual ~Wall() {}

    bool operator==(const EnvironmentObj& other) const {
        if (!EnvironmentObj::operator==(other))
            return false;

        auto p = dynamic_cast<const Wall*>(&other);
        if (!p) return false;

        return hashval == p->hashval;
    }

    size_t hash_it() {
        hashval = reinterpret_cast<uint64_t>(this);
        return hashval;
    }

    bool is_wall() const {
        return iswall;
    }

private:
    bool iswall{true};
    size_t hashval{0};
};
#endif 

