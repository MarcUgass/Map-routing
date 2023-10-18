#pragma once
#include "MapaBase.h"
#include "CamiSolucio.h"
#include "Util.h"
#include "PuntDeInteresBase.h"
#include "BallTree.h"
#include "GrafSolucio.h"

class MapaSolucio : public MapaBase, public CamiSolucio
{
public:
	void getPdis(std::vector<PuntDeInteresBase*>& pids);
	void getCamins(std::vector<CamiBase*>& camins);
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements);
	CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a);

	int TrobarIndex(const Coordinate coordinate, vector<Coordinate> c);

private:
	vector<PuntDeInteresBase*> m_pdis;
	vector<CamiBase*> m_camins;
	GrafSolucio* m_graf;
};

