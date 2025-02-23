#ifndef CONDITION_H
#define CONDITION_H

#include "../../../Config/Logger.h"

#include <string>

class Condition {
public:
  virtual ~Condition() = 0;
  virtual void ConditionType() = 0;
};

#endif