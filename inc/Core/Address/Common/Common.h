#ifndef COMMON_H
#define COMMON_H

#include <concepts>
#include <string>

/**
 * @brief this class and folder Common, is responsible for the validation of
 * Addresses and Countries when inputted, meaning if the user inputs an existing
 * data.
 * its the backend of the validation process in the frontend using third party
 * api for validation.
 * @todo test it, finish implementing it, test for move semantics.
 */

namespace Common {

static void Lookup();

/**
 * @brief Returns a new Header object of a specific type, initializing the
 * fields with "default" values.
 * @tparam Header
 * @param Name
 * @return Header
 */
template <typename Header> static Header GetHeader(const std::string &Name) {
  /**
   * @arg Valid: false, ShortName: "", FullName: Name
   */
  return std::move(Header{false, "", Name});
}

/**
 * @brief concept for Country Fields.
 * @tparam Header
 */
template <typename Header>
concept HasCountryFields = requires(Header header) {
  header.ShortCountry;
  header.FullCountry;
};

/**
 * @brief concept for Address Fields.
 * @tparam Header
 */
template <typename Header>
concept HasAddressFields = requires(Header header) {
  header.ShortAddress;
  header.FullAddress;
};

template <typename Header> static void ValidateHeader(Header &header) {
  /**
   * @todo
   * validation logic here.
   * checks header in third party api.
   * checks header full name and short name that they are valid.
   */
  if constexpr (HasAddressFields<Header>) {
    /**
     * header.ShortAddress = validated name..
     * header.FullAddress = validated name..
     */
  } else if constexpr (HasCountryFields<Header>) {
    /**
     * header.ShortCountry = validated name..
     * header.FullCountry = validated name..
     */
  }
  header.Valid = true;
}

} // namespace Common

#endif