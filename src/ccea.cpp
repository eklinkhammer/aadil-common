#include "ccea.h"

void testNetEval(std::vector<FANN::neural_net*> vec, double results[]) {
  results[0] = 4.2;
}
  
CCEA::CCEA() {

}

CCEA::CCEA (int size, int s) {

}

void CCEA::runGeneration(void(*evalNet)(std::vector<FANN::neural_net*>, double[]),double) {
  FANN::neural_net* net = new FANN::neural_net();
  std::vector<FANN::neural_net*> vec;
  vec.push_back(net);
  double a[1];
  evalNet(vec, a);
  std::cout << a[0];
  std::cout << "\n";
}

int main () {
  std::cout << "Hello World!\n";
  CCEA ccea;
  ccea.runGeneration(testNetEval,0.0);
  return 0;
}
