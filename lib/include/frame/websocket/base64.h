
#ifndef BASE64_H
#define BASE64_H

#include <string>
using namespace std;

class Base64
{
public:
	/*����
	DataByte
	[in]��������ݳ���,���ֽ�Ϊ��λ
	*/
	string Encode(const unsigned char* Data, int DataByte);
	/*����
	DataByte
	[in]��������ݳ���,���ֽ�Ϊ��λ
	OutByte
	[out]��������ݳ���,���ֽ�Ϊ��λ,�벻Ҫͨ������ֵ����
	������ݵĳ���
	*/
	string Decode(const char* Data, int DataByte, int& OutByte);
};

#endif // !BASE64_H
