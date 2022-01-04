#pragma once

#include <string>
#include <ctime>

#include "../Severity.hpp"

typedef struct Drink {
  Drink(std::string, int);
  size_t sinceEpoch() const;
  friend bool operator<(const Drink&, const Drink&);

  int unit_price;
  SEVERITY importance;
  int quantity;
  std::string name;
  std::tm *timestamp;
} Drink;

