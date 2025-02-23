#ifndef OBJECT_LOGGER_H
#define OBJECT_LOGGER_H

#include <string>

// TODO: write this into database, when accessible.

/**
 * @brief wont be done now, not until we figure out elastic search and kibana structure.
 * add this to LogModel!
 */

class InstanceLogger {
public:
	virtual ~InstanceLogger();
	virtual void log(std::string &&data) = 0;
};

class AddressLogger final : public InstanceLogger {
public:
	void log(std::string &&data) override;
};

class BusinessLogger final : public InstanceLogger {
public:
	void log(std::string &&data) override;
};

// TODO: street, road, business loggers..

#endif