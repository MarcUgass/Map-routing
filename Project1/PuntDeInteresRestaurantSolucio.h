#pragma once
#include "PuntDeInteresBase.h"
using namespace std;

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() { m_amenity = "", m_cuisine = "", m_wheelchair = ""; }
	~PuntDeInteresRestaurantSolucio() {}
	PuntDeInteresRestaurantSolucio(const Coordinate& c, const string& name, const string& amenity, const string cuisine, const string& wheelChair) : PuntDeInteresBase(c, name) { m_amenity = amenity, m_cuisine = cuisine, m_wheelchair = wheelChair; }

	unsigned int getColor();
	void setAmenity(const string amenity) { m_amenity = amenity; }
	void setCuisine(const string cuisine) { m_cuisine = cuisine; }
	void setWheelChair(const string wc) { m_wheelchair = wc; }

private:
	string m_amenity;
	string m_cuisine;
	string m_wheelchair;
};

