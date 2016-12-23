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

LocalAgent::LocalAgent(Location loc, FANN_Wrapper* startingNet) {
  this->gApproximation = startingNet;
}

// Estimates global reward if agent had done one less step
double LocalAgent::determineReward(std::vector<Actor*>& actors, double g) {
  std::vector<float> state = this->createState(actors);
  state.push_back(0);
  state.push_back(0);
  
  std::vector<float> output = this->getApproximation()->run(state);
  double counterfactual = (double) (output[0]);
  return g - counterfactual;
}

void LocalAgent::receiveBroadcastG(double g, std::vector<Actor*>& actors) {
  std::vector<float> state = this->createState(actors);
  Location previousCommand = this->getLastCommand();
  state.push_back((float) (previousCommand.x));
  state.push_back((float) (previousCommand.y));

  std::vector<float> output = {(float) g};
  
  this->getApproximation()->train(state,output);
}

void LocalAgent::initNetwork() {
  unsigned int layers[3];
  layers[0] = 10;
  layers[1] = 10;
  layers[2] = 1;
  FANN::neural_net* net = new FANN::neural_net(FANN::LAYER, 3, layers);
  net->randomize_weights(-10,10);
  FANN_Wrapper* wrapper = new FANN_Wrapper(net);
  this->gApproximation = wrapper;
}

FANN_Wrapper* LocalAgent::getApproximation() {
  return this->gApproximation;
}
