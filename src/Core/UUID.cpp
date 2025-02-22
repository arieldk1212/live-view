#include "../inc/Core/UUID.h"

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

namespace UUID {
/**
 * @brief Generates a random 64-bit UUID.
 *
 * This function uses a uniform integer distribution and a Mersenne Twister engine to generate 
 * a new random 64-bit unsigned integer, which serves as a universally unique identifier (UUID).
 *
 * @return const uint64_t A randomly generated UUID.
 */
const uint64_t GenUUID() { return s_UniformDistribution(s_Engine); }
} // namespace UUID