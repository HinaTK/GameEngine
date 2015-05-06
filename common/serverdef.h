
#ifndef SERVERDEF_H
#define SERVERDEF_H

#include <limits.h>
#include <memory.h>
#include <string.h>
#include "common/basedef.h"
#include "common/vector2d.h"

namespace InnerProtocol
{
	static const int MAX_GGPROTOCAL_LENGTH		= 1024;
}

namespace Protocol
{
	static const int MAX_MSG_SIZE = (4 * 1024 * 1024);	// 最大消息长度	
}

typedef char					LoginStr[32];		// 登录验证
typedef char					SessionKey[32];		// 登录验证
typedef char					HostName[64];		// 服务器IP
typedef char					PlatName[64];		// 账号名称
typedef char					GameName[32];		// 角色名称
typedef char					PetName[32];		// 宠物名称
typedef char					ItemName[32];		// 物品名称
typedef char					ArmyName[32];		// 帮派名称
typedef char					ArmyQQ[16];			// 帮派QQ
typedef char					ArmyYY[16];			// 帮派YY
typedef char					ArmyNotice[96];		// 帮派介绍
typedef char					SceneName[32];		// 场景名称
typedef char					ChannelName[32];	// 频道名称
typedef char					MailTitle[32];		// 邮件标题
typedef char					MailContent[512];	// 邮件内容
typedef char					NoticeMessage[128];	// 全服公告

typedef short					Axis;				// 坐标
typedef float					Dir;				// 方向
typedef float					Scalar;				// 距离
typedef TVector2<float>			Posf;				// 位置
typedef TVector2<Axis>			Posi;				// 位置
typedef TVector2<UInt16>		Posu;				// 位置
typedef int						Attribute;			// 人物属性

#define INVALID_AXIS			((Axis)0)
#define INVALID_DIR				((Dir)0)
#define INVALID_SCALAR			((Scalar)0)
#define INVALID_ATTRIBUTE		((Attribute)0)

static const Posi				INVALID_POSI(0, 0);
static const Posf				INVALID_POSF(0, 0);
static const Posu				INVALID_POSU(0, 0);

typedef UInt32					UniqueID32;			// 全局唯一ID
typedef UInt64					UniqueID64;			// 全局唯一ID
typedef UInt16					ObjID;				// 场景对象ID
typedef UInt32					RoleID;				// 角色唯一ID
typedef	UInt16					PetID;				// 宠物ID
typedef UInt16					NpcID;				// NPC ID
typedef UInt16					MonsterID;			// 怪物ID
typedef UInt16					GuardID;			// 守卫ID
typedef UInt16					MountID;			// 坐骑ID
typedef UInt16					WingID;				// 翅膀ID
typedef	UInt16					ItemID;				// 物品ID
typedef UInt16					GatherID;			// 采集ID
typedef UInt16					SceneID;			// 场景ID
typedef UInt16					MapID;				// 地图ID
typedef UInt16					DoorID;				// 传送ID
typedef UInt16					SkillID;			// 技能ID
typedef UInt16					DroperID;			// 掉落ID
typedef UInt16					TaskID;				// 任务ID
typedef UInt16					GoodsID;			// 市场商品ID
typedef UInt16					TitleID;			// 称号ID
typedef UInt32					ChannelID;			// 聊天频道ID
typedef UInt16					AimID;				// 目标ID
typedef UInt16					DialogID;			// 对话ID
typedef UInt16					ServerID;			// 服务区ID
typedef UInt16					AvatarID;			// 形象ID
typedef	UInt16					ProductID;			// buff源ID


typedef	UInt64					ArmyID;				// 家族ID
typedef UInt64					MailID;				// 邮件ID
typedef	UInt32					CampID;				// 阵营ID

#define INVALID_UNIQUE_ID32		((UniqueID32)0)
#define INVALID_UNIQUE_ID64		((UniqueID64)0)
#define INVALID_NET_ID			((NetID)-1)
#define INVALID_PORT			((Port)0)
#define INVALID_OBJ_ID			((ObjID)(-1))
#define INVALID_ROLE_ID			((RoleID)0)
#define INVALID_PET_ID			((PetID)0)
#define INVALID_NPC_ID			((NpcID)0)
#define INVALID_MONSTER_ID		((MonsterID)0)
#define INVALID_GUARD_ID		((GuardID)0)
#define INVALID_MOUNT_ID		((MountID)0)
#define INVALID_WING_ID			((WingID)0)
#define INVALID_ITEM_ID			((ItemID)0)
#define INVALID_GATHER_ID		((GatherID)0)
#define INVALID_SCENE_ID		((SceneID)0)
#define INVALID_MAP_ID			((MapID)0)
#define INVALID_DOOR_ID			((DoorID)0)
#define INVALID_SKILL_ID		((SkillID)0)
#define INVALID_TASK_ID			((TaskID)0)
#define INVALID_GOODS_ID		((GoodsID)0)
#define INVALID_TITLE_ID		((TitleID)0)
#define INVALID_CHANNEL_ID		((ChannelID)-1)
#define INVALID_MAIL_ID			((MailID)0)
#define INVALID_ARMY_ID			((ArmyID)0)
#define INVALID_DIALOG_ID		((DialogID)0)
#define INVALID_SERVER_ID		((ServerID)0)
#define INVALID_AVATAR_ID		((AvatarID)0)
#define INVALID_CAMP_ID			((CampID)0)
#define INVALID_PRODUCT_ID		((ProductID)0)

typedef UInt08					ItemType;			// 物品类型
typedef UInt08					MoneyType;			// 金钱类型
typedef UInt08					ObjType;			// 实体类型
typedef UInt08					GatherType;			// 采集类型
typedef UInt08					SkillType;			// 技能类型
typedef UInt08					MonsterType;		// 怪物类型
typedef UInt08					GuardType;			// 守卫类型
typedef UInt08					AIType;				// ai类型
typedef UInt08					AtkType;			// 攻击类型
typedef UInt08					ChannelType;		// 聊天频道类型
typedef UInt08					SceneType;			// 场景类型
typedef UInt08					MailType;			// 邮件类型

//#define INVALID_ITEM_TYPE		((ItemType)-1)		// 这个转化成int会变成255
#define INVALID_ITEM_TYPE		-1
#define INVALID_MONEY_TYPE		((MoneyType)-1)
#define INVALID_OBJ_TYPE		((ObjType)-1)
#define INVALID_SKILL_TYPE		((SkillType)-1)
#define INVALID_MONSTER_TYPE	((MonsterType)-1)
#define INVALID_AI_TYPE			((AIType)-1)
#define INVALID_CHANNEL_TYPE	((ChannelType)-1)
#define INVALID_SCENE_TYPE		((SceneType)-1)
#define INVALID_MAIL_TYPE		((MailType)0)

typedef UInt16					ServerIndex;		// 服务器索引
typedef UInt08					SkillIndex;			// 技能索引
typedef UInt16					SceneIndex;			// 场景索引
typedef UInt08					PetIndex;			// 宠物索引
typedef SInt32					KnapIndex;			// 背包索引
typedef UInt32					TeamIndex;			// 队伍索引
typedef UInt32					SceneKey;			// 场景Key
typedef UInt16					DamageIndex;		// 伤害扣血索引

#define INVALID_SERVER_INDEX	((ServerIndex)-1)
#define INVALID_SKILL_INDEX		((SkillIndex)-1)
#define INVALID_SCENE_INDEX		((SceneIndex)-1)
#define INVALID_PET_INDEX		((PetIndex)-1)
#define INVALID_TEAM_INDEX		((TeamIndex)-1)
#define INVALID_SCENE_KEY		((SceneKey)0)
#define INVALID_DAMAGE_INDEX	((DamageIndex)0)

enum _STRUCT_STATE
{
	STATE_INVALID	,
	STATE_NONE		,
	STATE_INSERT	,
	STATE_UPDATE	,
	STATE_DELETE	,
};

enum _ATTACK_MODE
{
	ATTACK_MODE_PEACE			= 0	,	// 和平
	ATTACK_MODE_ALL				= 1	,	// 全体
	ATTACK_MODE_ARMY			= 2	,	// 家族
	ATTACK_MODE_TEAM			= 3	,	// 队伍
	ATTACK_MODE_CAMP			= 4	,	// 阵营
	ATTACK_MODE_COUNT				,
};

enum _ATTACK_TYPE
{
	ATTACK_TYPE_PHY				= 0	,	// 物攻
	ATTACK_TYPE_MAG				= 1	,	// 法功
};

enum _EQUIPMENT_TYPE
{
	EQUIPMENT_TYPE_INVALID = 0,	// 无效
	EQUIPMENT_TYPE_WEAPON = 1,	// 武器
	EQUIPMENT_TYPE_NECKLACE = 2,	// 项链
	EQUIPMENT_TYPE_RING = 3,	// 戒指
	EQUIPMENT_TYPE_BRACELET = 4,	// 手镯
	EQUIPMENT_TYPE_EARRING = 5,	// 耳环
	EQUIPMENT_TYPE_HELMET = 6,	// 头盔
	EQUIPMENT_TYPE_GREAVE = 7,	// 胸甲
	EQUIPMENT_TYPE_WRIST = 8,	// 护腕
	EQUIPMENT_TYPE_ENKLE = 9,	// 护腿
	EQUIPMENT_TYPE_SHOES = 10,	// 鞋子
	EQUIPMENT_TYPE_COUNT,
};

enum _PROFESSION
{
	PROFESSION_NONE = 0,	// 无
	PROFESSION_WARRIOR = 1,	// 战士
	PROFESSION_MASTER = 2,	// 法师
	//PROFESSION_ARCHER			= 3	,	// 弓手
	PROFESSION_COUNT,
};

enum _SEX_TYPE
{
	SEX_TYPE_FEMALE = 0,	// 女
	SEX_TYPE_MALE = 1,	// 男
};

enum _MAIL_TYPE
{
	MAIL_TYPE_INVALID			= 0	,	// 无效
	MAIL_TYPE_USER				= 1	,	// 玩家邮件
	MAIL_TYPE_SYSTEM			= 2	,	// 系统邮件
};


enum _COLOUR_TYPE
{
	COLOUR_TYPE_GREEN = 0,	// 绿色
	COLOUR_TYPE_BLUE = 1,	// 蓝色
	COLOUR_TYPE_PURPLE = 2,	// 紫色
	COLOUR_TYPE_TPURPLE = 3,	// 真紫
	COLOUR_TYPE_ORANGE = 4,	// 真橙
	COLOUR_TYPE_PINK = 5,	// 真粉
	COLOUR_TYPE_COUNT,
};

enum _CHANNEL_TYPE
{
	CHANNEL_TYPE_WORLD			= 0	,	// 世界频道
	CHANNEL_TYPE_SYSTEM			= 1	,	// 系统频道
	CHANNEL_TYPE_SCENE			= 2	,	// 场景频道
	CHANNEL_TYPE_TEAM			= 3	,	// 队伍频道
	CHANNEL_TYPE_ARMY			= 4	,	// 帮派频道
};

enum _CHANNEL_ID_BEGIN
{
	CHANNEL_ID_WORLD_BEGIN		=0,			// 世界频道id为0
	CHANBEL_ID_COUNTRY_BEGIN	=100,		// 阵营频道id为100+阵营编号，1周，2楚，3汉
	CHANNEL_ID_SCENE_BEGIN		=10000,		// 场景频道id为10000 + 服务器id * 1000 + SceneIndex
	CHANNEL_ID_TEAM_BEGIN		=200000,	// 组队聊天id为20W + team_index
	CHANNEL_ID_ARMY_BEGIN		=1000000,	// 军团聊天id为100W + ArmyID
};


// 查看资料gameworld 和 globalserver 对应的结构
struct Attr
{
	UInt16			level;
	UInt16			viplevel;
	UInt16			wing_avatar;
	UInt16			fashion_id;
	ItemID			rind_id;
	UInt16			ring_level;
	GameName		fere_name;
	Attribute		capacity;
	Attribute		hpmax;
	Attribute		mpmax;
	Attribute		power;
	Attribute		attack;
	Attribute		phy_defend;
	Attribute		mag_defend;
	Attribute		crit;
	Attribute		tenacity;
	Attribute		charm;
	Attribute		speed;
	
};

namespace NoticeType
{
	enum
	{
		WING_STARLEVEL = 0,
		MOUNT_UPGRADE = 1,
		EQUIP_STRENGTHEN = 2,
		EQUIP_QUALITY = 3,
		EQUIP_LEVEL = 4,
		EQUIP_MOUNT = 5,
		EQUIP_RECAST = 6,
		EQUIP_MARK = 7,
		FABAO_AVATAR = 8,
		FABAO_HUNTSOUL = 9,
		FABAO_EXCHANGE = 10,
		NEILI_UPGRADE = 11,
		MOUNT_TRAIN = 12,
		PET_PERCEP = 13,
		PET_GROWTH = 14,
		FIRST_RECHARGE = 15,
		ARMY_CREATE = 16,
		BOSS_BE_KILL = 17,
		GOD_OF_WEALTH = 18,
		RAND_MONSTER_BE_KILL = 19,
		DRAGON_KING_APPEAR = 20,
		TODAY_RECHARGE_GIFT = 21,
		OPEN_LUCKY_STONE					= 22,
		CAMPBATTLE_BOSS_BE_KILL				= 23,
		WORLDFIRST_BOSS_BE_KILL				= 24,
		WORLDFIRST_FIRST_BLOOD				= 25,
		WORLDFIRST_TRIPLE_KILL				= 26,
		WORLDFIRST_QUTINTUPLE_KILL			= 27,
		WORLDFIRST_TENFOLD_KILL				= 28,
		WORLDFIRST_MULTI_KILL_TERMINATE		= 29,
		MONSTERTOWER_KILL_ALL_BOSS			= 30,
		ARENA_KEEP_WIN						= 31,
		ARENA_FIRST							= 32,
		BUY_GIFT_BAG						= 33,
		WORLD_BOSS_APPEAR					= 34,
		FIELD_BOSS_APPEAR					= 35,
		PET_CLASS_COLLECTION_COMPELETE		= 36,	// 宠物图鉴收集完成
		XIANGYAO_FIRST_COMPELETE			= 37,	// 首次通关降妖附魔
		ARMYBATTLE_BOSS_APPEAR				= 38,
		FIRST_RECHARGE_10					= 39,
		WHOLE_SERVER_ACTIVITY_COMPELETE		= 40,
		MARRY_NOTICE						= 41,
		BREAK_SUCCESS						= 42,	// 成功突破
	};
};

namespace ArmyNoticeType
{
	enum
	{
		CALL_ARMY_BOSS = 0,
		MAIN_BUILD_UPGRADE = 1,
		ALTAR_BUILD_UPGRADE = 2,
		KONGFU_BUILD_UPGRADE = 3,
		SMITHY_BUILD_UPGRADE = 4,
		SHOP_BUILD_UPGRADE = 5,
	};
};

struct GSNetID
{
	GSNetID() : inner_netid(-1), outer_netid(-1){}
	GSNetID(const GSNetID &v) : inner_netid(v.inner_netid), outer_netid(v.outer_netid){}
	GSNetID(unsigned short i_netid, unsigned short o_netid) : inner_netid(i_netid), outer_netid(o_netid){}
	
	bool operator<(const GSNetID& right) const
	{
		return ((inner_netid < right.inner_netid) || ((inner_netid == right.inner_netid) && (outer_netid < right.outer_netid)));
	}

	bool operator==(const GSNetID &right) const
	{
		return outer_netid == right.outer_netid && inner_netid == right.inner_netid;
	}
	
	bool operator!=(const GSNetID &right) const
	{
		return outer_netid != right.outer_netid || inner_netid != right.inner_netid;
	}
	
	unsigned short inner_netid;	// 内部服连接到网关的内部连接号
	unsigned short outer_netid;	// 客户端连接到网关的外部连接号
};

struct UserID
{
	UserID():db_index(-1), role_id(0){}
	UserID(const UserID &v):db_index(-1), role_id(v.role_id) {}
	UserID(unsigned int rid):db_index(-1), role_id(rid){}
	
	bool operator<(const UserID& right) const
	{
		return ((db_index < right.db_index) || ((db_index == right.db_index) && (role_id < right.role_id)));
	}

	bool operator==(const UserID &right) const
	{
		return db_index == right.db_index && role_id == right.role_id;
	}

	bool operator!=(const UserID &right) const
	{
		return db_index != right.db_index || role_id != right.role_id;
	}

	unsigned int db_index;
	unsigned int role_id;
};

static const GSNetID	INVALID_GSNETID(-1, -1);
static const UserID		INVALID_USER_ID(0);

struct TradeItem
{
	ItemID	item_id;
	UInt16	item_num;
	UInt16	item_index;
	UInt16	reserved;
};

#endif

