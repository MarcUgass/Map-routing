#include "pch.h"
#include "GrafSolucio.h"
#include "Util.h"

GrafSolucio::GrafSolucio(vector<CamiBase*> c)
{
	m_numNodes = 0;
	m_numArestes = 0;
	for (int i = 0; i < c.size(); i++) {
		vector<Coordinate> cami = c[i]->getCamiCoords();
		if (!TrobarIndex(m_nodes, cami[0]))
			afegirNode(cami[0]);
		for (int j = 1; j < cami.size(); j++) {
			int ant = j - 1;
			if (!TrobarIndex(m_nodes, cami[j]))
			{
				afegirNode(cami[j]);
				int pos1 = cerca(cami[ant], m_nodes);
				int pos2 = cerca(cami[j], m_nodes);
				afegirAresta(pos1, pos2);
			}
			else {
				int pos1 = cerca(cami[ant], m_nodes);
				int pos2 = cerca(cami[j], m_nodes);

				afegirAresta(pos1, pos2);
			}
		}
	}
}

void GrafSolucio::afegirNode(const Coordinate node)
{
	m_numNodes++;
	m_nodes.push_back(node);
	m_veins.resize(m_numNodes);

}

void GrafSolucio::afegirAresta(const int posNode1, const int posNode2)
{
	if ((posNode1 < m_numNodes) && (posNode2 < m_numNodes) && (posNode1 >= 0) && (posNode2 >= 0))
	{
		double distancia = Util::DistanciaHaversine(m_nodes[posNode1], m_nodes[posNode2]);
		m_veins[posNode2].emplace_back(pair<int, float>(posNode1, distancia));
		m_veins[posNode1].emplace_back(pair<int, float>(posNode2, distancia));
		m_numArestes++;
	}
}

int GrafSolucio::cerca(const Coordinate coord, const vector<Coordinate> nodes) {
	int i = 0;
	bool trobat = false;
	while (i < nodes.size() && !trobat) {
		if (nodes[i].lat == coord.lat && nodes[i].lon == coord.lon)
			trobat = true;
		else
			i++;
	}
	if (trobat)
		return i;
	return 0;
}

bool GrafSolucio::TrobarIndex(vector<Coordinate> c, const Coordinate& coord)
{
	auto it = c.begin();
	while (it != c.end())
	{
		if ((*it).lat == coord.lat && (*it).lon == coord.lon)
			return true;
		it++;
	}
	return false;
}

void GrafSolucio::camiMesCurt(Coordinate node1, Coordinate node2, CamiBase* camiSolucio) {
	int pos1 = cerca(node1, m_nodes);
	int pos2 = cerca(node2, m_nodes);

	vector<int> anterior;
	vector<float> vDist;

	dijkstra(pos1, pos2, vDist, anterior);

	int it = pos2;
	
	camiSolucio->addCoord(node2);

	while (it != pos1) {
		camiSolucio->addCoord(m_nodes[anterior[it]]);
		it = anterior[it];
	}
}

void GrafSolucio::dijkstra(int node, int node2, vector<float>& dist, vector<int>& anterior) {
	vector<bool> visitat;
	dist.resize(m_numNodes, distMax);
	anterior.resize(m_numNodes, -1);
	visitat.resize(m_numNodes, false);
	dist[node] = 0;
	anterior[node] = node;
	for (int i = 0; i < m_numNodes - 1; i++) {
		int posVeiAct = distMin(dist, visitat);
		visitat[posVeiAct] = true;
		if (posVeiAct == node2) return;
		for (auto posVei = m_veins[posVeiAct].begin(); posVei != m_veins[posVeiAct].end(); posVei++) {
			if (!visitat[posVei->first]) {
				if (dist[posVeiAct] + posVei->second < dist[posVei->first]) {
					dist[posVei->first] = dist[posVeiAct] + posVei->second;
					anterior[posVei->first] = posVeiAct;
				}
			}
		}
	}
}

int GrafSolucio::distMin(vector<float>& dist, vector<bool>& visitat) {
	float min = abs(distMax), pos = -1;
	for (int posVei = 0; posVei < m_numNodes; posVei++) {
		if (!visitat[posVei] && dist[posVei] < min) {
			min = dist[posVei];
			pos = posVei;
		}
	}
	return pos;
}