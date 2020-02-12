#!/bin/bash

rm -rf build/MyProject_run &&
rm -rf build/tests/unit_tests/unit_tests_run 
cd build && 
cmake .. && 
make && 
./tests/unit_tests/unit_tests_run

