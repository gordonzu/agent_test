#!/bin/bash

clear
rm -rf build/src/agent_test_run &&
rm -rf build/tests/unit_tests/unit_tests_run 
cd build && 
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" && 
make all && 
./tests/unit_tests/unit_tests_run
#valgrind --tool=memcheck --leak-check=yes ./tests/unit_tests/unit_tests_run
#valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all ./tests/unit_tests/unit_tests_run
