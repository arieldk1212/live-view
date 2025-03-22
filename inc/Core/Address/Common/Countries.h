#ifndef COUNTRIES_H
#define COUNTRIES_H

#include "Common.h"

namespace Countries {

struct CountryHeader {
  bool Valid{false};
  std::string ShortCountry;
  std::string FullCountry;

  operator bool() const { return Valid; }
};

/**
 * @brief Get the Country object
 * @param CountryName
 * @return const CountryHeader
 */
inline CountryHeader GetCountry(const std::string &CountryName) {
  return std::move(Common::GetHeader<CountryHeader>(CountryName));
}

/**
 * @brief validate the country object.
 * @param Country
 */
inline void ValidateCountry(CountryHeader &Country) {
  Common::ValidateHeader<CountryHeader>(Country);
}

} // namespace Countries

#endif