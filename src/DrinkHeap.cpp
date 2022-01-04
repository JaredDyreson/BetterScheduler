#include "../includes/DrinkHeap.hpp"
#include "../includes/dataclasses/Drink.hpp"

void DrinkHeap::insert(std::vector<Drink> _drinks) {
  while(!_drinks.empty()) {
    this->minHeap.push(_drinks.back());
    _drinks.pop_back();
  }
}

Drink DrinkHeap::pop() {
  Drink returnCandidate = this->minHeap.top();
  this->minHeap.pop();
  return returnCandidate;
}
