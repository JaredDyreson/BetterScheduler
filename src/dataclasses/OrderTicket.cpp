#include "../../includes/dataclasses/OrderTicket.hpp"

#include <iostream>
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
  this->container = new std::vector<Drink>();
}

OrderTicket::OrderTicket(const OrderTicket& other) {
  this->container =
      new std::vector<Drink>(other.container->begin(), other.container->end());
}

OrderTicket::~OrderTicket() {
  std::cout << "this is before deallocating the object" << std::endl;
  // delete this->container; FIXME
}

OrderTicket& OrderTicket::operator=(OrderTicket ticket) {
  this->container =
      new std::vector<Drink>(ticket.container->begin(), ticket.container->end());
  this->timestamp = ticket.timestamp;
  return *this;
}

void OrderTicket::emplace(Drink _drink) {
  /*
   * We assume this comes from some sort of UI
   * or file information
   */
  _drink.timestamp = this->timestamp;
  (*this->container).push_back(_drink);
}

size_t OrderTicket::sinceEpoch() const {
  /*
   * Give the time since the object was created
   */

  return std::mktime(this->timestamp);
}

size_t OrderTicket::count() const { return this->container->size(); }

bool operator<(const OrderTicket& a, const OrderTicket& b) {
  /*
   * We compare if which ticket has higher priority based
   * on the severity enumeration and how old the order is
   */

  return ((a.importance < b.importance) && (a.sinceEpoch() < b.sinceEpoch()));
}
