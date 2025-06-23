#ifndef AWS_CLIENT_H
#define AWS_CLIENT_H

#include "Config/Logger.h"

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/http/HttpResponse.h>
using namespace Aws;
using namespace Aws::Auth;

class AwsClient final {
public:
  AwsClient();
  ~AwsClient();

  const auto &GetAwsClient() const { return m_AwsClient; }
  const auto &GetOptions() const { return m_AwsOptions; }

private:
  Aws::SDKOptions m_AwsOptions;
  Aws::Client::ClientConfiguration m_AwsClient;
};

#endif