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
#include <string>



enum Reward {G, D, LocalD, Dpp, LocalDpp};

/*
  Parses the inputed string to create a reward. The default reward is G.
  The expected strings are exactly the constructor names. This function used to 
    aid in parsing of yaml files so that enum can be used everywhere else.
 */
Reward stringToReward(std::string);

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

/*
  Returns the average and standard dev of x number of statistical runs
 */
std::vector<double> statisticalRuns(CCEA,SimNetEval,int,World*);

CCEAConfig createCCEAConfig(unsigned int, unsigned int, double, double, double);

NetworkConfig createNetworkConfig(FANN::network_type_enum, unsigned int, unsigned int*, bool, double, double);

void setPOICoupling(std::vector<Actor*>&,double,double,double,int);
#endif
