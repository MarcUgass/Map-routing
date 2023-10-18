#include "pch.h"
#include "MapaSolucio.h"
#include "PuntDeInteresBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"


using namespace std;

void MapaSolucio::getPdis(vector<PuntDeInteresBase*>& pdis)
{
	for (vector<PuntDeInteresBase*>::iterator it = m_pdis.begin(); it != m_pdis.end(); it++)
		pdis.push_back(*it);
}

void MapaSolucio::getCamins(vector<CamiBase*>& camins)
{
	for (vector<CamiBase*>::iterator it = m_camins.begin(); it != m_camins.end(); it++)
		camins.push_back(*it);
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements) {
	if (!m_camins.empty())
		m_camins.clear();

	if (!m_pdis.empty())
		m_pdis.clear();

	vector<pair<string, Coordinate>> refs;
	for (vector<XmlElement>::iterator it = xmlElements.begin(); it != xmlElements.end(); it++) 
	{
		double lat = 0, lon = 0;
		if ((*it).id_element == "node") 
		{
			//Distingir si el node es un restaurant o una botiga
			int type = 0;
			for (int i = 0; i < (*it).fills.size(); i++) 
			{
				if ((*it).fills[i].first == "tag") 
				{
					std::pair<std::string, std::string> valorTag = Util::kvDeTag((*it).fills[i].second);
					if (valorTag.second == "restaurant" || valorTag.second == "cafe")
						type = 1;
				
					else if (valorTag.first == "shop") 
						type = 2;
				}
			}
			///////////////////////////////////////////////////
			switch (type) {
			case 1:
			{
				Coordinate c;
				string name;
				string cuisine;
				string wheelchair;
				string amenity;
				for (int i = 0; i < (*it).atributs.size(); i++) {
					// Iterem fins trobar el atribut que ens interessa
					// En el cas del node, guardar les coordenades a pdis
					if ((*it).atributs[i].first == "lat") {
						lat = stod((*it).atributs[i].second);
					}
					if ((*it).atributs[i].first == "lon") {
						lon = stod((*it).atributs[i].second);
					}
					c.lat = lat;
					c.lon = lon;
				}
				for (int i = 0; i < (*it).fills.size(); i++) {
					// Iterem i avaluem tots els fills que son tags
					if ((*it).fills[i].first == "tag") {
						// Emmagatzemem el valor d’aquest tag
						std::pair<std::string, std::string> valorTag = Util::kvDeTag((*it).fills[i].second);
						// Comprovem que es el tag que busquem
						if (valorTag.first == "name") {
							name = valorTag.second;
						}
						else if (valorTag.first == "amenity") {
							amenity = valorTag.second;
						}
						else if (valorTag.first == "cuisine") {
							cuisine = valorTag.second;
						}
						else if (valorTag.first == "wheelchair") {
							wheelchair = valorTag.second;
						}
					}

				}
				if (name != "") {
					PuntDeInteresRestaurantSolucio* pdiR;
					pdiR = new PuntDeInteresRestaurantSolucio(c, name, amenity, cuisine, wheelchair);

					m_pdis.push_back(pdiR);
				}

				break;
			}
			case 2:
			{
				bool isNode = false;
				Coordinate c;
				string name;
				string shop;
				string wheelchair;
				string opening_hours;
				for (int i = 0; i < (*it).atributs.size(); i++) {
					// Iterem fins trobar el atribut que ens interessa
					// En el cas del node, guardar les coordenades a pdis
					if ((*it).atributs[i].first == "lat") {
						lat = stod((*it).atributs[i].second);
					}
					if ((*it).atributs[i].first == "lon") {
						lon = stod((*it).atributs[i].second);
					}
					c.lat = lat;
					c.lon = lon;
				}
				for (int i = 0; i < (*it).fills.size(); i++) {
					// Iterem i avaluem tots els fills que son tags
					if ((*it).fills[i].first == "tag") {
						isNode = true;
						// Emmagatzemem el valor d’aquest tag
						std::pair<std::string, std::string> valorTag = Util::kvDeTag((*it).fills[i].second);
						// Comprovem que es el tag que busquem
						if (valorTag.first == "name") {
							name = valorTag.second;
						}
						else if (valorTag.first == "shop") {
							shop = valorTag.second;
						}
						else if (valorTag.first == "wheelchair") {
							wheelchair = valorTag.second;
						}
						else if (valorTag.first == "opening_hours") {
							opening_hours = valorTag.second;
						}
					}

				}
				if (isNode) {
					if (name != "") {
						PuntDeInteresBotigaSolucio* pdiB;
						pdiB = new PuntDeInteresBotigaSolucio(c, name, shop, opening_hours, wheelchair);

						m_pdis.push_back(pdiB);
					}
				}
				break;
			}
			default:
				Coordinate c;
				string id;
				for (int i = 0; i < (*it).atributs.size(); i++) {
					// Iterem fins trobar el atribut que ens interessa
					// En el cas del node, guardar les coordenades a pdis
					if ((*it).atributs[i].first == "id") {
						id = (*it).atributs[i].second;
					}
					if ((*it).atributs[i].first == "lat") {
						lat = stod((*it).atributs[i].second);
					}
					if ((*it).atributs[i].first == "lon") {
						lon = stod((*it).atributs[i].second);
					}
					c.lat = lat;
					c.lon = lon;
				}
				//vector<pair<string, vector<Coordinate>>> refs;
				bool isIn = false;
				for (vector<pair<string, Coordinate>>::iterator ite = refs.begin(); ite != refs.end(); ite++) {
					if ((*ite).first == id) {
						isIn = true;
					}
				}
				if (!isIn) {
					pair<string, Coordinate> ref;
					ref.first = id;
					ref.second = c;
					refs.push_back(ref);
				}

				break;
			}
		}
		bool isHighway = false;
		if ((*it).id_element == "way") {
			CamiSolucio* cs;
			cs = new CamiSolucio;
			vector<Coordinate> resultat;
			for (int i = 0; i < (*it).fills.size(); i++) {
				// Iterem i avaluem tots els fills que son tags

				if ((*it).fills[i].first == "nd") {
					for (vector<pair<string, Coordinate>>::iterator ite = refs.begin(); ite != refs.end(); ite++) {

						if ((*it).fills[i].second[0].second == (*ite).first) {
							//if ((find(refs.begin(), refs.end(), (*ite).first)) != refs.end()) {
							resultat.push_back((*ite).second);
							//}
						}
					}
				}
				if ((*it).fills[i].first == "tag") {
					// Emmagatzemem el valor d’aquest node
					std::pair<std::string, std::string> valorTag =
						Util::kvDeTag((*it).fills[i].second);

					if (valorTag.first == "highway") {
						cs->setHighway(valorTag.second);
						isHighway = true;
						/*......................*/
					}
				}
			}
			if (isHighway) {
				cs->setCami(resultat);
				m_camins.push_back(cs);

			}
		}
	}
}

CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) {
	Coordinate nodeDesde, nodeFins;
	vector<Coordinate> dataPoints;
	vector<CamiBase*>::iterator it = m_camins.begin();

	for (it; it != m_camins.end(); it++) {
		vector<Coordinate> cami = (*it)->getCamiCoords();
		vector<Coordinate>::iterator it2 = cami.begin();
		for (it2; it2 != cami.end(); it2++) {
			if (TrobarIndex((*it2), dataPoints) == -1)
				dataPoints.push_back(*it2);
		}
	}

	BallTree* bt = new BallTree(dataPoints);

	bt->nodeMesProper(desde->getCoord(), nodeDesde, bt);
	bt->nodeMesProper(a->getCoord(), nodeFins, bt);

	if (!m_camins.empty())
		m_graf = new GrafSolucio(m_camins);

	Util::escriuEnMonitor("Calculant ruta més curta...");

	CamiBase* mesCurt = new CamiSolucio;
	m_graf->camiMesCurt(nodeDesde, nodeFins, mesCurt);

	if (mesCurt != nullptr)
		Util::escriuEnMonitor("Calculant ruta més curta calculada correctament");
	else
		Util::escriuEnMonitor("Error");

	return mesCurt;
}

int MapaSolucio::TrobarIndex(const Coordinate coordinate, vector<Coordinate> c)
{
	bool trobat = false;
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i].lat == coordinate.lat && c[i].lon == coordinate.lon)
			return i;
	}

	return -1;
}