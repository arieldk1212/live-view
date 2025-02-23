#include "../inc/Core/UUID.h"

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

namespace UUID {
const uint64_t GenUUID() { return s_UniformDistribution(s_Engine); }
} // namespace UUID