/*********************************************************************
*  localAgent.cpp
*
*   Local agent is an agent with a neural network that approximates G (value
*   that is broadcast by world).
*
*  Copyright (C) 2016 Eric Klinkhammer
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#include "localAgent.h"
#include <iostream>

LocalAgent::LocalAgent() : Agent() {
  this->initNetwork();
}

LocalAgent::LocalAgent(Location loc) : Agent(loc) {
  this->initNetwork();
}

LocalAgent::LocalAgent(Location loc, FANN::neural_net* startingNet) {
  this->gApproximation = startingNet;
}

// Estimates global reward if agent had done one less step
double LocalAgent::determineReward(std::vector<Actor*>& actors, double g) {
  std::vector<double> state = this->createState(actors);
  state.push_back(0);
  state.push_back(0);

  float input[10];
  for (int i = 0; i < 10; i++) {
    input[i] = (float) state[i];
  }
  
  fann_type* output = this->getApproximation()->run(input);
  double counterfactual = (double) ((float) output[0]);
  return g - counterfactual;
}

void LocalAgent::receiveBroadcastG(double g, std::vector<Actor*>& actors) {
  std::vector<double> state = this->createState(actors);
  Location previousCommand = this->getLastCommand();
  state.push_back(previousCommand.x);
  state.push_back(previousCommand.y);

  float input[10];
  for (int i = 0; i < 10; i++) {
    input[i] = (float) state[i];
  }

  float output[1];
  output[0] = (float) g;

  fann_type* inputF  = (fann_type*) input;
  fann_type* outputF = (fann_type*) output;

  this->getApproximation()->train(inputF,outputF);
}

void LocalAgent::initNetwork() {
  unsigned int layers[3];
  layers[0] = 10;
  layers[1] = 10;
  layers[2] = 1;
  this->gApproximation = new FANN::neural_net(FANN::LAYER, 3, layers);
  this->gApproximation->randomize_weights(-10,10);
}

FANN::neural_net* LocalAgent::getApproximation() {
  return this->gApproximation;
}
