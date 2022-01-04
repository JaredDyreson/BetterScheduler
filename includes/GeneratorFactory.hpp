#pragma once
#include <memory>
#include <iostream>

#include "Generator.hpp"
#include "../includes/dataclasses/OrderTicket.hpp"
#include "../includes/dataclasses/Drink.hpp"

enum GeneratorType { MOBILE, UBER, CAFE, DRIVE };

class UberEats : public Generator {
 public:
   UberEats() {
     OrderTicket ticket;
     for(int i = 0; i < 5; ++i) {
      Drink drink = Drink("Iced Coffee", 1);
      ticket.emplace(drink);
     }
     //this->currentTicket = ticket;
   }
   void printContainer() override{
       for(auto drink : *this->currentTicket.container) {
         std::cout << "hello world" << std::endl;
       }
   }
  ~UberEats() override {}
};

struct GeneratorFactory {
  static std::unique_ptr<Generator> createGenerator(GeneratorType type) {
    switch(type) {
        case GeneratorType::UBER:
          return std::make_unique<UberEats>();
    }
    return std::make_unique<UberEats>();
  }
};
