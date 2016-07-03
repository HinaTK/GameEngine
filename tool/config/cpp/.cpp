bool Init()
{
	std::string file ="aaa.xml";	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(file.c_str()))
{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL) return false;
		TiXmlElement* curElement = rootElement->FirstChildElement("value");
		if (curElement == NULL){ShowError(file.c_str(), "value"); return false;}
		curElement = curElement->FirstChildElement("block");
		while (curElement != NULL)
		{
		)			{ShowError(file.c_str(), err.c_str());}return true;
}