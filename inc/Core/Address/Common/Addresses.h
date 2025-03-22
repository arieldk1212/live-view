#ifndef ADDRESSES_H
#define ADDRESSES_H

#include "Common.h"

namespace Addresses {

struct AddressHeader {
  bool Valid{false};
  std::string ShortAddress;
  std::string FullAddress;

  operator bool() const { return Valid; }
};

/**
 * @brief Get the Address object
 * @param AddressName
 * @return const AddressHeader
 */
inline AddressHeader GetAddress(const std::string &AddressName) {
  return std::move(Common::GetHeader<AddressHeader>(AddressName));
}

/**
 * @brief validate the address object.
 * @param Address
 */
inline void ValidateAddress(AddressHeader &Address) {
  Common::ValidateHeader<AddressHeader>(Address);
}

} // namespace Addresses

#endif