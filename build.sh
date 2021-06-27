#!/bin/sh
mkdir -p bin
gcc -g -o bin/csub csub.c mpc/mpc.c -Impc/
gcc -g -o bin/ya ya.c mpc/mpc.c -Impc/
