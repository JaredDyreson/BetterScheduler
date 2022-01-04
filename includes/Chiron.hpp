#include <queue>
#include <vector>

#include "Generator.hpp"
#include "dataclasses/OrderTicket.hpp"

/*
 * Listens for requests from server and
 * is the arbitier of what gets emplaced onto the
 * priority heap. This is a facade pattern
 */

class Chiron {
 public:
  void obtainRequest(OrderTicket);
  OrderTicket dispense();

 private:
  std::priority_queue<OrderTicket> candidates;
};
