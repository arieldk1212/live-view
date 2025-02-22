#ifndef CONDITION_H
#define CONDITION_H

#include "../../../Config/Logger.h"

#include <string>

/**
 * @brief Abstract base class for representing a condition.
 *
 * This class provides an interface for various condition types. It declares a
 * pure virtual destructor to ensure proper cleanup in derived classes and a
 * pure virtual method, ConditionType, that must be implemented by subclasses
 * to define their specific behavior.
 *
 * @note This abstract class cannot be instantiated directly.
 */

/**
 * @brief Pure virtual destructor.
 *
 * Ensures that the destructor of derived classes is called correctly.
 */

/**
 * @brief Specifies the condition type.
 *
 * Derived classes must override this method to implement behavior that identifies
 * or defines the type of condition.
 */
class Condition {
public:
  virtual ~Condition() = 0;
  virtual void ConditionType() = 0;
};

#endif