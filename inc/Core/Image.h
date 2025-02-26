#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>
#include <unordered_map>

/**
 * @brief images will be saved in a different storage, possibly an S3 bucket or
 * something like that.
 */

class Image {
public:
  using StringUnMap = std::unordered_map<std::string, std::string>;

public:
  Image(const std::filesystem::path &Path, const StringUnMap &Relation);
  Image(const std::filesystem::path &Path, StringUnMap &&Relation);
  ~Image();

  void Init();
  bool UploadToS3();
  bool DeleteFromS3();
  const std::string GetS3URL() const { return m_ImageURL; }
  const std::filesystem::path GetImagePath() const { return m_ImageFolderPath; }

private:
  StringUnMap m_ImageRelation;
  std::string m_ImagesRelation;
  std::string m_ImageURL;
  std::filesystem::path m_ImageFolderPath;
};

#endif