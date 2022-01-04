#include "../includes/Chiron.hpp"

void Chiron::obtainRequest(OrderTicket ticket) {
  this->candidates.push(ticket);
}

Drink Chiron::dispense() {
  if (this->candidates.top().container->empty()) {
    this->candidates
        .pop();  // remove from the queue, the OrderTicket has been exhausted
  }
  auto element = this->candidates.top().container;
  Drink returnCandidate = element->back();
  element->pop_back();
  return returnCandidate;
}

bool Chiron::is_empty() const { return this->candidates.empty(); }
