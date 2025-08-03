// #ifndef S3_SERVICE_H
// #define S3_SERVICE_H

// #include "AwsObj.h"
// #include "Services/Aws/RDSService.h"

// #include <aws/s3/S3Client.h>
// #include <aws/s3/S3ClientConfiguration.h>
// #include <aws/s3/model/BucketLocationConstraint.h>
// #include <aws/s3/model/CreateBucketRequest.h>
// #include <variant>
// #include <vector>

// class S3Service final {
// public:
//   S3Service();
//   ~S3Service();

//   bool Status() const { return m_Status; }

//   bool CreateBucket(const Aws::String &BucketName);

// private:
//   bool m_Status;
//   Aws::S3::S3Client m_S3Client;
//   std::unique_ptr<AwsObj> m_AwsObj;
//   Aws::S3::S3ClientConfiguration m_S3ClientConfig{m_AwsObj->GetAwsObj()};
// };

// class Services {
// public:
// private:
//   std::vector<std::variant<S3Service, RDSService>> m_Services;
// };

// #endif