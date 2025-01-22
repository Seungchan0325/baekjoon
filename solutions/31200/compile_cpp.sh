#!/bin/bash

problem=search
grader_name=stub

g++ -DEVAL -std=gnu++11 -O2 -pipe -static -s -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
