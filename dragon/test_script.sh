#!/bin/bash
TEST_FILES=$(pwd)/example_files/Semantic/*.p

make clean && make;
for f in $TEST_FILES; do
    echo "###### $f"
    head -1 $f
    ./mypc < $f
    read -p "###### Press enter for next test file"
done
