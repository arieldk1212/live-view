#ifndef AWS_OBJ_H
#define AWS_OBJ_H

#include "Config/Logger.h"

#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/http/HttpResponse.h>
using namespace Aws;
using namespace Aws::Auth;

class AwsObj final {
public:
  AwsObj();
  ~AwsObj();

  const auto &GetAwsObj() const { return m_AwsObj; }
  const auto &GetOptions() const { return m_AwsOptions; }

private:
  Aws::SDKOptions m_AwsOptions;
  Aws::Client::ClientConfiguration m_AwsObj;
};

#endif