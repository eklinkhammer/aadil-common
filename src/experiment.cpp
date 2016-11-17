#include "experiment.h"

const int NUM_AGENTS = 4;
const int NUM_POIS = 14;
const double SIZE_WORLD = 30.0;
const int POOL_SIZE = 10;
const int GENS = 30;

int main() {
  // Initialize set of actors
  std::vector<Actor*> actors;
  
  
  for (int i = 0; i < NUM_AGENTS; i++) {
    //GlobalAgentDpp* x = new GlobalAgentDpp(); // D++
    LocalAgentDpp* x = new LocalAgentDpp(); // Local D++
    //GlobalAgent* x = new GlobalAgent(); // D
    //Agent* x = new Agent(); // G
    actors.push_back(x);
  }

  for (int i = 0; i < NUM_POIS; i++) {
    POI* poi = new POI();
    poi->init(1, 0.1, 4.0, 5);
    actors.push_back(poi);
  }

    // Initialize World
  RoverDomain rWorld(actors, Location::createLoc(SIZE_WORLD, SIZE_WORLD));

  int s = 0;
  if (s == 1) {
    for (auto actor : actors) {
      if (actor->isAgent()) {
	GlobalAgentDpp* gAgent = (GlobalAgentDpp*) actor;
	gAgent->setWorld(&rWorld);
      }
    }
  }
  
  // Initialize Simulation
  SimulationConfig simConfig;
  simConfig.timesteps = 50;
  simConfig.actors = actors;
  simConfig.w = &rWorld;

  std::vector<int> coupling = couplingArray(8);
  
  Simulation sim(simConfig);
  SimNetEval evaluator (&sim);
  CCEA ccea(NUM_AGENTS, POOL_SIZE);

  for (int i = 0; i < coupling.size(); i++) {
    for (auto actor : actors) {
      if (actor->isPOI()) {
	POI* poi = (POI*) actor;
	poi->init(1, 0.1, 4.0, coupling[i]);
      }
    }
        
    for (int j = 0; j < GENS; j++) {
      ccea.runGeneration(&evaluator);
      if (j % 10 == 0) {
	std::cout << "Coupling of: " << coupling[i] << " Generation: " << j << "\n";
      }
      std::cout << rWorld.calculateG() << "\n";
    }
    
  }
  // Simulation sim(simConfig);
  
  // Initialize Network Evaluator
  //SimNetEval evaluator (&sim);

  
  // Intialize CCEA
  // CCEA can be initialized with all parameters needed for network or CCEA configuration
  // Additionally, can be constructed from a base population of neural networks.
  // Note - these policies are separate from the actor's state, so there are two ways to
  // carry policy information between trials - one by saving the networks for a new CCEA and
  // also to reuse the same agents. The former does transfer learning, the latter allows for
  // G approximation.
  // CCEA ccea(NUM_AGENTS, POOL_SIZE);
  
  // Run CCEA with Network Evaluator
  //ccea.trainForNGenerations(GENS, &evaluator);
  //for (int i = 0; i < GENS; i++) {
  //  ccea.runGeneration(&evaluator);
  //  if (i % 10 == 0) {
  //    std::cout << "Generation: " << i << "\n";
  //  }
  //  std::cout << rWorld.calculateG() << "\n";
    //rWorld.display();
  // }
  return 0;
  
}

std::vector<int> couplingArray(int n) {
  std::vector<int> coupling;
  for (int i = 1; i <= n; i++) {
    coupling.push_back(i);
  }
  return coupling;
}
