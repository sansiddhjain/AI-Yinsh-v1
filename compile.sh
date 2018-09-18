
#!/bin/bash

## Compile our two program files
g++ -std=c++14 -Ofast -march=native -o ./cmake-build-debug/yinsh_ai main.cpp Agent.cpp Board.cpp
