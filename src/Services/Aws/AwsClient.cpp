#include "Services/Aws/AwsClient.h"

AwsClient::AwsClient() {
  Aws::InitAPI(m_AwsOptions);
  m_AwsOptions.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
  m_AwsClient.region = "il-central-1";
  APP_INFO("AWS CLIENT CREATED");
}

AwsClient::~AwsClient() {
  Aws::ShutdownAPI(m_AwsOptions);
  APP_CRITICAL("AWS CLIENT DESTROYED");
}