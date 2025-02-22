#ifndef ROAD_CONDITION_H
#define ROAD_CONDITION_H

#include "Condition.h"

/**
 * @brief Abstract base class for road conditions.
 *
 * This class extends the Condition class by providing a default implementation
 * for setting a generic road condition type ("Road Condition"). It also enforces that
 * derived classes implement a method to append specific details to the road condition.
 */

/**
 * @brief Virtual destructor for RoadCondition.
 *
 * Ensures proper cleanup for derived classes during polymorphic deletion.
 */

/**
 * @brief Sets the generic road condition type.
 *
 * Overrides the base implementation to assign "Road Condition" to the internal
 * road condition type string.
 */

/**
 * @brief Pure virtual function to set detailed road condition information.
 *
 * Derived classes must implement this method to modify or append specific details
 * (e.g., " - in Construction.") to the generic road condition type.
 */
class RoadCondition : public Condition {
public:
	virtual ~RoadCondition();

	void ConditionType() override { m_RoadConditionType = "Road Condition"; }
	virtual void RoadConditionType() = 0;

protected:
	std::string m_RoadConditionType;
};

class Construction : public RoadCondition {
public:
	Construction() {
		RoadConditionType();
		// TODO: we need to set the LOG msg to a certain Address ID.
		APP_TRACE("ROAD CONDITION SET TO: CONSTRUCTION");
	};
	~Construction() override;
	void RoadConditionType() override {
		m_ConstructionRoadCondition = m_RoadConditionType + " - in Construction.";
	}

private:
	std::string m_ConstructionRoadCondition;
};

#endif