#include <iostream>

#include "../includes/GeneratorFactory.hpp"
#include "../includes/Chiron.hpp"
#include "../includes/DrinkHeap.hpp"

int main() {
  std::unique_ptr<Generator> generator =
      GeneratorFactory::createGenerator(GeneratorType::UBER);
  Chiron styx  = Chiron();
  DrinkHeap heap = DrinkHeap();

  generator->printContainer();

  styx.obtainRequest(generator->dispense());

  while(!styx.is_empty()){
    heap.insert(styx.dispense());
  }

  //while(!generator->is_empty()) {
    //std::cout << "I got an object" << std::endl;
  //}
  return 0;
}
