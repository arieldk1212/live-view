#ifndef LOCATION_OPENLOCATIONCODE_CODEAREA_H
#define LOCATION_OPENLOCATIONCODE_CODEAREA_H

#include <cstdlib>

/**
 * @brief Represents a geographic coordinate with latitude and longitude.
 */

/**
 * @brief Represents a geographic area defined by latitude and longitude bounds, along with a specific code length.
 *
 * This class encapsulates a region specified by its lower and upper latitude and longitude boundaries. The code length indicates
 * the number of characters in the encoded area representation.
 */

/**
 * @brief Constructs a CodeArea with the specified geographical bounds and code length.
 *
 * @param latitude_lo Lower bound for latitude.
 * @param longitude_lo Lower bound for longitude.
 * @param latitude_hi Upper bound for latitude.
 * @param longitude_hi Upper bound for longitude.
 * @param code_length Length of the code representing this area.
 */

/**
 * @brief Returns the lower latitude bound of the CodeArea.
 *
 * @return The lower latitude bound.
 */

/**
 * @brief Returns the lower longitude bound of the CodeArea.
 *
 * @return The lower longitude bound.
 */

/**
 * @brief Returns the upper latitude bound of the CodeArea.
 *
 * @return The upper latitude bound.
 */

/**
 * @brief Returns the upper longitude bound of the CodeArea.
 *
 * @return The upper longitude bound.
 */

/**
 * @brief Returns the code length associated with the CodeArea.
 *
 * @return The code length.
 */

/**
 * @brief Computes and returns the center coordinate of the CodeArea.
 *
 * The center is calculated as the midpoint between the lower and upper latitude bounds and the midpoint between the lower and upper
 * longitude bounds.
 *
 * @return A LatLng structure representing the center coordinate of the area.
 */
namespace openlocationcode {

struct LatLng {
  double latitude;
  double longitude;
};

class CodeArea {
 public:
  CodeArea(double latitude_lo, double longitude_lo, double latitude_hi,
           double longitude_hi, size_t code_length);
  double GetLatitudeLo() const;
  double GetLongitudeLo() const;
  double GetLatitudeHi() const;
  double GetLongitudeHi() const;
  size_t GetCodeLength() const;
  LatLng GetCenter() const;

 private:
  double latitude_lo_;
  double longitude_lo_;
  double latitude_hi_;
  double longitude_hi_;
  size_t code_length_;
};

}  // namespace openlocationcode

#endif  // LOCATION_OPENLOCATIONCODE_CODEAREA_H_