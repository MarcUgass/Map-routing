#pragma once

#include "PuntDeInteresBase.h"
#include <string>

using namespace std;

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() { m_tagShop = "", m_tagOpeningHours = "", m_tagWheelChair = ""; }
	~PuntDeInteresBotigaSolucio() {}
	PuntDeInteresBotigaSolucio(const Coordinate& c, const string& name, const string& shop, const string& hour, const string& wheelChair) : PuntDeInteresBase(c, name) { m_tagShop = shop, m_tagOpeningHours = hour, m_tagWheelChair = wheelChair; }

	unsigned int getColor();

	void setShop(const string shop) { m_tagShop = shop; }
	void setOpeningHours(const string openingHours) { m_tagOpeningHours = openingHours; }
	void setWheelChair(const string wheelChair) { m_tagWheelChair = wheelChair; }
private:
	string m_tagShop;
	string m_tagOpeningHours;
	string m_tagWheelChair;
};

