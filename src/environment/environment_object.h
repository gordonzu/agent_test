// gordon zuehlke 2/16/20

#ifndef AICPP_ENVIRONMENT_OBJECT_H
#define AICPP_ENVIRONMENT_OBJECT_H

#include<typeinfo>
#include<stddef.h>
#include<iostream>

class EnvironmentObject {
public:
    virtual ~EnvironmentObject() = 0;
 
    virtual bool operator==(const EnvironmentObject& other) const {
        if (typeid(*this) != typeid(other))
            return false;

        return true;
    }    
};
#endif //AICPP_ENVIRONMENT_OBJECT_H

