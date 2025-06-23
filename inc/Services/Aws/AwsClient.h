#ifndef AWS_CLIENT_H
#define AWS_CLIENT_H

#include "Config/Logger.h"

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/s3/S3ClientConfiguration.h>
using namespace Aws;
using namespace Aws::Auth;

class AwsClient final {
public:
  AwsClient();
  ~AwsClient();

  const auto &GetS3Client() const { return m_S3Client; }
  const auto &GetAwsClient() const { return m_AwsClient; }
  const auto &GetOptions() const { return m_AwsOptions; }

private:
  Aws::SDKOptions m_AwsOptions;
  Aws::Client::ClientConfiguration m_AwsClient;
  Aws::S3::S3ClientConfiguration m_S3Client{m_AwsClient};
};

#endif