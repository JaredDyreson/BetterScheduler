#include "../includes/Generator.hpp"
#include "../includes/dataclasses/OrderTicket.hpp"

Generator::Generator() {}

OrderTicket Generator::dispense() {
  /*
   * Once we give the contents of our OrderTicket
   * we no longer want the information persist
   */

  OrderTicket returnTicket = this->container;
  // FIXME: we need some way to clear this object after dispensing
  return returnTicket;
}

bool Generator::is_empty() const{
  return true; // this should probably check if this->container is a nullptr but I want to actively avoid a use after free here
}
