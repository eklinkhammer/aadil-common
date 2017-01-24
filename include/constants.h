#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "yaml-cpp/yaml.h"

YAML::Node config = YAML::LoadFile("../config.yaml");

// Debugging Parameters
const bool DEBUG = config["debug"].as<bool>();
const double VIEW_FREQUENCY = 0.1;

// Experiment Parameters
const int NUM_AGENTS = config["experiment"]["number_agents"].as<int>();
const int NUM_POIS   = config["experiment"]["number_pois"].as<int>();
const double SIZE_WORLD = config["experiment"]["size_world"].as<double>();
const double POI_RANGE_PERCENT_WORLD = config["experiment"]["poi_range_percent_world_size"].as<double>();
const int GENS = config["experiment"]["generations"].as<int>();
const std::string rString = config["experiment"]["reward"].as<std::string>();
const int SIM_TIMESTEPS = config["experiment"]["simulation_timesteps"].as<int>();
const int MIN_COUPLING = config["experiment"]["min_coupling"].as<int>();
const int MAX_COUPLING = config["experiment"]["max_coupling"].as<int>();

// Network Config
const FANN::network_type_enum NET_TYPE = FANN::LAYER;
const unsigned int NUM_LAYERS = config["network"]["number_layers"].as<int>();
const unsigned int INPUT_LAYER = config["network"]["input_layer"].as<int>();
const unsigned int HIDDEN_LAYER = config["network"]["hidden_layer"].as<int>();
const unsigned int OUTPUT_LAYER = config["network"]["output_layer"].as<int>();
unsigned int LAYERS[3] = {INPUT_LAYER, HIDDEN_LAYER, OUTPUT_LAYER};
const bool RANDOM_WEIGHTS = config["network"]["random_weights"].as<bool>();
const double RANDOM_MIN = config["network"]["random_min"].as<double>();
const double RANDOM_MAX = config["network"]["random_max"].as<double>();

// CCEA Config
const unsigned int NUMBER_POOLS = (unsigned int) config["ccea"]["number_pools"].as<int>();
const unsigned int NUMBER_NETWORKS = config["ccea"]["number_networks"].as<int>();
const double PERCENT_TO_MUTATE = config["ccea"]["percent_to_mutate"].as<double>();
const double MAG_MUTATION = config["ccea"]["mag_mutation"].as<double>();
const double PERCENT_BEST_CHOSEN = config["ccea"]["percent_best_chosen"].as<double>();
#endif
