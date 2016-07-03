struct ConfigArrayXMLKey
{
	int group;
	int talent_id;
	bool operator < (const ConfigArrayXMLKey &key) const
	{
		if (group < key.group ) return true;
		if (group == key.group ) return talent_id < key.talent_id;
	return false;
	};
};
struct ConfigArrayXML
{
	int chance;
	std::vector<Www> www;
	std::vector<Ttt> ttt;
	int rate;
};
std::map<ConfigArrayXMLKey, ConfigArrayXML> m_ConfigArrayXML_map;