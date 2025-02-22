#include "../inc/Core/Image.h"

/**
     * @brief Constructs an Image object.
     *
     * Initializes the object's folder path and relation mapping with the provided values.
     *
     * @param Path The filesystem path indicating the image folder location.
     * @param Relation A mapping detailing the image relationships.
     */
    Image::Image(const std::filesystem::path &Path, const StringUnMap &Relation)
    : m_ImageFolderPath(Path), m_ImageRelation(Relation) {}