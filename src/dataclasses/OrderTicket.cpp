#include "../../includes/dataclasses/OrderTicket.hpp"

#include <vector>

#include "../../includes/dataclasses/Drink.hpp"

OrderTicket::OrderTicket() {
  /*
   * Get the time in which the object was created
   * This will be used to help reorder the priority heap
   */
  std::time_t rawtime;
  std::time(&rawtime);
  this->timestamp = std::localtime(&rawtime);
}

void OrderTicket::emplace(Drink _drink) {
  /*
   * We assume this comes from some sort of UI
   * or file information
   */
  _drink.timestamp = this->timestamp;
  this->container.push_back(_drink);
}

size_t OrderTicket::sinceEpoch() const {
  /*
   * Give the time since the object was created
   */

  return std::mktime(this->timestamp);
}

bool operator<(const OrderTicket& a, const OrderTicket& b) {
  /*
   * We compare if which ticket has higher priority based
   * on the severity enumeration and how old the order is
   */

  return (
      (a.importance < b.importance) && (a.sinceEpoch() < b.sinceEpoch()));
}
