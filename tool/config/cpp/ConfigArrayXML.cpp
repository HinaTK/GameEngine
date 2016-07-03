bool Init()
{
	std::string file ="ConfigArrayXML.xml";
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL) return false;
		struct Www _www;
		struct Ttt _ttt;
		TiXmlElement* wwwElement = NULL;
		TiXmlElement* tttElement = NULL;
		TiXmlElement* curElement = rootElement->FirstChildElement("row");
		while (curElement != NULL)
		{
			if (!GetSubNodeValue(curElement, "group", info.group, err) ||
				!GetSubNodeValue(curElement, "talent_id", info.talent_id, err) ||
				!GetSubNodeValue(curElement, "chance", info.chance, err) ||
				!GetSubNodeValue(curElement, "rate", info.rate, err))
			{
				ShowError(file.c_str(), err.c_str());
				return false;
			}

			wwwElement= curElement->FirstChildElement("www");
			if (wwwElement == NULL){ShowError(file.c_str(), "www"); return false;}
			wwwElement = wwwElement->FirstChildElement("value");
			while (wwwElement != NULL)
			{
				info.www.push_back(_www);
				wwwElement = wwwElement->NextSiblingElement("value");
			}

			tttElement= curElement->FirstChildElement("ttt");
			if (tttElement == NULL){ShowError(file.c_str(), "ttt"); return false;}
			tttElement = tttElement->FirstChildElement("value");
			while (tttElement != NULL)
			{
				info.ttt.push_back(_ttt);
				tttElement = tttElement->NextSiblingElement("value");
			}
			curElement = curElement->NextSiblingElement("row");
		}
	}
	else
	{
		ShowError(file.c_str(), "can not load the file");
		return false;
	}
	return true;
}