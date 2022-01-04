#include "dataclasses/Drink.hpp"

#include <vector>
#include <queue>

class DrinkHeap {
  /*
   * In the future this should be
   * NodeHeap
   * where `T` type occupy the priority heap
  */

  public:
    DrinkHeap();
    void insert(Drink);
    Drink pop();
  private:
    std::priority_queue<Drink, std::vector<Drink>> minHeap;
};

