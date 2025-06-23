#ifndef S3_SERVICE_H
#define S3_SERVICE_H

#include "AwsClient.h"

#include <aws/s3/S3Client.h>
#include <aws/s3/model/BucketLocationConstraint.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <memory>

class S3Service final {
public:
  S3Service();
  ~S3Service();

  bool Status() const { return m_Status; }

  bool CreateBucket(const Aws::String &BucketName);

private:
  bool m_Status;
  std::unique_ptr<AwsClient> m_Client;
};

#endif