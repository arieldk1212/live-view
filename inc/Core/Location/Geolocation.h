#ifndef GEOLOCATION_H
#define GEOLOCATION_H

#include "PlusCodes/openlocationcode.h"

#include <string>

/**
 * @brief this file is responsible for the image, address geolocation,
 * verification, also verifying with a gps.
 */
class Geolocation {
public:
  /**
   * @todo log the geolocation in the correct address, then make sure to log
   * errors and exceptions.
   */
  Geolocation(double Latitude, double Longitude);
  ~Geolocation() = default;

  [[nodiscard]] const std::string GetPlusCode() const;
  [[nodiscard]] const std::string GetCoordinatesString() const;
  [[nodiscard]] const std::pair<double, double> GetCoordinates() const;

private:
  double m_Longitude;
  double m_Latitude;
  std::string m_PlusCode;
};

#endif