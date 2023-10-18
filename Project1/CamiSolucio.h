#pragma once

#include <Algorithm>
#include "CamiBase.h"

using namespace std;

class CamiSolucio : public CamiBase
{
public:
	CamiSolucio() { m_highway = ""; }
	~CamiSolucio() {}
	vector<Coordinate> getCamiCoords() { 
		vector<Coordinate> temp = m_cami;
		reverse(temp.begin(), temp.end());
		return temp; 
	}
	void addCoord(const Coordinate coord) { m_cami.push_back(coord); }
	void setCami(vector<Coordinate> coords) { m_cami = coords; }
	void setHighway(const string hw) { m_highway = hw; }

private:
	vector<Coordinate> m_cami;
	string m_highway;
};

