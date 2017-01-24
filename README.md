# aadil-common
Eric Klinkhammer's common code for use in Autonomous Agents and Distributed Intelligence Lab.

Dependencies: 

FANN (Fast Artifical Neural Network) library installed and on path. Can find here: http://leenissen.dk/fann/wp/
yaml-cpp: Clone and install from https://github.com/jbeder/yaml-cpp

For documentation on use, please read comments in include files. Docs to come soon.

## Installation Instructions (As executable)
1) Clone library
2) CMake (mkdir cmake && cd cmake && cmake .. && make)
3) Run Project (./execProject)

## ccea
Cooperative Coevolutionary Algorithm
Status - Tests required (for XOR most likely)

## Models
Rover domain with Actor, POI, and Agent working. For specific agent reward structures, use GlobalAgent, LocalAgent, LocalAgentDpp, and GlobalAgentDpp. (GlobalAgent calculate D using global information, local agent calculates D with an approximation of the global reward function).

## Simulation
Continuous world and simulation complete.

## fann-cpp-vector
Wrapper for FANN::neural_net that works with std::vector instead of fann_types. Copies input and output out of buffer that neural net uses.
