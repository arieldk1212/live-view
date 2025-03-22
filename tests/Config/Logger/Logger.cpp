#include "Config/Logger.h"
#include "../../Test.h"

int main() {

  Logger::Init("logs/");
  APP_ERROR("Test");
  APP_INFO("Test");
  APP_TRACE("Test");
  APP_CRITICAL("Test");
  APP_DEBUG("Test");
  APP_WARNING("Test");

  SYSTEM_ERROR("Test");
  SYSTEM_INFO("Test");
  SYSTEM_TRACE("Test");
  SYSTEM_CRITICAL("Test");
  SYSTEM_DEBUG("Test");
  SYSTEM_WARNING("Test");
}