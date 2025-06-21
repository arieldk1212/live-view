#include "Core/Image/Image.h"

Image::Image(const std::filesystem::path &Path, const StringUnMap &Relation)
    : m_ImageFolderPath(Path), m_ImageRelation(Relation) {}

Image::Image(const std::filesystem::path &Path, StringUnMap &&Relation)
    : m_ImageFolderPath(Path), m_ImageRelation(std::move(Relation)) {}

void Image::Init() {}

Image::ImageResponse Image::UploadToS3(const std::string &ImageUrl) {}

Image::ImageResponse Image::DeleteFromS3(const std::string &ImageUrl) {}