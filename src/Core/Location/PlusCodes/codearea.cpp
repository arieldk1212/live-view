#include "../inc/Core/Location/PlusCodes/codearea.h"

#include <algorithm>

namespace openlocationcode {

const double kLatitudeMaxDegrees = 90;
const double kLongitudeMaxDegrees = 180;

/**
       * @brief Constructs a CodeArea with specified geographical boundaries and code length.
       *
       * This constructor initializes a CodeArea by setting its lower and upper latitude and longitude bounds,
       * along with a code length that represents the precision of the corresponding area.
       *
       * @param latitude_lo Lower bound of the latitude.
       * @param longitude_lo Lower bound of the longitude.
       * @param latitude_hi Upper bound of the latitude.
       * @param longitude_hi Upper bound of the longitude.
       * @param code_length Length of the location code.
       */
      CodeArea::CodeArea(double latitude_lo, double longitude_lo, double latitude_hi,
                   double longitude_hi, size_t code_length)
    : latitude_lo_(latitude_lo), longitude_lo_(longitude_lo),
      latitude_hi_(latitude_hi), longitude_hi_(longitude_hi),
      code_length_(code_length) {}

/**
 * @brief Retrieves the lower latitude bound for the CodeArea.
 *
 * This function returns the stored lower latitude value, representing the minimum boundary of the geographical area.
 *
 * @return The lower latitude bound.
 */
double CodeArea::GetLatitudeLo() const { return latitude_lo_; }

/**
 * @brief Returns the lower longitude bound of the CodeArea.
 *
 * Retrieves the stored lower bound value for longitude, representing the western edge of the geographic area.
 *
 * @return The lower longitude value.
 */
double CodeArea::GetLongitudeLo() const { return longitude_lo_; }

/**
 * @brief Returns the upper latitude bound of the geographical area.
 *
 * This method retrieves the maximum latitude value defining the area, as initialized in the CodeArea object.
 *
 * @return The upper latitude coordinate.
 */
double CodeArea::GetLatitudeHi() const { return latitude_hi_; }

/**
 * @brief Returns the upper longitude bound of the geographical area.
 *
 * This method retrieves the maximum longitude value defining the CodeArea.
 *
 * @return double The upper bound longitude.
 */
double CodeArea::GetLongitudeHi() const { return longitude_hi_; }

/**
 * @brief Retrieves the code length of the geographical area.
 *
 * Returns the number of characters that define the open location code's precision.
 *
 * @return A size_t value representing the code length.
 */
size_t CodeArea::GetCodeLength() const { return code_length_; }

/**
 * @brief Computes the geographical center of the area.
 *
 * Calculates the center latitude and longitude by averaging the lower and upper bounds,
 * while ensuring that the computed values do not exceed the maximum allowed values defined
 * by kLatitudeMaxDegrees and kLongitudeMaxDegrees.
 *
 * @return LatLng The computed center as a coordinate pair.
 */
LatLng CodeArea::GetCenter() const {
  const double latitude_center = std::min(
      latitude_lo_ + (latitude_hi_ - latitude_lo_) / 2, kLatitudeMaxDegrees);
  const double longitude_center =
      std::min(longitude_lo_ + (longitude_hi_ - longitude_lo_) / 2,
               kLongitudeMaxDegrees);
  const LatLng center = {latitude_center, longitude_center};
  return center;
}

} // namespace openlocationcode