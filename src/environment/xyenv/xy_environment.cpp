// gordonzu 2/11/20

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <algorithm>
#include "xy_environment.h"

XYEnvironment::XYEnvironment(int w, int h) : width(w), height(h) {
    assert (width > 0);
    assert (height > 0);
}


