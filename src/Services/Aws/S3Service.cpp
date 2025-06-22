#include "Services/Aws/S3Service.h"

S3Service::S3Service() : m_Status(true) { APP_INFO("S3 SERVICE CREATED"); }

S3Service::~S3Service() {
  if (!m_Status) {
    APP_CRITICAL("S3 SERVICE DESTROYED");
  }
}