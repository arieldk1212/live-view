#include "../inc/Core/Location/Geolocation.h"

namespace {
constexpr double MIN_LATITUDE = -90.0;
constexpr double MAX_LATITUDE = 90.0;
constexpr double MIN_LONGITUDE = -180.0;
constexpr double MAX_LONGITUDE = 180.0;
} // namespace

Geolocation::Geolocation(double Latitude, double Longitude)
    : m_Latitude(Latitude), m_Longitude(Longitude) {
  if (m_Latitude < MIN_LATITUDE || m_Latitude > MAX_LATITUDE ||
      m_Longitude < MIN_LONGITUDE || m_Longitude > MAX_LONGITUDE) {
    throw std::invalid_argument("Latitude Longitude Error");
  }
  try {
    auto Code = openlocationcode::Encode({m_Latitude, m_Longitude});
    if (openlocationcode::IsValid(Code)) {
      m_PlusCode = Code;
    } else {
      m_PlusCode = "Not Valid";
    }
  } catch (const std::exception &e) {
    m_PlusCode = static_cast<std::string>(e.what());
  }
}

const std::string Geolocation::GetPlusCode() const { return m_PlusCode; }
const std::string Geolocation::GetCoordinatesString() const {
  return "Latitude: " + std::to_string(m_Latitude) +
         " Longitude: " + std::to_string(m_Longitude);
}
const std::pair<double, double> Geolocation::GetCoordinates() const {
  return {m_Latitude, m_Longitude};
}