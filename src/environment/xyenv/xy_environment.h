// gordon zuehlke 2/11/20
// XYEnvironment is a class representation of a 2-D matrix

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>

class XYEnvironment {
public:
    XYEnvironment() = delete;
    XYEnvironment(int w, int h);
    virtual ~XYEnvironment() = default;

private:
    unsigned width;
    unsigned height;
};
#endif

