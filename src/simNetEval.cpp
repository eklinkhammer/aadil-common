/*********************************************************************
*  simNetEval.cpp
*
*  The most important class in the library. This is what enables CCEA
*    to use the various simulators to actually train the policies.
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

#include "SimNetEval.h"

SimNetEval::SimNetEval(Simulation simulator) {
  this->sim = &simulator;
}

std::vector<double> SimNetEval::evaluateNNs(std::vector<FANN::neural_net*>& nets) {
  this->sim->assignPolicies(nets);
  this->sim->run();
  return this->sim->getRewards();
}
