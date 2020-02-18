// gordon zuehlke 2/16/20

#ifndef AICPP_ENVIRONMENT_OBJ_H
#define AICPP_ENVIRONMENT_OBJ_H

#include<typeinfo>
#include<stddef.h>
#include<iostream>

class EnvironmentObj {
public:
    virtual ~EnvironmentObj() = 0;
 
    virtual bool operator==(const EnvironmentObj& other) const {
        if (typeid(*this) != typeid(other))
            return false;

        return true;
    }    
};
#endif //AICPP_ENVIRONMENT_OBJECT_H

