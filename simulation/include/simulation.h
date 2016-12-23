/*********************************************************************
* simulation.h
*
*  Simulations are containers for policies, and the machinery that evaluates
*    them. They are used by Net Evaluators to track some state across 
*    runs.
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

#ifndef _SIM_H
#define _SIM_H

#include "ccea.h"
#include "netEvaluator.h"
#include "world.h"
#include "poi.h"
#include "agent.h"
#include <random>
#include "roverDomain.h"
#include "wrapper.h"

class SimulationConfig {
 public:
  int timesteps;
  std::vector<Actor*> actors;
  World* w;
};

class Simulation {
 public:
  Simulation(SimulationConfig);

  /*
    Maps each neural net policy to the appropriate actors. This is the initialization step
      for a simulation. The separation of this from the intial setting of the actor is what
      allows for actor state across simulations (to, for example, have each actor maitain
      its own approximation of D for local D)

    Args:
      List of neural network policies. It is assumed they are assigned to agents.
   */
  void assignPolicies(std::vector<FANN::neural_net*>);;

  /*
    Runs the simulation for a certain number of timesteps. A run of a simulation involves
      randomizing the starting locations of all actors and then timesteping through
      the world.
   */
  void run();

  /*
    Get the agent defined rewards for the current state of the world (typically the end state).
    These are the values that will typically be used by the evaluator to return to the CCEA.
   */
  std::vector<double> getRewards();

  /*
    Returns the list of G values that were run with this simulation. This is one of the main 
      purposes of having a separate simulation and net evaluator, to carry state (this is
      the data for graphing training speed / efficacy)
   */
  std::vector<double> getG();

  /*
    Returns the actors that are implementing the policies in the simulation. As with G, this means
      the actors can preserve all state (potentially even their previous network) across runs.
   */
  std::vector<Actor*> getActors();

  void init(SimulationConfig);
 private:
  World* world;
  int timesteps;
  std::vector<Actor*> actors;
  std::vector<double> gValues;
  
};


#endif
