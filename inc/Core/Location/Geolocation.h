#ifndef GEOLOCATION_H
#define GEOLOCATION_H

#include "PlusCodes/openlocationcode.h"

#include <string>

/**
 * @brief Encapsulates geolocation data and utilities.
 *
 * Initializes a geolocation object with specified latitude and longitude values.
 * The class provides methods to retrieve the associated Plus Code and a formatted
 * string of the coordinates. It is designed for applications requiring geolocation
 * verification, such as image or address geolocation and basic GPS validation.
 *
 * @example
 * Geolocation location(37.421998, -122.084);
 * std::string plusCode = location.GetPlusCode();
 * std::string coords = location.GetCoordinates();
 */

class Geolocation {
public:
  Geolocation(double Latitude, double Longitude);
  ~Geolocation() = default;

  [[nodiscard]] const std::string GetPlusCode() const;
  [[nodiscard]] std::string GetCoordinates() const;

private:
  double m_Longitude;
  double m_Latitude;
  std::string m_PlusCode;
};

#endif