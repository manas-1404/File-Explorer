#!/bin/bash

echo "RUNNING LISTING TEST ..."
./stupidos -s 500000 -f test.hd < input1

echo "RUNNING ADDING TEST ..."
./stupidos -s 10000 < input2

echo "RUNNING DELETING TEST ..."
./stupidos -s 10000 < input3
