
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
	static const int MAX_MSG_SIZE = (4 * 1024 * 1024);	// �����Ϣ����	
}

typedef char					LoginStr[32];		// ��¼��֤
typedef char					SessionKey[32];		// ��¼��֤
typedef char					HostName[64];		// ������IP
typedef char					PlatName[64];		// �˺�����
typedef char					GameName[32];		// ��ɫ����
typedef char					PetName[32];		// ��������
typedef char					ItemName[32];		// ��Ʒ����
typedef char					ArmyName[32];		// ��������
typedef char					ArmyQQ[16];			// ����QQ
typedef char					ArmyYY[16];			// ����YY
typedef char					ArmyNotice[96];		// ���ɽ���
typedef char					SceneName[32];		// ��������
typedef char					ChannelName[32];	// Ƶ������
typedef char					MailTitle[32];		// �ʼ�����
typedef char					MailContent[512];	// �ʼ�����
typedef char					NoticeMessage[128];	// ȫ������

typedef short					Axis;				// ����
typedef float					Dir;				// ����
typedef float					Scalar;				// ����
typedef TVector2<float>			Posf;				// λ��
typedef TVector2<Axis>			Posi;				// λ��
typedef TVector2<UInt16>		Posu;				// λ��
typedef int						Attribute;			// ��������

#define INVALID_AXIS			((Axis)0)
#define INVALID_DIR				((Dir)0)
#define INVALID_SCALAR			((Scalar)0)
#define INVALID_ATTRIBUTE		((Attribute)0)

static const Posi				INVALID_POSI(0, 0);
static const Posf				INVALID_POSF(0, 0);
static const Posu				INVALID_POSU(0, 0);

typedef UInt32					UniqueID32;			// ȫ��ΨһID
typedef UInt64					UniqueID64;			// ȫ��ΨһID
typedef UInt16					ObjID;				// ��������ID
typedef UInt32					RoleID;				// ��ɫΨһID
typedef	UInt16					PetID;				// ����ID
typedef UInt16					NpcID;				// NPC ID
typedef UInt16					MonsterID;			// ����ID
typedef UInt16					GuardID;			// ����ID
typedef UInt16					MountID;			// ����ID
typedef UInt16					WingID;				// ���ID
typedef	UInt16					ItemID;				// ��ƷID
typedef UInt16					GatherID;			// �ɼ�ID
typedef UInt16					SceneID;			// ����ID
typedef UInt16					MapID;				// ��ͼID
typedef UInt16					DoorID;				// ����ID
typedef UInt16					SkillID;			// ����ID
typedef UInt16					DroperID;			// ����ID
typedef UInt16					TaskID;				// ����ID
typedef UInt16					GoodsID;			// �г���ƷID
typedef UInt16					TitleID;			// �ƺ�ID
typedef UInt32					ChannelID;			// ����Ƶ��ID
typedef UInt16					AimID;				// Ŀ��ID
typedef UInt16					DialogID;			// �Ի�ID
typedef UInt16					ServerID;			// ������ID
typedef UInt16					AvatarID;			// ����ID
typedef	UInt16					ProductID;			// buffԴID


typedef	UInt64					ArmyID;				// ����ID
typedef UInt64					MailID;				// �ʼ�ID
typedef	UInt32					CampID;				// ��ӪID

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

typedef UInt08					ItemType;			// ��Ʒ����
typedef UInt08					MoneyType;			// ��Ǯ����
typedef UInt08					ObjType;			// ʵ������
typedef UInt08					GatherType;			// �ɼ�����
typedef UInt08					SkillType;			// ��������
typedef UInt08					MonsterType;		// ��������
typedef UInt08					GuardType;			// ��������
typedef UInt08					AIType;				// ai����
typedef UInt08					AtkType;			// ��������
typedef UInt08					ChannelType;		// ����Ƶ������
typedef UInt08					SceneType;			// ��������
typedef UInt08					MailType;			// �ʼ�����

//#define INVALID_ITEM_TYPE		((ItemType)-1)		// ���ת����int����255
#define INVALID_ITEM_TYPE		-1
#define INVALID_MONEY_TYPE		((MoneyType)-1)
#define INVALID_OBJ_TYPE		((ObjType)-1)
#define INVALID_SKILL_TYPE		((SkillType)-1)
#define INVALID_MONSTER_TYPE	((MonsterType)-1)
#define INVALID_AI_TYPE			((AIType)-1)
#define INVALID_CHANNEL_TYPE	((ChannelType)-1)
#define INVALID_SCENE_TYPE		((SceneType)-1)
#define INVALID_MAIL_TYPE		((MailType)0)

typedef UInt16					ServerIndex;		// ����������
typedef UInt08					SkillIndex;			// ��������
typedef UInt16					SceneIndex;			// ��������
typedef UInt08					PetIndex;			// ��������
typedef SInt32					KnapIndex;			// ��������
typedef UInt32					TeamIndex;			// ��������
typedef UInt32					SceneKey;			// ����Key
typedef UInt16					DamageIndex;		// �˺���Ѫ����

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
	ATTACK_MODE_PEACE			= 0	,	// ��ƽ
	ATTACK_MODE_ALL				= 1	,	// ȫ��
	ATTACK_MODE_ARMY			= 2	,	// ����
	ATTACK_MODE_TEAM			= 3	,	// ����
	ATTACK_MODE_CAMP			= 4	,	// ��Ӫ
	ATTACK_MODE_COUNT				,
};

enum _ATTACK_TYPE
{
	ATTACK_TYPE_PHY				= 0	,	// �﹥
	ATTACK_TYPE_MAG				= 1	,	// ����
};

enum _EQUIPMENT_TYPE
{
	EQUIPMENT_TYPE_INVALID = 0,	// ��Ч
	EQUIPMENT_TYPE_WEAPON = 1,	// ����
	EQUIPMENT_TYPE_NECKLACE = 2,	// ����
	EQUIPMENT_TYPE_RING = 3,	// ��ָ
	EQUIPMENT_TYPE_BRACELET = 4,	// ����
	EQUIPMENT_TYPE_EARRING = 5,	// ����
	EQUIPMENT_TYPE_HELMET = 6,	// ͷ��
	EQUIPMENT_TYPE_GREAVE = 7,	// �ؼ�
	EQUIPMENT_TYPE_WRIST = 8,	// ����
	EQUIPMENT_TYPE_ENKLE = 9,	// ����
	EQUIPMENT_TYPE_SHOES = 10,	// Ь��
	EQUIPMENT_TYPE_COUNT,
};

enum _PROFESSION
{
	PROFESSION_NONE = 0,	// ��
	PROFESSION_WARRIOR = 1,	// սʿ
	PROFESSION_MASTER = 2,	// ��ʦ
	//PROFESSION_ARCHER			= 3	,	// ����
	PROFESSION_COUNT,
};

enum _SEX_TYPE
{
	SEX_TYPE_FEMALE = 0,	// Ů
	SEX_TYPE_MALE = 1,	// ��
};

enum _MAIL_TYPE
{
	MAIL_TYPE_INVALID			= 0	,	// ��Ч
	MAIL_TYPE_USER				= 1	,	// ����ʼ�
	MAIL_TYPE_SYSTEM			= 2	,	// ϵͳ�ʼ�
};


enum _COLOUR_TYPE
{
	COLOUR_TYPE_GREEN = 0,	// ��ɫ
	COLOUR_TYPE_BLUE = 1,	// ��ɫ
	COLOUR_TYPE_PURPLE = 2,	// ��ɫ
	COLOUR_TYPE_TPURPLE = 3,	// ����
	COLOUR_TYPE_ORANGE = 4,	// ���
	COLOUR_TYPE_PINK = 5,	// ���
	COLOUR_TYPE_COUNT,
};

enum _CHANNEL_TYPE
{
	CHANNEL_TYPE_WORLD			= 0	,	// ����Ƶ��
	CHANNEL_TYPE_SYSTEM			= 1	,	// ϵͳƵ��
	CHANNEL_TYPE_SCENE			= 2	,	// ����Ƶ��
	CHANNEL_TYPE_TEAM			= 3	,	// ����Ƶ��
	CHANNEL_TYPE_ARMY			= 4	,	// ����Ƶ��
};

enum _CHANNEL_ID_BEGIN
{
	CHANNEL_ID_WORLD_BEGIN		=0,			// ����Ƶ��idΪ0
	CHANBEL_ID_COUNTRY_BEGIN	=100,		// ��ӪƵ��idΪ100+��Ӫ��ţ�1�ܣ�2����3��
	CHANNEL_ID_SCENE_BEGIN		=10000,		// ����Ƶ��idΪ10000 + ������id * 1000 + SceneIndex
	CHANNEL_ID_TEAM_BEGIN		=200000,	// �������idΪ20W + team_index
	CHANNEL_ID_ARMY_BEGIN		=1000000,	// ��������idΪ100W + ArmyID
};


// �鿴����gameworld �� globalserver ��Ӧ�Ľṹ
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
		PET_CLASS_COLLECTION_COMPELETE		= 36,	// ����ͼ���ռ����
		XIANGYAO_FIRST_COMPELETE			= 37,	// �״�ͨ�ؽ�����ħ
		ARMYBATTLE_BOSS_APPEAR				= 38,
		FIRST_RECHARGE_10					= 39,
		WHOLE_SERVER_ACTIVITY_COMPELETE		= 40,
		MARRY_NOTICE						= 41,
		BREAK_SUCCESS						= 42,	// �ɹ�ͻ��
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
	
	unsigned short inner_netid;	// �ڲ������ӵ����ص��ڲ����Ӻ�
	unsigned short outer_netid;	// �ͻ������ӵ����ص��ⲿ���Ӻ�
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

