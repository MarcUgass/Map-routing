#pragma once
#ifndef _BALL_
#define _BALL_

#include "Util.h"
#include <vector>
#include <list>

using namespace std;

class BallTree {
public:
	BallTree();

	BallTree(const vector<Coordinate>& datapoints);
	~BallTree() {}
	void construirArbre(const vector<Coordinate>& datapoints);

	

	void inOrdre(vector<list<Coordinate>>& out);
	void inOrdreRec(BallTree* root, vector<list<Coordinate>>& out);

	void postOrdre(vector<list<Coordinate>>& out);
	void postOrdreRec(BallTree* root, vector<list<Coordinate>>& out);

	void preOrdre(vector<list<Coordinate>>& out);
	void preOrdreRec(BallTree* root, vector<list<Coordinate>>& out);

	Coordinate nodeMesProper(Coordinate targetQuery, Coordinate& Q, BallTree* ball);

	void puntC();

	void calculaDistanciesC(vector<double>& distancies);

	int puntMesLlunya(const vector<double> distancies);

	void calculaDistanciesA(vector<double>& distancies, const Coordinate& puntA);
	
	BallTree* getArrel() { return m_root; }

	Coordinate getPivot() {return m_pivot;}

	double getRadi() {return m_radi;}

	BallTree* getEsquerre() {return m_right;}

	BallTree* getDreta() {return m_left;}

	std::vector<Coordinate>& getCoordenades() {return m_coordenades;}

	void setPivot(Coordinate pivot) {m_pivot = pivot;}

	void setRadius(double radi) {m_radi = radi;}

	void setEsquerre(BallTree* right) {m_right = right;}

	void setDreta(BallTree* left) {m_left = left;}

	void setCoordenades(std::vector<Coordinate>& coordenades) {m_coordenades = coordenades;}

private:
	BallTree* m_root;
	BallTree* m_left = nullptr;
	BallTree* m_right = nullptr;
	double m_radi;
	Coordinate m_pivot;
	std::vector<Coordinate> m_coordenades;
};

#endif // !_BALL_
