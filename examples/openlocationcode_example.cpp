#include "../inc/Core/Location/PlusCodes/openlocationcode.h"

#include <iomanip>
#include <iostream>

/**
 * @brief Demonstrates the usage of the Open Location Code library.
 *
 * This function serves as the entry point of the program and shows how to:
 * - Encode geographic coordinates into Plus+Codes, both with default and specified code lengths.
 * - Decode a Plus+Code into its geographical area.
 * - Validate whether a Plus+Code is valid, full, or short.
 * - Shorten a Plus+Code relative to a reference location.
 * - Recover the full Plus+Code from a shortened version using a reference location.
 *
 * The results of these operations are printed to the console.
 *
 * @return int Exit status (0 indicates successful execution).
 */
int main() {
  // Encodes latitude and longitude into a Plus+Code.
  std::string code = openlocationcode::Encode({47.0000625, 8.0000625});
  std::cout << "Encoded: " << code << "\n";
  // => "8FVC2222+22"

  // Encodes latitude and longitude into a Plus+Code with a preferred length.
  code = openlocationcode::Encode({47.0000625, 8.0000625}, 16);
  std::cout << "Encoded 16: " << code << "\n";
  // => "8FVC2222+22GCCCC"

  // Decodes a Plus+Code back into coordinates.
  openlocationcode::CodeArea code_area = openlocationcode::Decode(code);
  std::cout << "Code length: " << std::fixed << std::setprecision(15) << ' '
            << code_area.GetLatitudeLo()         // 47.000062479999997
            << ' ' << code_area.GetLongitudeLo() // 8.000062500000013
            << ' ' << code_area.GetLatitudeHi()  // 47.000062520000000
            << ' ' << code_area.GetLongitudeHi() // 8.000062622070317
            << ' ' << code_area.GetCodeLength()  // 15
            << "\n";

  // Checks if a Plus+Code is valid.
  bool isValid = openlocationcode::IsValid(code);
  std::cout << "Is valid? " << isValid << "\n";
  // => true

  // Checks if a Plus+Code is full.
  bool isFull = openlocationcode::IsFull(code);
  std::cout << "Is full? " << isFull << "\n";
  // => true

  // Checks if a Plus+Code is short.
  bool isShort = openlocationcode::IsShort(code);
  std::cout << "Is short? " << isShort << "\n";
  // => false

  // Shorten a Plus+Codes if possible by the given reference latitude and
  // longitude.
  std::string short_code =
      openlocationcode::Shorten("9C3W9QCJ+2VX", {51.3708675, -1.217765625});
  std::cout << "Shortened: " << short_code << "\n";
  // => "CJ+2VX"

  // Extends a Plus+Code by the given reference latitude and longitude.
  std::string recovered_code =
      openlocationcode::RecoverNearest("CJ+2VX", {51.3708675, -1.217765625});
  std::cout << "Recovered: " << recovered_code << "\n";
  // => "9C3W9QCJ+2VX"
}