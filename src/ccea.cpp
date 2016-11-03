#include "ccea.h"

int CCEA::dummy() {
  return 5;
}
void testNetEval(std::vector<FANN::neural_net*> vec, double results[]) {
  results[0] = 4.2;
}
  
CCEA::CCEA() {

}

CCEA::CCEA (int size, int s, NetworkConfig config) {

}

void CCEA::runGeneration(void(*evalNet)(std::vector<FANN::neural_net*>, double[])) {
  FANN::neural_net* net = new FANN::neural_net();
  std::vector<FANN::neural_net*> vec;
  vec.push_back(net);
  double a[1];
  evalNet(vec, a);
  std::cout << a[0];
  std::cout << "\n";
}

/*int main () {
  std::cout << "Hello World!\n";
  CCEA ccea;
  ccea.runGeneration(testNetEval,0.0);
  std::cout << ccea.dummy();
  std::cout << "\n";
  return 0;
  }*/
