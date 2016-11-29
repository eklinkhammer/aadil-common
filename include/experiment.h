#ifndef _EXP_H
#define _EXP_H

#include "poi.h"
#include "roverDomain.h"
#include "localAgentDpp.h"
#include "globalAgent.h"
#include "globalAgentDpp.h"

#include "simulation.h"
#include "simNetEval.h"

#include "ccea.h"

#include <vector>

enum Reward {G, D, LocalD, Dpp, LocalDpp};

Actor* getAppropriateActor(Reward);

std::vector<int> couplingArray(int);

/*
  Adds some number of default POIs to the list of actors.
 */
void addPois(std::vector<Actor*>&,int);

/*
  Adds some number of the appropriate agent to the list of actors.
 */
void addAgents(std::vector<Actor*>&,Reward,int);

/*
  For the agents that use global information in their own calculations of the 
    reward, sets the world for those agents.
  Note that this is a two step process because the world has a list of actors, which 
    is created first. Then, the actors (optionally) learn about the world.
 */
void setWorld(std::vector<Actor*>&,Reward,World*);

double statisticalRuns(CCEA,SimNetEval,int,World*);

CCEAConfig createCCEAConfig(unsigned int, unsigned int, double, double, double);

NetworkConfig createNetworkConfig(FANN::network_type_enum, unsigned int, unsigned int*, bool, double, double);

#endif
