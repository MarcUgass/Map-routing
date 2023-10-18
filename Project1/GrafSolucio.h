#pragma once
#include "CamiBase.h"
#include "CamiSolucio.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class GrafSolucio
{
public:
	GrafSolucio(vector<CamiBase*> c);
	~GrafSolucio() {};
	GrafSolucio() { m_numNodes = 0; m_numArestes = 0; }
	void afegirNode(const Coordinate node);
	void afegirAresta(const int pos1, const int pos2);
	int cerca(const Coordinate coord, const vector<Coordinate> nodes);
	bool TrobarIndex(vector<Coordinate> c, const Coordinate& coordinate);
	void camiMesCurt(Coordinate node1, Coordinate node2, CamiBase* camiSolucio);
	void dijkstra(int node, int node2, vector<float>& dist, vector<int>& anterior);
	int distMin(vector<float>& dist, vector<bool>& visitat);
private:
	vector<list<pair<int, float>>> m_veins;
	vector<Coordinate> m_nodes;
	int m_numNodes;
	int m_numArestes;
	const int distMax = 789423897;
};

