#include "FactoryRegister.h"

/// include
#include "./createClass/Action.h"

/// registers
void FactoryRegister::Registers() {
    factory_.Register<Action>();
}
