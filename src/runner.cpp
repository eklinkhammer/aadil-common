#include "experiment.h"
#include "constants.h"

int main() {

  // Bootstrapping both policies and approximations

  Reward r = stringToReward(rString);
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
  Simulation sim(simConfig);

  // Initialize CCEA
  SimNetEval evaluator (&sim);
  NetworkConfig netConfig = createNetworkConfig(NET_TYPE, NUM_LAYERS, LAYERS, RANDOM_WEIGHTS, RANDOM_MIN, RANDOM_MAX);
  CCEAConfig cceaConfig = createCCEAConfig(NUMBER_POOLS, NUMBER_NETWORKS, PERCENT_TO_MUTATE, MAG_MUTATION, PERCENT_BEST_CHOSEN);
  CCEA ccea(netConfig, cceaConfig);

  // Configure experiment parameters
  std::vector<int> coupling = couplingArray(MAX_COUPLING);
  /*
  for (const auto i : coupling) {
    std::cout << i << std::endl;
  }
  exit(1);*/
  // Run experiment for various number of viewing agents required
  for (int i = 0; i < coupling.size(); i++) {
    setPOICoupling(actors, 1, 0.1, SIZE_WORLD*POI_RANGE_PERCENT_WORLD, coupling[i]);

    std::vector<double> scoresForCoupling;
    double rollingAverage = 0;
    double newTermWeight = 0.1;
    std::cout << "Running Gens..." << std::endl;
    for (int j = 0; j < GENS; j++) {
      ccea.runGeneration(&evaluator);
      double score = rWorld.calculateG();
      //      scoresForCoupling.push_back(score);

      if (j > 1) {
	rollingAverage = rollingAverage * (1 - newTermWeight) + score * newTermWeight;
      }
      if (DEBUG) {
	int gensToDisplay = (int) (VIEW_FREQUENCY * GENS);
	if (j % gensToDisplay == 0) {
	  std::cout << "World - Agents Required: " << i << " Generation: " << j << " Rolling Average Score: " << rollingAverage << std::endl;
	  rWorld.display();
	}
      }
    }

    /*
    LocalAgent* agent = (LocalAgent*) actors[0];
    FANN::neural_net* netA = agent->getApproximation()->getNeuralNet();
    FANN::neural_net* netP = agent->getPolicy()->getNeuralNet();

    std::string netAFilename = "approx" + std::to_string(i);
    std::string netPFilename = "policy" + std::to_string(i);

    //netA->save(netAFilename);
    //netP->save(netPFilename);
    */
  }

  return 0;
}
