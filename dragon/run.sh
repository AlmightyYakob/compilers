#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
fi

./mypc < $1;
make assemble;
./COMPILED
