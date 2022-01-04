#pragma once

#include <ctime>
#include <vector>

#include "Drink.hpp"
#include "../Severity.hpp"

class OrderTicket {
 public:
  OrderTicket();
  void emplace(Drink);
  size_t count();
  size_t sinceEpoch() const;
  friend bool operator<(const OrderTicket&, const OrderTicket&);
  std::vector<Drink> container; // FIXME

 private:
  SEVERITY importance;
  double price;
  std::tm *timestamp;
};
