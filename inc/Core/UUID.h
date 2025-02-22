#ifndef UUID_H
#define UUID_H

#include <cstdint>
#include <random>

/**
 * @brief Generates a new universally unique identifier (UUID).
 *
 * This function returns a randomly generated 64-bit unsigned integer that serves as a UUID.
 *
 * @return The generated UUID as a 64-bit unsigned integer.
 */
namespace UUID {
  const uint64_t GenUUID();
} // namespace UUID

#endif