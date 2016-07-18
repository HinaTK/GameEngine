
#ifndef TEST_JSON_H
#define TEST_JSON_H

#include <iostream>
#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include "lib/include/rapidjson/define.h"
#include "lib/include/mysql/field.h"

namespace TestJson
{
#define TEST_TIME 100000
	using namespace rapidjson;
	using namespace std;

// 	void Test4()
// 	{
// 		rapidjson::Document document;
// 		document.SetObject();
// 		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
// 
// 		rapidjson::Value array(rapidjson::kArrayType);
// 
// 		for (int i = 0; i < 10; i++)
// 		{
// 			rapidjson::Value object(rapidjson::kObjectType);
// // 			object.AddMember("id", 1, allocator);
// // 			object.AddMember("name", "test", allocator);
// // 			object.AddMember("version", 1.01, allocator);
// // 			object.AddMember("vip", true, allocator);
// 
// 			object.SetInt(i);
// 			array.PushBack(object, allocator);
// 		}
// 
// 		document.AddMember("title", "PLAYER INFO", allocator);
// 		document.AddMember("players", array, allocator);
// 
// 		rapidjson::StringBuffer buffer;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// //		document.Accept(writer);
// 		auto out = buffer.GetString();
// 	}
// 
// 
// 	void Test5()
// 	{
// 		StringBuffer s;
// 		Writer<StringBuffer> writer(s);
// 
// 		writer.StartObject();               // Between StartObject()/EndObject(), 
// 		writer.Key("hello");                // output a key,
// 		writer.String("world");             // follow by a value.
// 		writer.Key("t");
// 		writer.Bool(true);
// 		writer.Key("f");
// 		writer.Bool(false);
// 		writer.Key("n");
// 		writer.Null();
// 		writer.Key("i");
// 		writer.Uint(123);
// 		writer.Key("pi");
// 		writer.Double(3.1416);
// 		writer.Key("a");
// 		writer.StartArray();                // Between StartArray()/EndArray(),
// 		for (unsigned i = 0; i < 4; i++)
// 			writer.Uint(i);                 // all values are elements of the array.
// 		writer.EndArray();
// 		writer.EndObject();
// 
// 		// {"hello":"world","t":true,"f":false,"n":null,"i":123,"pi":3.1416,"a":[0,1,2,3]}
// 		cout << s.GetString() << endl;
// 	}
// 
// 	struct Item
// 	{
// 		int id = 0;
// 		int level = 1;
// 	};
// 
// 	struct Item2
// 	{
// 		int level = 1;
// 		int star = 0;
// 	};
// 
// 	class Data : public Model
// 	{
// 	public:
// 		static const unsigned short DATA_VER = 0;
// 		Data(): Model(DATA_VER){}
// 		~Data(){}
// 
// 
// 		int item_id;
// 		int item_num;
// 		std::set<int> item_list;
// 		std::vector<Item> item_list2;
// 
// 		typedef std::map<int, Item2> DataMap;
// 		DataMap item_list3;
// 	};
// 
// 	void DataInit(Data &data)
// 	{
// 		data.item_id = 111;
// 		data.item_list.insert(3);
// 		data.item_list.insert(5);
// 
// 		Item item1;
// 		item1.id = 6; item1.level = 7;
// 		data.item_list2.push_back(item1);
// 		item1.id = 8; item1.level = 9;
// 		data.item_list2.push_back(item1);
// 
// 		Item2 item2;
// 		item2.level = 2; item2.star = 3;
// 		data.item_list3[1] = item2;
// 		item2.level = 4; item2.star = 5;
// 		data.item_list3[2] = item2;
// 	}
// 
// 	void Test6()
// 	{
// 		Data data;
// 		DataInit(data);
// 
// 		StringBuffer s;
// 		Writer<StringBuffer> writer(s);
// 		const StringBuffer::Ch *ret;
// 
// 		unsigned long begin = GetTickCount();
// 		for (int i = 0; i < TEST_TIME; ++i)
// 		{
// 			writer.StartObject();
// 
// 			writer.Key("ver");
// 			writer.Int(data.ver);
// 
// 			writer.Key("base");
// 			writer.StartArray();                // Between StartArray()/EndArray(),
// 			JsonWrite(writer, data.item_id);
// 			JsonWrite(writer, data.item_num);
// 			writer.EndArray();
// 
// 			writer.Key("item_list");
// 			writer.StartArray();
// 			for (std::set<int>::iterator itr = data.item_list.begin(); itr != data.item_list.end(); ++itr)
// 			{
// 				JsonWrite(writer, *itr);
// 			}
// 			writer.EndArray();
// 
// 			writer.Key("item_list2");
// 			writer.StartArray();
// 			for (std::vector<Item>::iterator itr = data.item_list2.begin(); itr != data.item_list2.end(); ++itr)
// 			{
// 				writer.StartArray();
// 				JsonWrite(writer, itr->id);
// 				JsonWrite(writer, itr->level);
// 				writer.EndArray();
// 			}
// 			writer.EndArray();
// 
// 			writer.Key("item_list3");
// 			writer.StartArray();
// 			for (Data::DataMap::iterator itr = data.item_list3.begin(); itr != data.item_list3.end(); ++itr)
// 			{
// 				writer.StartArray();
// 				JsonWrite(writer, itr->first);
// 				JsonWrite(writer, itr->second.level);
// 				JsonWrite(writer, itr->second.star);
// 				writer.EndArray();
// 			}
// 			writer.EndArray();
// 
// 			writer.EndObject();
// 
// 			ret = s.GetString();
// 			writer.Reset(s);
// 		}
// 
// 		cout << GetTickCount() - begin << " ms" << endl;
// 
// // 		Document doc;
// // 		if (doc.ParseInsitu((StringBuffer::Ch *)ret).HasParseError())
// // 		{
// // 			cout << doc.GetParseError() << endl;
// // 			cout << doc.GetErrorOffset() << endl;
// // 			return;
// // 		}
// // 
// // 		//doc.Parse<'4'>(updateInfo.c_str());
// // 
// // 		if (doc.IsObject())
// // 		{
// // 			if (doc.HasMember("base") && doc["base"].IsArray())
// // 			{
// // 				Value &dataArray = doc["base"];
// // 				for (unsigned int i = 0; i < dataArray.Size(); i++)
// // 				{
// // 					const Value& object = dataArray[i];
// // 
// // 					if (object["url"].IsDouble())
// // 					{
// // 						double url = object["url"].GetDouble();
// // 					}
// // 					else if (object["url"].IsString())
// // 					{
// // 						string url = object["url"].GetString();
// // 					}
// // 
// // 					string platform = object["platform"].GetString();
// // 				}
// // 			}
// // 			if (doc.HasMember("jjj") && doc["jjj"].IsArray())
// // 			{
// // 				Value &dataArray = doc["jjj"];
// // 				if (dataArray[0].IsInt())
// // 				{
// // 					int a = dataArray[0].GetInt();
// // 				}
// // 
// // 
// // 				int b = dataArray[1].GetInt();
// // 				int c = dataArray[2].GetInt();
// // 			}
// // 		}
// 	}

// 	void Test7()
// 	{
// 		struct MyHandler {
// 			bool Null() { cout << "Null()" << endl; return true; }
// 			bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
// 			bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
// 			bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
// 			bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
// 			bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
// 			bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
// 			bool RawNumber(const char* str, SizeType length, bool copy) {
// 				cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
// 				return true;
// 			}
// 			bool String(const char* str, SizeType length, bool copy) {
// 				cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
// 				return true;
// 			}
// 			bool StartObject() { cout << "StartObject()" << endl; return true; }
// 			bool Key(const char* str, SizeType length, bool copy) {
// 				cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
// 				return true;
// 			}
// 			bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
// 			bool StartArray() { cout << "StartArray()" << endl; return true; }
// 			bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
// 		};
// 
// 		const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 5, 4, 6], \"jia\":[[1,2],[3,4]] } ";
// 
// 		MyHandler handler;
// 		Reader reader;
// 		StringStream ss(json);
// 		reader.Parse(ss, handler);
// 	}
// 
// 	void Test8()
// 	{
// 		string updateInfo = "{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\",\"point\":112233}]}";
// 
// 		Document doc;
// 		doc.Parse<'4'>(updateInfo.c_str());
// 
// 		Value &dataArray = doc["UpdateInfo"];
// 
// 		if (dataArray.IsArray())
// 		{
// 			for (unsigned int i = 0; i < dataArray.Size(); i++)
// 			{
// 				const Value& object = dataArray[i];
// 
// 				if (object["url"].IsDouble())
// 				{
// 					double url = object["url"].GetDouble();
// 				}
// 				else if (object["url"].IsString())
// 				{
// 					string url = object["url"].GetString();
// 				}
// 				
// 				string platform = object["platform"].GetString();
// 			}
// 		}
// 	}
// 
// 	void Test9()
// 	{
// 		char updateInfo[] = "{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\",\"point\":112233}],\"jjj\":[2,4,6]}";
// 
// 		Document doc;
// 		if (doc.ParseInsitu(updateInfo).HasParseError())
// 		{
// 			cout << doc.GetParseError() << endl;
// 			cout << doc.GetErrorOffset() << endl;
// 			return;
// 		}
// 			
// 		//doc.Parse<'4'>(updateInfo.c_str());
// 
// 		if (doc.IsObject())
// 		{
// 			if (doc.HasMember("UpdateInfo") && doc["UpdateInfo"].IsArray())
// 			{
// 				Value &dataArray = doc["UpdateInfo"];
// 				for (unsigned int i = 0; i < dataArray.Size(); i++)
// 				{
// 					const Value& object = dataArray[i];
// 
// 					if (object["url"].IsDouble())
// 					{
// 						double url = object["url"].GetDouble();
// 					}
// 					else if (object["url"].IsString())
// 					{
// 						string url = object["url"].GetString();
// 					}
// 
// 					string platform = object["platform"].GetString();
// 				}
// 			}
// 			if (doc.HasMember("jjj") && doc["jjj"].IsArray())
// 			{
// 				Value &dataArray = doc["jjj"];
// 				if (dataArray[0].IsInt())
// 				{
// 					int a = dataArray[0].GetInt();
// 				}
// 				
// 				
// 				int b = dataArray[1].GetInt();
// 				int c = dataArray[2].GetInt();
// 			}
// 
// 		}
// 	}
// 
// 	class TTTT :public Field<TestJson::Data>
// 	{
// 	public:
// 		TTTT() :Field("tttt"){}
// 		~TTTT(){}
// 
// 		void Serialize(TestJson::Data &data)
// 		{
// 			m_writer.StartObject();
// 			WriteVer(data);
// 
// 			JSON_WRITE_BASE_ARRAY_BEGIN(m_writer, FIELD_BASE_NAME);
// 			JsonWrite(m_writer, data.item_id);
// 			JsonWrite(m_writer, data.item_num);
// 			JSON_WRITE_BASE_ARRAY_END(m_writer);
// 
// 			JSON_WRITE_ARRAY_INT_SET(m_writer, "item_list", data.item_list);
// 			
// 			JSON_WRITE_TWO_ARRAY_BEGIN(m_writer, "item_list2", data.item_list2, std::vector<Item>::iterator);
// 			JsonWrite(m_writer, itr->id);
// 			JsonWrite(m_writer, itr->level);
// 			JSON_WRITE_TWO_ARRAY_END(m_writer);
// 
// 			JSON_WRITE_TWO_ARRAY_BEGIN(m_writer, "item_list3", data.item_list3, Data::DataMap::iterator);
// 			JsonWrite(m_writer, itr->first);
// 			JsonWrite(m_writer, itr->second.level);
// 			JsonWrite(m_writer, itr->second.star);
// 			JSON_WRITE_TWO_ARRAY_END(m_writer);
// 			m_writer.EndObject();
// 
// 			auto ret = m_s.GetString();
// 		}
// 
// 		void inline Serialize2(TestJson::Data &data, rapidjson::Writer<rapidjson::StringBuffer> &writer)
// 		{
// 			writer.StartObject();
// 			WriteVer2(writer, data);
// 
// 			JSON_WRITE_BASE_ARRAY_BEGIN(writer, FIELD_BASE_NAME);
// 			JsonWrite(writer, data.item_id);
// 			JsonWrite(writer, data.item_num);
// 			JSON_WRITE_BASE_ARRAY_END(writer);
// 
// 			JSON_WRITE_ARRAY_INT_SET(writer, "item_list", data.item_list);
// 
// 			JSON_WRITE_TWO_ARRAY_BEGIN(writer, "item_list2", data.item_list2, std::vector<Item>::iterator);
// 			JsonWrite(writer, itr->id);
// 			JsonWrite(writer, itr->level);
// 			JSON_WRITE_TWO_ARRAY_END(writer);
// 
// 			JSON_WRITE_TWO_ARRAY_BEGIN(writer, "item_list3", data.item_list3, Data::DataMap::iterator);
// 			JsonWrite(writer, itr->first);
// 			JsonWrite(writer, itr->second.level);
// 			JsonWrite(writer, itr->second.star);
// 			JSON_WRITE_TWO_ARRAY_END(writer);
// 			writer.EndObject();
// 
// 		}
// 
// 		bool Deserialize(StringBuffer::Ch *str, Data &data)
// 		{
// 			JSON_BASIC_CHECK(str);
// 
// 			Version ver = 0;
// 			if (!ReadVer(doc, ver)) return false;
// 			
// 			JSON_READ_BASE_ARRAY_BEGIN(FIELD_BASE_NAME);
// 			JSON_READ_ARRAY_INT(array, 0, data.item_id);
// 			JSON_READ_ARRAY_INT(array, 1, data.item_num);
// 			JSON_READ_BASE_ARRAY_END();
// 
// 			JSON_READ_ARRAY_INT_SET("item_list", data.item_list);
// 
// 			JSON_READ_TWO_ARRAY_BEGIN("item_list2");
// 			Item item;
// 			JSON_READ_ARRAY_INT(sub, 0, item.id);
// 			JSON_READ_ARRAY_INT(sub, 1, item.level);
// 			data.item_list2.push_back(item);
// 			JSON_READ_TWO_ARRAY_END();
// 
// 			JSON_READ_TWO_ARRAY_BEGIN("item_list3");
// 			int key = 0;
// 			Item2 item2;
// 			JSON_READ_ARRAY_INT(sub, 0, key);
// 			JSON_READ_ARRAY_INT(sub, 1, item2.level);
// 			JSON_READ_ARRAY_INT(sub, 2, item2.star);
// 			data.item_list3[key] = item2;
// 			JSON_READ_TWO_ARRAY_END();
// 
// 			return true;
// 		}
// 	};
// 
// 	void Test10()
// 	{
// 		TTTT t;
// 		Data data;
// 		DataInit(data);
// 		t.Serialize(data);
// 		char *dd = "{\"ver\":0,\"base\":[111,0],\"item_list\":[3,5],\"item_list2\":[[6,7],[8,9]],\"item_list3\":[[1,2,3],[2,4,5]]}";
// 		Data data2;
// 		t.Deserialize(dd, data2);
// 	}
// 
// 	void Test11()
// 	{
// 		// http://www.oschina.net/code/snippet_566882_18509
// 	}
// 
// 	void Test12()
// 	{
// 		//rapidjson::Document::AllocatorType allocator;
// 		//rapidjson::StringBuffer sb(&allocator);
// 		
// 		Data data;
// 		DataInit(data);
// 
// 		rapidjson::StringBuffer s;
// 		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
// 		const StringBuffer::Ch *ret;
// 
// 		unsigned long begin = GetTickCount();
// 		
// 		TTTT t;
// 		for (int i = 0; i < TEST_TIME; ++i)
// 		{
// 			t.Serialize2(data, writer);
// 			ret = s.GetString();
// 			writer.Reset(s);
// 		}
// 		cout << GetTickCount() - begin << " ms" << endl;
// 	}
// 
// 	void Test13()
// 	{
// 		Data data;
// 		DataInit(data);
// 		unsigned long begin = GetTickCount();
// 		for (int i = 0; i < TEST_TIME; ++i)
// 		{
// 			TTTT t;
// 			t.Serialize(data);
// 		}
// 		cout << GetTickCount() - begin << " ms" << endl;
// 
// 	}
}


#endif // !TEST_JSON_H
