#!/usr/bin/env bash

mkdir cmake
cd cmake
cmake ..
make
./models/runUnitTestsModels
./simulation/runUnitTestsSimulation
./ccea/runUnitTestsCCEA
