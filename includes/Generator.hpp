#pragma once

#include <vector>

#include "dataclasses/OrderTicket.hpp"

class Generator {
 public:
  Generator();
  void emplace(OrderTicket);
  OrderTicket dispense();
  bool is_empty() const;

  virtual void printContainer() = 0;
  virtual ~Generator() = 0;

 protected:
  OrderTicket container;
};

inline Generator::~Generator(){};
