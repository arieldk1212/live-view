#ifndef OBJECT_LOGGER_H
#define OBJECT_LOGGER_H

#include <string>

// TODO: write this into database, when accessible.

/**
 * @brief Abstract base class for logging messages.
 *
 * This class defines a common interface for logging operations. Derived classes must override
 * the log() method to implement specific logging behaviors. The log() method accepts an rvalue
 * reference to a std::string, allowing efficient transfer of the message data.
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