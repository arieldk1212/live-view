#include "../inc/Core/Location/Geolocation.h"

Geolocation::Geolocation(double Latitude, double Longitude)
    : m_Latitude(Latitude), m_Longitude(Longitude) {
  auto Code = openlocationcode::Encode({m_Latitude, m_Longitude});
  if (openlocationcode::IsValid(Code)) {
    m_PlusCode = Code;
  } else {
    m_PlusCode = "Not Valid";
  }
}

const std::string Geolocation::GetPlusCode() const { return m_PlusCode; }
std::string Geolocation::GetCoordinates() const {
  return "Latitude: " + std::to_string(m_Latitude) +
         " Longitude: " + std::to_string(m_Longitude);
}