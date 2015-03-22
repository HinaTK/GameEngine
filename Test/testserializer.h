
#ifndef TEST_SERIALIZER_H
#define TEST_SERIALIZER_H

#include <vector>
#include "lib/include/common/serializer.h"
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


	void ShowLength()
	{
// 		struct StructA
// 		{
// 			int		a[10];
// 			short	b;
// 			char	c[2];
// 		};
// 
// 		struct StructB
// 		{
// 			char	a[10];
// 			short	b;
// 		};
// 		StructA s_a;
// 		StructB s_b;
// 		char data[1024] = { 0 };
// 		Serializer temp1(data, 1024);
// 		temp1.Push(s_a);
// 		temp1.Push(s_b);
	}
}

#endif