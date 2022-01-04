#include "../../includes/dataclasses/Drink.hpp"

#include <string>
#include <ctime>

Drink::Drink(std::string _name, int quant) {
  this->name = _name;
  this->quantity = quant;
}

bool operator<(const Drink& a, const Drink& b) {
  return ((a.sinceEpoch() < b.sinceEpoch()) && (a.importance < b.importance));
}

size_t Drink::sinceEpoch() const {
	return std::mktime(this->timestamp);
}
