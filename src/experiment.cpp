#include "experiment.h"

std::vector<int> couplingArray(int n) {
  std::vector<int> coupling;
  for (int i = 1; i <= n; i++) {
    coupling.push_back(i);
  }
  return coupling;
}

Actor* getAppropriateActor(Reward reward) {
  if (reward == LocalDpp) {
    LocalAgentDpp* agent = new LocalAgentDpp();
    return agent;
  } else if (reward == LocalD) {
    LocalAgent* agent = new LocalAgent();
    return agent;
  } else if (reward == Dpp) {
    GlobalAgentDpp* agent = new GlobalAgentDpp();
    return agent;
  } else if (reward == G) {
    Agent* agent = new Agent();
    return agent;
  } else if (reward == D) {
    GlobalAgent* agent = new GlobalAgent();
    return agent;
  } else {
    throw new std::exception();
  }
}

void addPois(std::vector<Actor*>& actors, int numberPois) {
  for (int i = 0; i < numberPois; i++) {
    POI* poi = new POI();
    poi->init(1, 0.1, 10.0, 1);
    actors.push_back(poi);
  }
}

void addAgents(std::vector<Actor*>& actors, Reward reward, int numberAgents) {
  for (int i = 0; i < numberAgents; i++) {
    actors.push_back(getAppropriateActor(reward));
  }
}

void setWorld(std::vector<Actor*>& actors, Reward reward, World* world) {
  if (reward != D && reward != Dpp) {
    return;
  }
  
  for (auto actor : actors) {
    if (actor->isAgent()) {
      GlobalAgent* gAgent = (GlobalAgent*) actor;
      gAgent->setWorld(world);
    }
  }
}

CCEAConfig createCCEAConfig(unsigned int numPools, unsigned int numNetworks, double percentWeights, double magMut, double percentChosen) {
  CCEAConfig config;
  config.numberPools = numPools;
  config.numberNetworks = numNetworks;
  config.percentOfWeightsToMutate = percentWeights;
  config.magnitudeOfMutation = magMut;
  config.percentageMaxScoreChosen = percentChosen;
  return config;
}

NetworkConfig createNetworkConfig(FANN::network_type_enum type, unsigned int numberLayers, unsigned int* layers, bool rWeights, double rMin, double rMax) {
  NetworkConfig config;
  config.netType = type;
  config.numLayers = numberLayers;
  config.layers = layers;
  config.randomWeights = rWeights;
  config.randomMin = rMin;
  config.randomMax = rMax;
  return config;
}

std::vector<double> statisticalRuns(CCEA ccea, SimNetEval simNetEval, int runs, World* world) {
  double average = 0;
  std::vector<double> scores;
  
  std::vector<FANN::neural_net*> bestTeam = ccea.getCurrentBestTeam();
  for (int i = 0; i < runs; i++) {
    simNetEval.evaluateNNs(bestTeam);
    double score = world->calculateG();
    average += score;
    scores.push_back(score);
  }

  average /= runs;

  double variance = 0;
  for (const auto s : scores) {
    variance += (average - s) * (average - s);
  }

  double std_dv = sqrt(variance / runs);

  std::vector<double> result;
  result.push_back(average);
  result.push_back(std_dv);
  return result;
}

void setPOICoupling(std::vector<Actor*>& actors, double value, double minRange, double maxRange, int agentsRequired) {
  for (auto actor : actors) {
    if (actor->isPOI()) {
      POI* poi = (POI*) actor;
      poi->init(value, minRange, maxRange, agentsRequired);
    }
  }
}

Reward stringToReward(std::string str) {
  if (str == "G") return G;
  if (str == "D") return D;
  if (str == "LocalD") return LocalD;
  if (str == "Dpp") return Dpp;
  if (str == "LocalDpp") return LocalDpp;
  else return G;
}
