
#ifndef CENTER_PROXY_PROTO_H
#define CENTER_PROXY_PROTO_H

namespace Proto
{
	class MessageHeader
	{
	public:
		MessageHeader(int msg_id) : msgid(msg_id), svrid(-1), check(0), time_s(0){}

		unsigned short		msgid;
		unsigned short		svrid;
		unsigned int		check;
		unsigned int		time_s;
	};

	struct CSSynRoleInfo
	{
		// MT_CENTER_SYN_ROLE_INFO_CS
		CSSynRoleInfo() :header(1185){}
		static const int MAX_SIZE = 4 * 1024 * 1024;
		MessageHeader	header;
		char data[MAX_SIZE]; 		// 这里保存的是GWSynRoleInfo所有内容
	};
}

#endif // !CENTER_PROXY_PROTO_H
