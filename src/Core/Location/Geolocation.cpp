#include "../inc/Core/Location/Geolocation.h"

/**
 * @brief Initializes a Geolocation instance with specified coordinates.
 *
 * This constructor sets the latitude and longitude for the location and generates a corresponding Plus Code.
 * It calls openlocationcode::Encode to compute the code and, using openlocationcode::IsValid, verifies its validity.
 * If the Plus Code is valid, it is stored; otherwise, the Plus Code is set to "Not Valid".
 *
 * @param Latitude The latitude value for the location.
 * @param Longitude The longitude value for the location.
 */
Geolocation::Geolocation(double Latitude, double Longitude)
    : m_Latitude(Latitude), m_Longitude(Longitude) {
  auto Code = openlocationcode::Encode({m_Latitude, m_Longitude});
  if (openlocationcode::IsValid(Code)) {
    m_PlusCode = Code;
  } else {
    m_PlusCode = "Not Valid";
  }
}

/**
 * @brief Retrieves the Plus Code for the geolocation.
 *
 * This function returns the Plus Code generated during the construction of the
 * Geolocation object by encoding the provided latitude and longitude. If the
 * generated Plus Code is invalid, it returns "Not Valid".
 *
 * @return A string representing the Plus Code, or "Not Valid" if the code is invalid.
 */
const std::string Geolocation::GetPlusCode() const { return m_PlusCode; }
/**
 * @brief Retrieves the geolocation coordinates as a formatted string.
 *
 * Constructs and returns a string displaying the latitude and longitude
 * in the format "Latitude: [value] Longitude: [value]".
 *
 * @return std::string The formatted coordinates.
 */
std::string Geolocation::GetCoordinates() const {
  return "Latitude: " + std::to_string(m_Latitude) +
         " Longitude: " + std::to_string(m_Longitude);
}