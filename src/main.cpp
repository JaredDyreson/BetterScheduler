#include <iostream>

#include "../includes/GeneratorFactory.hpp"
#include "../includes/Chiron.hpp"

int main() {
  std::unique_ptr<Generator> generator =
      GeneratorFactory::createGenerator(GeneratorType::UBER);
  Chiron styx  = Chiron();

  generator->printContainer();
  while(!generator->is_empty()) {
    std::cout << "I got an object" << std::endl;
    //styx.obtainRequest(generator->dispense());
    generator->dispense();
  }
  return 0;
}
