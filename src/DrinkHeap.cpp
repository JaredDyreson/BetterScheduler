#include "../includes/DrinkHeap.hpp"
#include "../includes/dataclasses/Drink.hpp"

void DrinkHeap::insert(Drink _drink) {
    this->minHeap.push(_drink);
}

DrinkHeap::DrinkHeap(){}

Drink DrinkHeap::pop() {
  Drink returnCandidate = this->minHeap.top();
  this->minHeap.pop();
  return returnCandidate;
}
