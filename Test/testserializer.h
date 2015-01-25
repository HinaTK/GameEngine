
#ifndef TEST_SERIALIZER_H
#define TEST_SERIALIZER_H

#include <vector>
#include "libcommon/serializer.h"
#include "libcommon/dbserializer.h"
#ifdef WIN32
#include <windows.h>
#endif // WIN32


namespace TestSerializer
{
	class TestData
	{
	public:
		TestData(){};
		~TestData(){};

		bool		Serialize(Serializer &stream) const;
		bool		Unserialize(Serializer &stream);

		struct DataStruct
		{
			int a;
			short b;
			char c;
			char d;
			//int e[48];
		};


		DataStruct m_data_struct;
		typedef std::vector<int> VECTOR_TEST;
		typedef std::vector<std::string> VECTOR_NAME;

		VECTOR_TEST role_data;
		VECTOR_NAME role_name;
	};

	bool TestData::Serialize(Serializer &stream) const
	{
		//PUSH(stream, m_data_struct);
		stream.Push(m_data_struct);
		stream.Push(role_data.size());
		for (VECTOR_TEST::const_iterator itr = role_data.begin(); itr != role_data.end(); ++itr)
		{
			stream.Push((*itr));
		}

		stream.Push(role_name.size());
		for (VECTOR_NAME::const_iterator itr = role_name.begin(); itr != role_name.end(); ++itr)
		{
			stream.PushStr(itr->c_str(), itr->length() + 1);
		}
		return true;
	}

	bool TestData::Unserialize(Serializer &stream)
	{
		stream.Pop(m_data_struct);
		//POP(stream, m_data_struct);
		unsigned int size = 0;
		stream.Pop(size);
		int data = 0;
		for (unsigned int i = 0; i < size; ++i)
		{
			stream.Pop(data);
			role_data.push_back(data);
		}

		stream.Pop(size);
		char *str = 0;
		unsigned int length = 0;
		bool ret = false;
		for (unsigned int i = 0; i < size; ++i)
		{
			ret = stream.PopStr(&str, length);
			if (!ret)
			{
				return ret;
			}
			role_name.push_back(str);
		}
		return true;
	}

	typedef char GameName[32];		// ½ÇÉ«Ãû³Æ

	class TestDBSerialize
	{
	public:
		TestDBSerialize(){};
		~TestDBSerialize(){};

		bool		Serialize(DBSerializer &stream)
		{
			stream.Push(ROLE_ID, _ROLE_ID);
			stream.PushStr(ROLE_NAME, _ROLE_NAME);
			stream.Push(FRIENDS, _FRIENDS.size());
			for (std::vector<unsigned int>::iterator itr = _FRIENDS.begin(); itr != _FRIENDS.end(); ++itr)
			{
				stream.Push(FRIENDS, *itr);
			}
			return true;
		}
		bool		Unserialize(DBSerializer &stream)
		{
			const char *_name;
			unsigned int length = 0;
			unsigned int size = 0;
			stream.Pop(ROLE_ID, _ROLE_ID);
			stream.PopStr(ROLE_NAME, &_name, length);
			memcpy(_ROLE_NAME, _name, length);
			stream.Pop(FRIENDS, size);
			for (unsigned int i = 0; i < size; ++i)
			{
				unsigned int friend_id;
				stream.Pop(FRIENDS, friend_id);
				_FRIENDS.push_back(friend_id);
			}
			return true;
		}

		enum
		{
			ROLE_ID,
			ROLE_NAME,
			FRIENDS,
			MAX_FIELD
		};

		unsigned int _ROLE_ID;
		GameName	_ROLE_NAME;
		std::vector<unsigned int> _FRIENDS;
		

		TLV	data[MAX_FIELD];
	};

	
	void Normal()
	{
		TestData src_data;
		TestData des_data;

		src_data.m_data_struct.a = 11;
		src_data.m_data_struct.b = 22;
		src_data.m_data_struct.c = 33;
		src_data.m_data_struct.d = 44;

		src_data.role_data.push_back(55);
		src_data.role_data.push_back(66);

		src_data.role_name.push_back("xian");
		src_data.role_name.push_back("jia");
		src_data.role_name.push_back("ming");

		char data[1024] = { 0 };
		Serializer temp1(data, 1024);
		src_data.Serialize(temp1);

		Serializer temp2(data, 1024);
		des_data.Unserialize(temp2);


// 		char test_data[102400] = { 0 };
// 		int a = 123;
// 		unsigned int len = sizeof(src_data.m_data_struct);
// 		unsigned long begin = GetTickCount();
// 		for (int i = 0; i < 5000000; ++i)
// 		{
// 			memcpy(test_data, &src_data.m_data_struct, len);
// 		}
// 		printf("%d ms\n", GetTickCount() - begin);
// 		begin = GetTickCount();
// 		for (int i = 0; i < 5000000; ++i)
// 		{
// 			*(TestData::DataStruct *)test_data = src_data.m_data_struct;
// 		}
// 		printf("%d ms\n", GetTickCount() - begin);
	}

	void NormalDB()
	{
		TestDBSerialize src_data;
		TestDBSerialize des_data;

		src_data._ROLE_ID = 123;
		memcpy(src_data._ROLE_NAME, "xjm", sizeof(src_data._ROLE_NAME));
		src_data._FRIENDS.push_back(456);
		src_data._FRIENDS.push_back(789);

		char data[1024] = { 0 };
		DBSerializer temp1(data, 1024);
		src_data.Serialize(temp1);

		DBSerializer temp2(data, 1024);
		des_data.Unserialize(temp2);
	}

	void ShowLength()
	{
		struct StructA
		{
			int		a[10];
			short	b;
			char	c[2];
		};

		struct StructB
		{
			char	a[10];
			short	b;
		};
		StructA s_a;
		StructB s_b;
		char data[1024] = { 0 };
		Serializer temp1(data, 1024);
		temp1.Push(s_a);
		temp1.Push(s_b);
	}
}

#endif