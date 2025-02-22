#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>
#include <unordered_map>

/**
 * @brief Represents an image with associated metadata for external storage.
 *
 * This class encapsulates details such as the local folder path, external URL, and image metadata
 * provided via a key-value map. It supports initializing an image object with either a constant or
 * movable metadata map, enabling efficient resource management. The image may reside on external
 * storage systems (e.g., an S3 bucket), and the class provides an Init() method for any additional
 * initialization steps post construction.
 */

class Image {
public:
  using StringUnMap = std::unordered_map<std::string, std::string>;

public:
  Image(const std::filesystem::path &Path, const StringUnMap &Relation);
  Image(const std::filesystem::path &Path, StringUnMap &&Relation);
  ~Image();

  void Init();

private:
  StringUnMap m_ImageRelation;
  std::string m_ImagesRelation;
  std::string m_ImageURL;
  std::filesystem::path m_ImageFolderPath;
};

#endif