#!/bin/bash
rm -rf out
mkdir out
g++ suomic.cc -o transpiler
mv transpiler out
./out/transpiler $1
