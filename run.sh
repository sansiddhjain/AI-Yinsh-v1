#!/bin/bash

## This is to run the first program main.cpp

if [ -e "./build/yinsh_ai" ]; then
    ./build/yinsh_ai $1
else
    echo "First run compile.sh to compile the code"
fi
