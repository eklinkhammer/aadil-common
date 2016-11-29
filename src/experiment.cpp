#include "experiment.h"

// Experiment Parameters
const int NUM_AGENTS = 20;
const int NUM_POIS = 40;
const double SIZE_WORLD = 100.0;
const double POI_RANGE_PERCENT_WORLD = 0.25;
const int GENS = 1000;
const Reward r = LocalDpp;
const int SIM_TIMESTEPS = 50;
const int MAX_COUPLING = 8;
const int STAT_RUNS = 100;

// Network Config
const FANN::network_type_enum NET_TYPE = FANN::LAYER;
const unsigned int NUM_LAYERS = 3;
const unsigned int INPUT_LAYER = 8;
const unsigned int HIDDEN_LAYER = 9;
const unsigned int OUTPUT_LAYER = 2;
unsigned int LAYERS[NUM_LAYERS] = {INPUT_LAYER, HIDDEN_LAYER, OUTPUT_LAYER};
const bool RANDOM_WEIGHTS = true;
const double RANDOM_MIN = -10;
const double RANDOM_MAX = 10;

// CCEA Config
const unsigned int NUMBER_POOLS = (unsigned int) NUM_AGENTS;
const unsigned int NUMBER_NETWORKS = 10;
const double PERCENT_TO_MUTATE = 0.4;
const double MAG_MUTATION = 0.75;
const double PERCENT_BEST_CHOSEN = 0.9;


int main() {

  // Bootstrapping both policies and approximations
  
  // Initialize set of actors
  std::vector<Actor*> actors;
  addAgents(actors,r,NUM_AGENTS);
  addPois(actors, NUM_POIS);

  // Initialize World
  RoverDomain rWorld(actors, Location::createLoc(SIZE_WORLD, SIZE_WORLD));
  setWorld(actors,r,&rWorld);

  // Initialize Simulation
  SimulationConfig simConfig;
  simConfig.timesteps = SIM_TIMESTEPS;
  simConfig.actors = actors;
  simConfig.w = &rWorld;

  std::vector<int> coupling = couplingArray(MAX_COUPLING);
  
  Simulation sim(simConfig);
  SimNetEval evaluator (&sim);




  NetworkConfig netConfig = createNetworkConfig(NET_TYPE, NUM_LAYERS, LAYERS, RANDOM_WEIGHTS, RANDOM_MIN, RANDOM_MAX);
  CCEAConfig cceaConfig = createCCEAConfig(NUMBER_POOLS, NUMBER_NETWORKS, PERCENT_TO_MUTATE, MAG_MUTATION, PERCENT_BEST_CHOSEN);
  
  CCEA ccea(netConfig, cceaConfig);

  std::vector<std::vector<std::vector<double> > > gValues;
  for (int i = 0; i < coupling.size(); i++) {

    std::vector<std::vector<double> >scores;
    for (auto actor : actors) {
      if (actor->isPOI()) {
	POI* poi = (POI*) actor;
	poi->init(1, 0.1, SIZE_WORLD*POI_RANGE_PERCENT_WORLD, coupling[i]);
      }
    }
        
    for (int j = 0; j < GENS; j++) {
      ccea.runGeneration(&evaluator);
      //if (j % 100 == 0) {
      std::vector<double> score = statisticalRuns(ccea, evaluator, STAT_RUNS, &rWorld);
	scores.push_back(score);
	// }
    }

    gValues.push_back(scores);
  }

  std::cout << "Bootstrapping both. Coupling 1 -> 8 \n";
  for (const auto v : gValues) {
    std::cout << "Scores: \n";
    for (const auto score : v) {
      std::cout << "(" << score[0] << "," << score[1] << ") ";
    }
    std::cout << "\n";
  }
  /*
  // Just bootstrapping approximation
  actors.empty();
  addAgents(actors,r,NUM_AGENTS);
  addPois(actors, NUM_POIS);


  gValues.empty();
  for (int i = 0; i < coupling.size(); i++) {
    netConfig = createNetworkConfig(NET_TYPE, NUM_LAYERS, LAYERS, RANDOM_WEIGHTS, RANDOM_MIN, RANDOM_MAX);
    cceaConfig = createCCEAConfig(NUMBER_POOLS, NUMBER_NETWORKS, PERCENT_TO_MUTATE, MAG_MUTATION, PERCENT_BEST_CHOSEN);
    
    CCEA ccea1(netConfig, cceaConfig);
    std::vector<double> scores;
    for (auto actor : actors) {
      if (actor->isPOI()) {
	POI* poi = (POI*) actor;
	poi->init(1, 0.1, SIZE_WORLD*POI_RANGE_PERCENT_WORLD, coupling[i]);
      }
    }
        
    for (int j = 0; j < GENS; j++) {
      ccea1.runGeneration(&evaluator);
      if (j % 100 == 0) {
	double score = statisticalRuns(ccea, evaluator, STAT_RUNS, &rWorld);
	scores.push_back(score);
      }
    }

    gValues.push_back(scores);
  }

  std::cout << "Bootstrapping just approximation. Coupling 1 -> 8 \n";
  for (const auto v : gValues) {
    std::cout << "Scores: \n";
    for (const auto score : v) {
      std::cout << score << " ";
    }
    std::cout << "\n";
  }

  
  // Just bootstrapping policy


  netConfig = createNetworkConfig(NET_TYPE, NUM_LAYERS, LAYERS, RANDOM_WEIGHTS, RANDOM_MIN, RANDOM_MAX);
  cceaConfig = createCCEAConfig(NUMBER_POOLS, NUMBER_NETWORKS, PERCENT_TO_MUTATE, MAG_MUTATION, PERCENT_BEST_CHOSEN);
    
  CCEA ccea2(netConfig, cceaConfig);
    
  gValues.empty();
  for (int i = 0; i < coupling.size(); i++) {
    actors.empty();
    addAgents(actors,r,NUM_AGENTS);
    addPois(actors, NUM_POIS);
    std::vector<double> scores;
    for (auto actor : actors) {
      if (actor->isPOI()) {
	POI* poi = (POI*) actor;
	poi->init(1, 0.1, SIZE_WORLD*POI_RANGE_PERCENT_WORLD, coupling[i]);
      }
    }
        
    for (int j = 0; j < GENS; j++) {
      ccea2.runGeneration(&evaluator);
      if (j % 100 == 0) {
	double score = statisticalRuns(ccea, evaluator, STAT_RUNS, &rWorld);
	scores.push_back(score);
      }
    }

    gValues.push_back(scores);
  }

  std::cout << "Bootstrapping just approximation. Coupling 1 -> 8 \n";
  for (const auto v : gValues) {
    std::cout << "Scores: \n";
    for (const auto score : v) {
      std::cout << score << " ";
    }
    std::cout << "\n";
  }
  
  return 0;
  */
}

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
