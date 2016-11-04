/*********************************************************************
*  ccea.h
*
*  CCEA provides an API for a Cooperative Coevolutionary Algorithm based on
*    the FANN neural network library.
*
*  Copyright (C) 2016 Eric Klinkhammer and Connor Yates
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

#include "ccea.h"


NetworkConfig getDefaultNetworkConfig() {
  NetworkConfig defaultNC;
  defaultNC.netType = FANN::LAYER;
  defaultNC.numLayers = 3;
  defaultNC.layers = new unsigned int[3];
  defaultNC.layers[0] = 8;
  defaultNC.layers[1] = 10;
  defaultNC.layers[2] = 2;
  defaultNC.randomWeights = true;
  defaultNC.randomMin = -10;
  defaultNC.randomMax = 10;
  return defaultNC;
}

CCEAConfig getDefaultCCEAConfig() {
  CCEAConfig defaultCC;
  defaultCC.numberPools = 5;
  defaultCC.numberNetworks = 11;
  defaultCC.percentOfWeightsToMutate = 0.1;
  defaultCC.magnitudeOfMutation = 0.5;
  defaultCC.percentageMaxScoreChosen = 0.9;
  return defaultCC;
}

void testNetEval(std::vector<FANN::neural_net*> vec, std::vector<double> results) {
  results[0] = 4.2;
}

/*** Constructors ***/
CCEA::CCEA () {
  init(getDefaultNetworkConfig(), getDefaultCCEAConfig());
}

CCEA::CCEA (int pools, int networks) {
  CCEAConfig ccConfig = getDefaultCCEAConfig();
  ccConfig.numberPools = pools;
  ccConfig.numberNetworks = networks;
  init(getDefaultNetworkConfig(), ccConfig);
}

CCEA::CCEA (int pools, int networks, NetworkConfig config) {
  CCEAConfig ccConfig = getDefaultCCEAConfig();
  ccConfig.numberPools = pools;
  ccConfig.numberNetworks = networks;
  init(config, ccConfig);
}

CCEA::CCEA (std::vector<std::vector<FANN::neural_net*> > networks) {
  CCEAConfig ccConfig = getDefaultCCEAConfig();
  ccConfig.numberPools = networks.size();
  ccConfig.numberNetworks = networks[0].size();

  init(getDefaultNetworkConfig(), ccConfig, networks);
}

CCEA::CCEA (NetworkConfig netConfig, CCEAConfig ccConfig) {
  init(netConfig, ccConfig);
}

CCEA::CCEA (NetworkConfig netConfig, CCEAConfig ccConfig, std::vector<std::vector<FANN::neural_net*> > networks) {
  init(netConfig, ccConfig, networks);
}


void CCEA::runGeneration(void(*evalNet)(std::vector<FANN::neural_net*>&, std::vector<double>&)) {

  for (auto& i: this->population) {
    createSuccessors(i);
    std::random_shuffle(i.begin(), i.end());
  }

  std::vector<std::vector<double> > allScores;
  
  for (int teamCount = 0; teamCount < this->cceaConfig.numberNetworks * 2; teamCount++) {
    std::vector<FANN::neural_net*> team;
    std::vector<double> teamScore;
    for (int creatingTeam = 0; creatingTeam < this->cceaConfig.numberPools; creatingTeam++) {
      team.push_back(this->population[creatingTeam][teamCount]);
    }

    evalNet(team, teamScore);

    if (team.size() != teamScore.size()) {
      std::cout << "Evaluation method must provide score for each team member.\n";
      exit(0);
    }
    for (int teamWideScore = 0; teamWideScore < teamScore.size(); teamWideScore++) {
      if (teamWideScore >= allScores.size()) {
	std::vector<double> newV;
	allScores.push_back(newV);
      }
      allScores[teamWideScore].push_back(teamScore[teamWideScore]);
    }
  }

  for (int pools = 0; pools < this->cceaConfig.numberPools; pools++) {

    this->population[pools] = cullTheWeak(this->population[pools], allScores[pools]);
  }
}

std::vector<std::vector<FANN::neural_net*> > CCEA::getPopulation() {
  return this->population;
}


/** Private Methods **/
void CCEA::init(NetworkConfig netConfig, CCEAConfig cceaConfig) {

  std::vector<std::vector<FANN::neural_net*> > population = initPopulation(cceaConfig.numberPools, cceaConfig.numberNetworks, netConfig);
  init(netConfig, cceaConfig, population);
}

void CCEA::init(NetworkConfig netConfig, CCEAConfig ccConfig, std::vector<std::vector<FANN::neural_net*> > nets) {
  this->population = nets;
  this->networkConfig = netConfig;
  this->cceaConfig = ccConfig;
}

std::vector<std::vector<FANN::neural_net*> > CCEA::initPopulation(int pools, int networks, NetworkConfig netConfig) {
  std::vector<std::vector<FANN::neural_net*> > population;
  // Create neural networks
  for (int pop = 0; pop < pools; pop++) {
    std::vector<FANN::neural_net*> nets;
    for (int pool = 0; pool < networks; pool++) {
      FANN::neural_net* net = new FANN::neural_net(netConfig.netType, netConfig.numLayers, netConfig.layers);

      if (netConfig.randomWeights) {
	net->randomize_weights(netConfig.randomMin, netConfig.randomMax);
      }
      nets.push_back(net);
    }
    population.push_back(nets);
  }
  return population;
}

FANN::neural_net* CCEA::mutate(FANN::neural_net* net) {
  int totalWeights = net->get_total_connections();
  int numberMutations = this->cceaConfig.percentOfWeightsToMutate * totalWeights;
  
  FANN::neural_net* newNet = new FANN::neural_net(*net);
  FANN::connection connections[totalWeights];
  net->get_connection_array(connections);
  
  for (int mutationCount = 0; mutationCount < numberMutations; mutationCount++) {
    int index = rand() % totalWeights;
    fann_type current = connections[index].weight;
    
    double randomFactor = (double) rand() / (RAND_MAX);
    int sign = rand() % 2 ? 1 : -1;
    double val = sign * randomFactor * this->cceaConfig.magnitudeOfMutation;
    
    connections[index].weight += (fann_type)val * current;
  }
  
  newNet->set_weight_array(connections, totalWeights);
  
  return newNet;
}
  
void CCEA::createSuccessors(std::vector<FANN::neural_net*>& pool) {
  for (const auto net : pool)
    pool.push_back(mutate(net));
}

std::vector<FANN::neural_net*> CCEA::cullTheWeak(std::vector<FANN::neural_net*>& networks, std::vector<double>& scores) {
  int numToSelect = networks.size() / 2;
  std::vector<FANN::neural_net*> survivors;
  for (int i = 0; i < numToSelect; i++) {
    double r = (double)rand() / RAND_MAX;
    if (r > this->cceaConfig.percentageMaxScoreChosen) {
      survivors.push_back(selectRandom(networks, scores));
    } else {
      survivors.push_back(selectBest(networks, scores));
    }
  }
  
  return survivors;
}

FANN::neural_net* CCEA::selectBest(std::vector<FANN::neural_net*>& nets, std::vector<double>& scores) {
  double currentMax = scores[0];
  int maxIndex = 0;
  for (int i = 0; i < nets.size(); i++) {
    if (scores[i] > currentMax) {
      currentMax = scores[i];
      maxIndex = i;
    }
  }
  
  FANN::neural_net* chosen = nets[maxIndex];
  nets.erase(nets.begin() + maxIndex);
  scores.erase(scores.begin() + maxIndex);
  return chosen;
}

FANN::neural_net* CCEA::selectRandom(std::vector<FANN::neural_net*>& nets, std::vector<double>& scores) {
  int randIndex = rand() % nets.size();
  
  FANN::neural_net* chosen = nets[randIndex];
  nets.erase(nets.begin() + randIndex);
  scores.erase(scores.begin() + randIndex);
  return chosen;
}
