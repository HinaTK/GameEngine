
#ifndef LIB_TINYXML_H
#define LIB_TINYXML_H

#include <string>
#include <sstream>
#include "tinyxml/tinyxml.h"

// 将字符串转成基础数据类型,非基础类型需显示定义
template<class T>
bool StringToBaseType(const std::string& str, T& val)
{
	std::istringstream stream;
	stream.str(str);
	if (stream>>val)
	{
		return true;
	}
	return false;
}

// 将基础数据类型转成字符串,非基础类型需显示定义
template<class T>
bool BaseTypeToString(const T& src, std::string &tar)
{
	std::ostringstream stream;
	if (stream<<src)
	{
		tar = stream.str();
		return true;
	}
	return false;
}

template<class T>
static bool GetSubNodeValue(TiXmlElement *element, const std::string &name, T &val, std::string &err)
{
	if (!element) return false;
	TiXmlElement *TmpElement = element->FirstChildElement(name.c_str());
	if (!GetNodeValue(TmpElement, val))
	{
		err = name;
		return false;
	}
	return true;
}
template<class T>
static bool SetSubNodeValue(TiXmlElement *element, const std::string& name, T& val)
{
	if (!element) return false;
	TiXmlElement *TmpElement = element->FirstChildElement(name.c_str());
	return SetNodeValue(TmpElement, val);
}

// 读写如下节点element的值,不支持形如<element/>的空值
// <element>s_val</element>
template<class T>
static bool GetNodeValue(TiXmlElement *element, T& val)
{
	if (!element || !element->FirstChild() || !StringToBaseType(element->GetText(), val))
	{
		return false;
	}
	return true;
}

static void ShowError(const char *file, const char *element)
{
	printf("read %s element %s error\n", file, element);
}
class ConfigElementBase
{
public:
	ConfigElementBase():m_element(0) {}
	virtual ~ConfigElementBase() {}

	void SetElement(TiXmlElement *element) { m_element = element; }

	// 供子类列表中获取偏移地址
	virtual ConfigElementBase* offset() = 0;
	// 将子节点读到相应成员数据中
	virtual bool read() = 0;
	// 将成员数据写入文件
	virtual bool write() = 0;

protected:
	// 获取子节点的值,不适用有多个同名子节点的情况
	template<class T>
	bool GetValue(const char *name, T* value)
	{
		if (m_element == 0) return false;
		return GetSubNodeValue(m_element, name, *value);
	}
	bool GetValue(const char *name, ConfigElementBase* value)
	{
		if (m_element == 0) return false;
		value->SetElement(m_element->FirstChildElement(name));
		return value->read();
	}

	// 获取子节点的值,适用有多个同名子节点的情况,与数组对应
	template<class T>
	bool GetListValue(const char *name, T* list_value, int& list_len, int list_max_len)
	{
		list_len = 0;
		if (m_element == 0)
		{
			return false;
		}
		TiXmlElement *tmp_element = m_element->FirstChildElement(name);
		for ( ;list_len < list_max_len && tmp_element != 0; ++list_len, ++list_value, tmp_element = tmp_element->NextSiblingElement(name))
		{
			if (!GetNodeValue(tmp_element, *list_value)) return false;
		}
		return true;
	}
	bool GetListValue(const char *name, ConfigElementBase* list_value, int& list_len, int list_max_len)
	{
		list_len = 0;
		if (m_element == 0)
		{
			return false;
		}
		TiXmlElement *tmp_element = m_element->FirstChildElement(name);
		for ( ;list_len < list_max_len && tmp_element != 0; ++list_len)
		{
			list_value->SetElement(tmp_element);
			if (!list_value->read())return false;
			list_value = list_value->offset();
			tmp_element = tmp_element->NextSiblingElement(name);
		}
		return true;
	}

	// 设置子节点的值,不适用有多个同名子节点的情况
	template<class T>
	bool SetValue(const char *name, T* value)
	{
		if (m_element == 0) return false;

		TiXmlElement * tmp_element = m_element->FirstChildElement(name);
		if (!tmp_element)
		{
			TiXmlElement insert_node(name);
			tmp_element = (TiXmlElement *)m_element->InsertEndChild(insert_node);
		}
		if (!tmp_element->FirstChild())
		{
			std::string tmp_value;
			BaseTypeToString(*value, tmp_value);
			TiXmlText sub_node(tmp_value);
			tmp_element->InsertEndChild(sub_node);
			return true;
		}
		return SetSubNodeValue(m_element, name, *value);
	}
	bool SetValue(const char *name, ConfigElementBase* value)
	{
		if (m_element == 0) return false;
		TiXmlElement * tmp_element = m_element->FirstChildElement(name);
		if (!tmp_element)
		{
			TiXmlElement insert_node(name);
			m_element->InsertEndChild(insert_node);
			tmp_element = m_element->FirstChildElement(name);
		}
		value->SetElement(tmp_element);
		return value->write();
	}

	// 设置子节点的值,适用有多个同名子节点的情况,与数组对应
	template<class T>
	bool SetListValue(const char *name, T* list_value, int list_len)
	{
		if (m_element == 0 || list_len < 0)
		{
			return false;
		}
		TiXmlElement *tmp_element = m_element->FirstChildElement(name);
		for(int i=0;i<list_len;++i,++list_value)
		{
			if (!tmp_element)
			{
				TiXmlElement insert_node(name);
				tmp_element = (TiXmlElement *)m_element->InsertEndChild(insert_node);
			}
			if (!tmp_element->FirstChild())
			{
				std::string tmp_value;
				BaseTypeToString(*list_value, tmp_value);
				TiXmlText sub_node(tmp_value);
				tmp_element->InsertEndChild(sub_node);
			}
			else
			{
				if (!SetNodeValue(tmp_element, *list_value)) return false;
			}
			tmp_element = tmp_element->NextSiblingElement(name);
		}
		while(tmp_element)
		{
			TiXmlElement *to_remove = tmp_element;
			tmp_element = tmp_element->NextSiblingElement(name);
			m_element->RemoveChild(to_remove);
		};
		return true;
	}
	bool SetListValue(const char *name, ConfigElementBase* list_value, int list_len)
	{
		if (m_element == 0 || list_len < 0)
		{
			return false;
		}
		TiXmlElement *tmp_element = m_element->FirstChildElement(name);
		for(int i=0;i<list_len;++i)
		{
			if (!tmp_element)
			{
				TiXmlElement insert_node(name);
				tmp_element = (TiXmlElement *)m_element->InsertEndChild(insert_node);
			}

			list_value->SetElement(tmp_element);
			if (!list_value->write()) return false;

			list_value= list_value->offset();
			tmp_element = tmp_element->NextSiblingElement(name);
		}
		while(tmp_element)
		{
			TiXmlElement *to_remove = tmp_element;
			tmp_element = tmp_element->NextSiblingElement(name);
			m_element->RemoveChild(to_remove);
		};
		return true;
	}


	// 至少有一个节点的xml结构
	TiXmlElement *m_element;

private:
};

#endif

