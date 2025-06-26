#include "Services/Aws/AwsObj.h"

AwsObj::AwsObj() {
  Aws::InitAPI(m_AwsOptions);
  m_AwsOptions.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
  m_AwsObj.region = "il-central-1";
  APP_INFO("AWS CLIENT CREATED");
}

AwsObj::~AwsObj() {
  Aws::ShutdownAPI(m_AwsOptions);
  APP_CRITICAL("AWS CLIENT DESTROYED");
}