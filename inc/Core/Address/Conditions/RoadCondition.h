#ifndef ROAD_CONDITION_H
#define ROAD_CONDITION_H

#include "Condition.h"

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