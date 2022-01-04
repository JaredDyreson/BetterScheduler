#include "../includes/Chiron.hpp"

void Chiron::obtainRequest(OrderTicket ticket) {

}

OrderTicket Chiron::dispense() {
  OrderTicket returnCandidate = this->candidates.top();
  this->candidates.pop();
  return returnCandidate;
}
