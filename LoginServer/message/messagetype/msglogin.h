
#ifndef MSGLOGIN_H
#define MSGLOGIN_H

#include "common/serverdef.h"
#include "common/protocol/messageheader.h"

#pragma pack(push)
#pragma pack(4)

namespace EProtocol
{
	enum __LoginAckResult
	{
		LOGIN_RESULT_SUC		=0,
		LOGIN_NO_THREAD			=-1,
		LOGIN_SERVER_ERROR		=-2,
		LOGIN_RESULT_EXIST		=-3,
		LOGIN_SCENE_NOT_EXIST	=-4,
		LOGIN_RESULT_NO_GATEWAY	=-5,
		LOGIN_RESULT_NO_ROLE	=-6,
		LOGIN_THREAD_BUSY		=-7,
		LOGIN_LOGIN_FORBID		=-8,
		LOGIN_ANTI_WALLOW		=-9,
		LOGIN_CREATE_ROLE_ERR	=-10,
		LOGIN_RNAME_DUPLICATE	=-11,
		LOGIN_FORBID_ID			=-12,
		LOGIN_FORBID_IP			=-13,
	};

	// 7050 请求登录
	class CSLogin
	{
	public:
		CSLogin();
		MessageHeader	header;
		PlatName		pname;
		unsigned short	anti_wallow;
		unsigned short	server_id;
	};

	// 7150 请求创建角色
	class CSCreateRole
	{
	public:
		CSCreateRole();
		MessageHeader	header;
		PlatName		pname;
		GameName		rname;
		unsigned short	avatar;
		unsigned short	profession;
		unsigned short	sex;
		unsigned short	server_id;
	};

	// 7001 登录错误返回
	class SCLoginErr
	{
	public:
		SCLoginErr();
		MessageHeader	header;
		unsigned int	result;
	};

	// 7000 登录成功返回
	class SCLoginAck
	{
	public:
		SCLoginAck();
		MessageHeader	header;
		unsigned int	role_id;
		GameName		role_name;
		unsigned short	scene_id;
		unsigned short	last_scene_id;
		unsigned int	scene_key;
		unsigned int	time_s;
		SessionKey		sessionkey;
		HostName		host_name;
		unsigned short	host_port;
		unsigned short	host_index;
	};
}

#pragma pack(pop)

#endif

