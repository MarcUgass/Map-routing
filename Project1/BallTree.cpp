#include "pch.h"
#include "BallTree.h"

using namespace std;

BallTree::BallTree()
{
	m_root = nullptr;
	m_left = nullptr;
	m_right = nullptr;
	m_radi = 0.001;
	m_pivot = Coordinate{ 0.0, 0.0 };
	
}

BallTree::BallTree(const vector<Coordinate>& datapoints)
{
	if (datapoints.size() == 1) {
		m_radi = 0;
		m_coordenades = datapoints;
		m_pivot = m_coordenades[0];
		return;
	}
	else {
		
		m_coordenades = datapoints;
		vector<double> distancies;
		m_pivot = Util::calcularPuntCentral(m_coordenades);
		calculaDistanciesC(distancies);
		Coordinate PuntA = m_coordenades[puntMesLlunya(distancies)];
		distancies.clear();
		calculaDistanciesA(distancies, PuntA);
		m_radi = distancies[puntMesLlunya(distancies)];
		Coordinate PuntB = m_coordenades[puntMesLlunya(distancies)];
		vector<Coordinate> datapointsL;
		vector<Coordinate> datapointsR;
		for (auto it = m_coordenades.begin(); it != m_coordenades.end(); it++) {
			double D1 = Util::DistanciaHaversine(PuntA, (*it));
			double D2 = Util::DistanciaHaversine(PuntB, (*it));
			if (D1 >= D2) {
				datapointsL.push_back(*it);
			}
			else if (D1 < D2) {
				datapointsR.push_back(*it);
			}
		}
		m_left = new BallTree(datapointsL);
		m_right = new BallTree(datapointsR);
	}
}

void BallTree::construirArbre(const vector<Coordinate>& datapoints) {
	m_root = new BallTree(datapoints);
}

void BallTree::inOrdre(vector<list<Coordinate>>& out) {
	if (m_root == nullptr) {
		return;
	}
	else {
		inOrdreRec(m_root, out);
	}
}

void BallTree::inOrdreRec(BallTree* root, vector<list<Coordinate>>& out) {
	if (root == nullptr) {
		return;
	}
	else {
		inOrdreRec(root->getEsquerre(), out);
		list<Coordinate> nodes;
		for (auto it = root->getCoordenades().begin(); it != root->getCoordenades().end(); it++)
			nodes.push_back(*it);
		out.push_back(nodes);
		nodes.clear();
		inOrdreRec(root->getDreta(), out);
	}
}

void BallTree::postOrdre(vector<list<Coordinate>>& out) {
	if (m_root == nullptr) {
		return;
	}
	else {
		postOrdreRec(m_root, out);
	}
}
void BallTree::postOrdreRec(BallTree* root, vector<list<Coordinate>>& out) {
	if (root == nullptr) {
		return;
	}
	else {
		postOrdreRec(root->getEsquerre(), out);
		postOrdreRec(root->getDreta(), out);

		list<Coordinate> nodes;
		for (auto it = root->getCoordenades().begin(); it != root->getCoordenades().end(); it++)
			nodes.push_back(*it);
		out.push_back(nodes);
		nodes.clear();
	}
}

void BallTree::preOrdre(vector<list<Coordinate>>& out) {
	if (m_root == nullptr) {
		return;
	}
	else {
		preOrdreRec(m_root, out);
	}
}
void BallTree::preOrdreRec(BallTree* root, vector<list<Coordinate>>& out) {
	if (root == nullptr) {
		return;
	}
	else {
		list<Coordinate> nodes;
		for (auto it = root->getCoordenades().begin(); it != root->getCoordenades().end(); it++)
			nodes.push_back(*it);
		out.push_back(nodes);
		nodes.clear();
		preOrdreRec(root->getEsquerre(), out);
		preOrdreRec(root->getDreta(), out);

	}
}


Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball) {
	double D1 = Util::DistanciaHaversine(targetQuery, ball->getPivot());
	double D2 = Util::DistanciaHaversine(Q, ball->getPivot());

	if (D1 - ball->getRadi() >= D2) {
		return Q;
	}
	else {
		if (ball->getDreta() == nullptr && ball->getEsquerre() == nullptr) {
			double distanciaActual = Util::DistanciaHaversine(targetQuery, Q);
			double distancia = Util::DistanciaHaversine(targetQuery, ball->getCoordenades()[0]);
			if (distancia < distanciaActual) {
				Q = ball->getCoordenades()[0];
			}
			return Q;
		}
		else {
			double Da = Util::DistanciaHaversine(targetQuery, ball->getDreta()->getPivot());
			double Db = Util::DistanciaHaversine(targetQuery, ball->getEsquerre()->getPivot());
			if (Da < Db) {
				nodeMesProper(targetQuery, Q, ball->getEsquerre());
				nodeMesProper(targetQuery, Q, ball->getDreta());
			}
			else if (Da >= Db) {
				nodeMesProper(targetQuery, Q, ball->getDreta());
				nodeMesProper(targetQuery, Q, ball->getEsquerre());
			}
		}
		return Q;
	}
}

void BallTree::puntC()
{
		m_pivot = Util::calcularPuntCentral(m_coordenades);
}

void BallTree::calculaDistanciesC(vector<double>& distancies)
{
	for (auto it = m_coordenades.begin(); it != m_coordenades.end(); it++) {
		distancies.push_back(Util::DistanciaHaversine(m_pivot, (*it)));
	}
}

int BallTree::puntMesLlunya(const vector<double> distancies)
{
	double max = distancies[0];
	int pos = 0;
	for (auto it = distancies.begin(); it != distancies.end(); it++) {
		if ((*it) > max) {
			max = (*it);
			pos = distance(distancies.begin(), it);
		}
	}
	return pos;
}

void BallTree::calculaDistanciesA(vector<double>& distancies, const Coordinate& puntA)
{
	for (auto it = m_coordenades.begin(); it != m_coordenades.end(); it++) {
		distancies.push_back(Util::DistanciaHaversine(puntA, (*it)));
	}
}
