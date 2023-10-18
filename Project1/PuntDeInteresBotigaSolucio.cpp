#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	if (m_tagShop == "supermarket")
	{
		return 0xA5BE00;
	}
	else if (m_tagShop == "tobacco")
	{
		return 0xFFAD69;
	}
	else if (m_tagShop == "bakery")
	{
		return 0xE85D75;
	}
	else if (m_tagShop == "bakery" && (m_tagOpeningHours == "Div 06:00-22:00" || m_tagOpeningHours == "Dill 06:00-22:00") && m_tagWheelChair == "yes")
	{
		return 0x4CB944;
	}
	else
		return 0xEFD6AC;

}