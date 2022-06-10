@echo off
g++ main.cpp Stack.hpp Formula.h Formula.cpp Logic.h Logic.cpp QM.h QM.cpp -o test.exe
del *.gch
echo "task finished!"
test.exe