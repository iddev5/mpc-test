#!/bin/sh
mkdir -p bin
gcc -g -o bin/csub csub.c mpc/mpc.c -Impc/
