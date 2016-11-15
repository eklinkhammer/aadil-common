/*********************************************************************
*  localAgentDpp.cpp
*
*   Local agent is an agent with a neural network that approximates G (value
*   that is broadcast by world) to calculate D++.
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

#include "localAgentDpp.h"
#include <iostream>

LocalAgentDpp::LocalAgentDpp() : LocalAgent() {
  //this->initNetwork(); // needed?
}

LocalAgentDpp::LocalAgentDpp(Location loc) : LocalAgent(loc) {
  //this->initNetwork();
}

LocalAgentDpp::LocalAgentDpp(Location loc, FANN::neural_net* startingNet) : LocalAgent (loc, startingNet) {
  //this->gApproximation = startingNet;
}

// Estimates global reward if agent had done one less step
double LocalAgentDpp::determineReward(std::vector<Actor*>& actors, double G) {
  double newDpp = 0;
  Location loc = this->getLocation();
  Location previousCommand = this->getLastCommand();
  std::vector<double> state = this->createState(actors);
  state.push_back(0);
  state.push_back(0);

  float input[10];
  for (int i = 0; i < 10; i++) {
    input[i] = (float) state[i];
  }
  
  fann_type* output = this->getApproximation()->run(input);
  double D = (double) ((float) output[0]);

  if (G - D > 0) {
    return G - D;
  }
  std::vector<Actor*> actorCopy;
  for (const auto actor : actors) {
    actorCopy.push_back(actor);
  }
  state = this->createState(actorCopy);
  state.push_back(previousCommand.x);
  state.push_back(previousCommand.y);
  for (int i = 0; i < 10; i++) {
    input[i] = (float) state[i];
  }

  output = this->getApproximation()->run(input);
  double counter = (double) ((float) output[0]);

  double Dpp = counter - G;
  if (Dpp > 0) {
    return Dpp;
  }
  


  // TODO parametarize this value
  for (int i = 1; i < 10; i++) {
    Agent a (Location::createLoc(loc.x + 0.05, loc.y + 0.05));
    actorCopy.push_back(&a);
    state = this->createState(actorCopy);
    state.push_back(previousCommand.x);
    state.push_back(previousCommand.y);
    for (int i = 0; i < 10; i++) {
      input[i] = (float) state[i];
    }

    output = this->getApproximation()->run(input);
    counter = (double) ((float) output[0]);
    newDpp = (counter - G) / i;
    if (newDpp > Dpp) {
      return newDpp;
    } else {
      Dpp = newDpp;
    }
  }

  return newDpp;
}
