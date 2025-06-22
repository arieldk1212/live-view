#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>
#include <unordered_map>

class Image {
public:
  using StringUnMap = std::unordered_map<std::string, std::string>;

  struct ImageResponse {
    ImageResponse();

    std::string Data;
    bool IsValid{false};
  };

public:
  Image(const std::filesystem::path &Path, const StringUnMap &Relation);
  Image(const std::filesystem::path &Path, StringUnMap &&Relation);
  ~Image();

  void Init();
  ImageResponse UploadToS3(const std::string &ImageUrl);
  ImageResponse DeleteFromS3(const std::string &ImageUrl);
  const std::string &GetS3URL() const { return m_ImageUrl; }
  const std::filesystem::path &GetImagePath() const {
    return m_ImageFolderPath;
  }

private:
  StringUnMap m_ImageRelation;
  std::string m_ImagesRelation;
  std::string m_ImageUrl;
  std::filesystem::path m_ImageFolderPath;
};

#endif