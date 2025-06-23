#ifndef RDS_SERVICE_H
#define RDS_SERVICE_H

#include "AwsClient.h"


class RDSService final {
public:
  RDSService();
  ~RDSService();

  bool Status() const { return m_Status; }

private:
  bool m_Status;
};

#endif