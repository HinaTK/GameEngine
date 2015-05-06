
#pragma once

#ifndef MSG_CODE_H
#define MSG_CODE_H

namespace EProtocol
{
	enum
	{
		/************************************************************************/
		MT_TEST_GM_COMMAND					= 500,	// ��������
		// ��¼
		MT_SERVER_ENTER_SC					= 1000,	// ���볡��������
		MT_SERVER_CHANGE_SC					= 1001,	// �л�����������
		MT_SERVER_INFO_SC					= 1002,	// ��������Ϣ
		MT_SERVER_ENTER_CS					= 1050,	// ������볡��������
		MT_SERVER_HEARTBEAT_CS				= 1053,	// �ͻ���������
		// ����
		MT_SCENE_ENTER_SC					= 1100,	// ���볡��
		MT_SCENE_LEAVE_SC					= 1101,	// �뿪����
		MT_SCENE_VISIBLE_ENTER_ROLE_SC		= 1102,	// Role��������������
		MT_SCENE_VISIBLE_LEAVE_SC			= 1103,	// �����˳���������
		MT_SCENE_OBJ_MOVE_SC				= 1104,	// ����λ���ƶ�ͬ��
		MT_SCENE_VISIBLE_ENTER_FALLING_SC	= 1105,	// �����������������
		MT_SCENE_VISIBLE_ENTER_MONSTER_SC	= 1106,	// �����������������
		MT_SCENE_VISIBLE_ENTER_PET_SC		= 1107,	// �����������������
		MT_SCENE_VISIBLE_ENTER_TRUCK_SC		= 1108,	// �ڳ���������������
		MT_SCENE_VISIBLE_ENTER_GATHER_SC	= 1109,	// �ɼ���Ʒ�����������
		MT_SCENE_SMALL_SHOE_SC				= 1110,	// ʹ��С��Ь���
		MT_SCENE_RESET_POSI_SC				= 1111,	// �����Լ�λ��
		MT_FB_PANEL_INFO_SC					= 1112,	// ���������Ϣ����
		MT_FB_ENTER_TIME_INFO_SC			= 1113, // ������Ϣ��������
		MT_FB_VDEMON_INFO_SC				= 1114,	// ��ħ����������Ϣ����
		MT_FB_VDEMON_INFO_CHANGE_SC			= 1115, // ��ħ����������Ϣ�ı䷵��
		MT_FB_VDEMON_FINISH_SC				= 1116,	// ɨ��������֪ͨ�����ȡ����
		MT_FB_VDEMON_SWEEP_INFO_SC			= 1117,	// ɨ����Ϣ
		MT_FB_DELEGATION_INFO_SC			= 1118,	// ί����Ϣ����
		MT_FB_DELEGATION_FINISH_SC			= 1119,	// ί�����
		MT_SCENE_GATHER_RSP_SC				= 1120,	// ��ʼ�ɼ�
		MT_SCENE_GATHER_SUCCESS_SC			= 1123,	// �ɼ��ɹ�
		MT_SCENE_OBJ_UPGRADE_SC				= 1124,	// �����㲥
		MT_FB_MONSTER_INFO_SC				= 1125,	// ���︱����Ϣ
		MT_FB_MONSTER_DIE_SC				= 1126,	// ������������
		MT_IS_ACCELERATING_SC				= 1127,	// ������ڼ���

		MT_FB_ALL_ENTER_TIME_INFO_SC		= 1130,	// ���и������������Ϣ����
		MT_FB_VDEMON_HAS_GET_REWARD_SC		= 1131, // ��ħ����������ȡ��������(������������Ϣ)
		MT_FB_DELEGATION_GET_REWARD_SC		= 1132, // ί���콱����
		MT_FB_FINISH_SC						= 1133,	// ����ͨ�����
		MT_SCENE_FALLING_OWNER_CHANGE_SC	= 1136,	// ��������仯
		MT_SCENE_REST_START_CS				= 1141,	// ����ʼ����
		MT_SCENE_REST_START_SC				= 1142,	// ��ʼ�������
		MT_SCENE_REST_STOP_CS				= 1143,	// �����������
		MT_SCENE_REST_STOP_SC				= 1144,	// �����������
		MT_SCENE_REST_INVITE_CS				= 1145,	// ����˫��
		MT_SCENE_REST_INVITE_SC				= 1146,	// ����˫�� ת��
		MT_SCENE_REST_INVITE_RESULT_CS		= 1147,	// ������C-S
		MT_SCENE_REST_INVITE_RESULT_SC		= 1148,	// ������S-C
		MT_SCENE_SING_STATUS_SC				= 1149,	// ����״̬

		MT_SCENE_ENTER_HOOK_CS				= 1152,	// �������һ���ͼ
		MT_SCENE_TRANSPORT_CS				= 1153,	// ������
		MT_SCENE_OBJ_MOVE_CS				= 1154,	// ����ƶ�
		MT_SCENE_SMALL_SHOE_CS				= 1155,	// ʹ��С��Ь
		MT_FB_TRIAL_ENTER_CS				= 1156, // ������������
		MT_FB_EXP_ENTER_CS					= 1157,	// ���뾭�鸱��
		MT_FB_PET_ENTER_CS					= 1158, // ������︱��
		MT_FB_BOUNTY_ENTER_CS				= 1159, // �����ͽ𸱱�
		MT_FB_BABEL_ENTER_CS				= 1160, // ����ͨ���ؾ�����
		MT_FB_DREAMLAND_ENTER_CS			= 1161,	// ���������þ�����
		MT_FB_FABAO_ENTER_CS				= 1162,	// ���뷨������
		MT_FB_ENTER_TIME_INFO_CS			= 1163, // ���븱��������Ϣ����
		MT_FB_EXIT_FB_CS					= 1164, // �����˳�����
		MT_FB_ENTER_NEXT_SCENE_CS			= 1165, // ���������һ��
		MT_FB_DEFEND_ENTER_CS				= 1166,	// ������ظ���
		MT_FB_VDEMON_ENTER_CS				= 1167,	// ���뽵ħ��������
		MT_FB_VDEMON_SWEEP_CS				= 1168, // ɨ����ħ��������
		MT_FB_VDEMON_CANCEL_SWEEP_CS		= 1169, // ȡ��ɨ��
		MT_FB_VDEMON_INFO_CS				= 1170, // ����ħ����������Ϣ
		MT_FB_VDEMON_GET_REWARD_CS			= 1171,	// ������ȡ��ħ��������ɨ������
		MT_FB_DELEGATION_BEGIN_CS			= 1172,	// ����ί�п�ʼ
		MT_FB_DELEGATION_GET_REWARD_CS		= 1173, // ��ȡί�н���
		MT_SCENE_ENTER_FIND_TREASURE_CS		= 1174,	// ����򱦵�ͼ
		MT_FB_VDEMON_SWEEP_INFO_CS			= 1175,	// ��ɨ�����
		MT_FB_DELEGATION_FINISH_NOW_CS		= 1176, // �������ί��
		MT_FB_DELEGATION_INFO_CS			= 1177,	// ��ί�и�����壨��ʼUpdate��
		MT_FB_DAYBREAK_ENTER_CS				= 1178,	// ���������ɾ�
		MT_FB_NEWBIE_ENTER_CS				= 1179,	// �������ָ���
		MT_SCENE_GATHER_REQ_CS				= 1180,	// ����ɼ�
		MT_FB_SHURA_ENTER_CS				= 1181, // �������޵���
		MT_FB_MONSTERTOWER_ENTER_CS			= 1182,	// ����������
		MT_FB_OLDCEMETERY_ENTER_CS			= 1183,	// �����������
		

		// ս�����
		MT_FIGHT_CHANGE_HP_SC				= 1300,	// �㲥hp�仯
		MT_FIGHT_PERFORM_SKILL_SC			= 1301,	// �ͷż���
		MT_FIGHT_CHARA_DEAD_SC				= 1302,	// ����
		MT_FIGHT_ROLE_REALIVE_SC			= 1303,	// ����
		MT_FIGHT_PERFORM_AOE_SKILL_SC		= 1304,	// ʩ��AOE���ܣ���Ŀ��ص�
		MT_FIGHT_CHANGE_MP_SC				= 1305,	// �㲥mp�仯
		MT_FIGHT_BUFF_ADD_SC				= 1306,	// ����buff
		MT_FIGHT_BUFF_DEL_SC				= 1307,	// ɾ��buff
		MT_FIGHT_FLY_SKY_SKILL_POS_SC		= 1308,	// ������ն
		MT_FIGHT_PERFORM_SKILL_EX_SC		= 1312,	// �ͷż��ܣ����ϲ����ܺ�����λ�ã���
		

		MT_FIGHT_PERFORM_AOE_SKILL_CS		= 1350,	// �ͷ�AOE����
		MT_FIGHT_PERFORM_SKILL_CS			= 1351,	// ʩ�ż���
		MT_FIGHT_ROLE_REALIVE_CS			= 1352,	// �����ɫ����
		MT_FIGHT_CHANGE_PK_MODE_CS			= 1353,	// �ı�pkģʽ

		// ��ɫ��Ϣ���
		MT_ROLE_BAS_INFO_SC					= 1400,	// �����ɫ������Ϣ����
		MT_ROLE_SKILL_INFO_SC				= 1401,	// �����ɫ������Ϣ����
		MT_ROLE_ATTR_VALUE_SC				= 1402,	// ��ɫ������ֵ֪ͨ
		MT_ROLE_SKILL_LEARN_SC				= 1403,	// ����ѧϰ����											�Ѿ�����*
		MT_ROLE_SKILL_UPGRADE_SC			= 1404,	// ������������											�Ѿ�����*
		MT_ROLE_EXP_CHANGE_SC				= 1405,	// ������֪ͨ
		MT_ROLE_LEVEL_UPGRADE_SC			= 1406,	// ���������㲥
		MT_ROLE_HP_MP_PACK_SC				= 1407,	// �������仯
		MT_ROLE_ARMY_INFO_SC				= 1408,	// ������Ϣ
		MT_ROLE_EFFECT_LIST_SC				= 1409,	// buff�б�
		MT_ROLE_EXP_DAN_INFO_SC				= 1410,	// ���鵤
		MT_ROLE_INFO_OTHER_SC				= 1415,	// �鿴������Ϣ����

		MT_ROLE_BASE_INFO_CS				= 1450,	// �����ɫ������Ϣ
		MT_ROLE_SKILL_INFO_CS				= 1451,	// �����ɫ������Ϣ
		MT_ROLE_SKILL_UPGRADE_ENTIRE_CS		= 1452,	// һ����������
		MT_ROLE_SKILL_LEARN_REQ_CS			= 1453,	// ������ѧϰ
		MT_ROLE_SKILL_UPGRADE_REQ_CS		= 1454,	// ����������
		MT_ROLE_SET_ATTACK_MODE_CS			= 1455,	// ���ù���ģʽ
		MT_ROLE_ALL_INFO_REQ_CS				= 1458,	// ���ڵ�½ʱ����һϵ����Ϣ(ԭ��ģ��ĵ���������Ϣ����)
		// ��Ʒ�������
		MT_KNAPSACK_INFO_ACK_SC				= 1500,	// ���󱳰���Ϣ����
		MT_KNAPSACK_GRID_CHANGE_SC			= 1501,	// �����������ӱ仯
		MT_KNAPSACK_PARAM_SC				= 1502,	// ���������б�
		MT_KNAPSACK_GRID_CHANGE_PARAM_SC	= 1503,	// �в����ĸ��ӱ仯
		MT_STROAGE_COIN_CHANGE_SC			= 1504,	// �ֿ�ͭǮ�����ı�
		MT_USE_ITEM_SUC_SC					= 1505,	// ʹ����Ʒ�ɹ�
		MT_KNAPSACK_MAX_GRID_NUM_SC			= 1506,	// ����������������
		MT_FUNCTION_NEW_ITEM_NOTICE_SC		= 1507,	// ����Ʒ֪ͨ
		MT_TEAM_MEMBER_PICK_ITEM_SC			= 1508,	// �����Աʰȡ������Ʒ
		MT_TEAM_MEMBER_PICK_COIN_SC			= 1509,	// �����Աʰȡ����ͭ��
		MT_KNAPSACK_ACQUIRE_SC				= 1510,	// ��ȡ��Ʒ��Ϣ
		MT_KNAPSACK_INFO_REQ_CS				= 1550,	// ���󱳰���Ϣ
		MT_USE_ITEM_CS						= 1551,	// ʹ����Ʒ
		MT_MOVE_ITEM_CS						= 1552,	// �ƶ�������Ԫ
		MT_DICARD_ITEM_CS					= 1553,	// ������Ʒ
		MT_KNAPSACK_ARRANGE_CS				= 1554,	// ������
		MT_ITEM_PICK_CS						= 1555,	// ���������Ʒ
		MT_SPLIT_ITEM_CS					= 1556,	// ��ֱ�����Ʒ
		MT_NPC_STROAGE_MOVE_CS				= 1557,	// ͨ��npc�ƶ��ֿ���Ʒ
		MT_NPC_STROAGE_COIN_MOVE_CS			= 1558,	// ͨ��npc�ƶ��ֿ�ͭǮ
		MT_ARMY_PUT_STORE_ITEM_CS			= 1559,	// ����ѱ�������Ʒ����ֿ�
		MT_EXTEND_KNAPSACK_NUM_CS			= 1560,	// ��չ������ֿ�
		MT_TWISTEGG_STORAGE_CS				= 1570,	// ����Ť���ֿ�
		MT_MOVE_GASHAPON_ALL_TO_KNAPSACK_CS	= 1571,	// �ƶ�Ѱ��������Ʒ
		MT_ITEM_LINK_INFO_CS				= 1572,	// ������Ʒ������
		MT_TWIST_OTHER_INFOGET_CS			= 1573,// ����������ҵ�Ť����ҫ��Ϣ�� ֻ����ҵ�һ�δ򿪵�ʱ���ȡ
		MT_MERGER_ITEM_CS					= 1574,// �ϲ�ĳ��λ�õ���Ʒ
		MT_SELL_ITEM_CS						= 1575,// ������Ʒ
		MT_WALLOW_PERCENT_CHANGE_CS			= 1576,// ��������Ϣ�ı䣬Ҫ������������ݿ��ѯ
		MT_MERGER_ALL_ITEM_CS				= 1577,// �ϲ�����������Ʒ
		MT_ITEM_COMPOSITE_ITEM_CS			= 1578,// �ϳ���Ʒ��2013.12.28��
		MT_ITEM_BATCH_COMPOSITE_ITEM_CS		= 1579,// �����ϳ���Ʒ��2013.12.28��
		MT_ITEM_COMPOSITE_ALL_JEWEL_CS		= 1580,// һ���ϳ����еı�ʯ
		MT_ITEM_TRANSFORM_CS				= 1581,// ��Ʒת��
		// װ�����
		MT_EQUIPMENT_INFO_ACK_SC			= 1700,	// ��ȡװ����Ϣ����
		MT_EQUIPMENT_ITEM_CHANGE_SC			= 1701,	// װ����Ϣ�ı�
		MT_EQUIPMENT_BATCH_PURIFY_SC		= 1720,	// ����ϴ�����Է���
		MT_EQUIPMENT_STRENGTHEN_WISHES_SC	= 1721,	// ����ǿ��ף��ֵ
		
		MT_EQUIPMENT_INFO_REQ_CS			= 1750,	// ����װ����Ϣ
		MT_EQUIPMENT_TAKE_OFF_CS			= 1751,	// ����װ��
		MT_EQUIPMENT_TAKE_OFF_FASHION_CS	= 1752,	// ����ʱװ
		MT_EQUIPMENT_STRENGTHEN_CS			= 1786,	// װ��ǿ��
		MT_EQUIPMENT_MOUNT_JEWEL_CS			= 1787,	// ��Ƕ��ʯ
		MT_EQUIPMENT_UNMOUNT_JEWEL_CS		= 1788,	// ժ����ʯ
		MT_EQUIPMENT_UPGRADE_CS				= 1789,	// װ������
		MT_EQUIPMENT_PROMOTE_QUALITY_CS		= 1790,	// װ������
		MT_EQUIPMENT_RECAST_CS				= 1791,	// װ������
		MT_EQUIPMENT_WASH_CS				= 1792,	// װ��ϴ��
		MT_EQUIPMENT_BATCH_WASH_CS			= 1793,	// װ������ϴ��
		MT_EQUIPMENT_SAVE_WASH_CS			= 1794,	// ��������ϴ�����
		MT_EQUIPMENT_MARK_CS				= 1795,	// װ������
		// NPC ����
		MT_TASK_LIST_RSP_SC					= 1800,	// ���������б���
		MT_TASK_RECORDER_LIST_SC			= 1801,	// ���������¼�б�
		MT_TASK_ACCEPT_SC					= 1802,	// �������񷵻�
		MT_TASK_COMMIT_SC					= 1803,	// �ύ���񷵻�
		MT_TASK_GIVEUP_SC					= 1804,	// �������񷵻�
		MT_TASK_CHANGE_SC					= 1805,	// ����ı䷵��
		MT_TASK_RECORDER_CHANGE_SC			= 1806,	// ���������¼��Ϣ
		MT_TASK_LOOP_SC						= 1807,	// ѭ������
		MT_TASK_BOARD_SC					= 1808,	// ��������
		MT_TASK_COIN_SC						= 1809,	// ��������
		MT_TASK_ARMY_SC						= 1810,	// ��������
		MT_TASK_XLIAN_SC					= 1811,	// ����������
		MT_TASK_BOARD_LIST_SC				= 1812,	// ���������б�
		MT_TASK_BOARD_ITEM_CHANGE_SC		= 1813,	// �����б�ı�
		MT_TASK_DAY_COUNT_CHANGE_SC			= 1814,	// �ճ�����ÿ�մ����仯
		MT_TASK_XLIAN_FINISH_REWARD_SC		= 1815,	// ������ȫ����ɽ���
		MT_TASK_LIST_REQ_CS					= 1850,	// ���������б�
		MT_TASK_RECORDER_LIST_CS			= 1851,	// ���������¼�б�
		MT_TASK_ACCEPT_CS					= 1852,	// �����������
		MT_TASK_COMMIT_CS					= 1853,	// �����ύ����
		MT_TASK_GIVEUP_CS					= 1854,	// �����������
		MT_TASK_TALK_CS						= 1855,	// ��NPC�Ի�
		MT_TASK_BOARD_LIST_CS				= 1856,	// ����������Ϣ
		MT_TASK_BOARD_FRESH_CS				= 1857,	// ˢ����������
		MT_TASK_BOARD_FINISH_CS				= 1858,	// ���������������
		MT_TASK_XLIAN_INFO_CS				= 1859,	// ������������Ϣ
		MT_TASK_XLIAN_FRESH_CS				= 1860,	// ˢ������������
		MT_TASK_XLIAN_TOP_QUALITY_CS		= 1861,	// һ����������������
		MT_TASK_XLIAN_FINISH_ALL_CS			= 1862,	// һ�����ȫ��������
		MT_TASK_XLIAN_FINISH_CS				= 1863,	// �����������������
		MT_TASK_XLIAN_FINISH_ALL_REWARD_CS	= 1864,	// ��ȡ��ɽ���
		// ��Ǯ���
		MT_MONEY_SC							= 2000,	// Ǯ
		// �������
		MT_PET_LIST_ACK_SC					= 2200,	// ��������б�ظ�
		MT_PET_CALL_INDEX_CHANGE_SC			= 2201,	// ��ս����仯
		MT_PET_ATTR_CHANGE_SC				= 2202,	// �������Ա仯
		MT_PET_INFO_SC						= 2203,	// ���������������Ϣ
		MT_PET_LEVEL_UPGRADE_SC				= 2204,	// ���ﾭ�������㲥
		MT_PET_PERCEPTION_UPGRADE_SC		= 2205,	// �������������㲥
		MT_PET_RENAME_SC					= 2213,	// �������--Leon Add 12-02-29
		MT_PET_DISCARD_SC					= 2214,	// �������--Leon Add 12-02-29
		MT_PET_SHOW_OFF_SC					= 2229,	// ��ҫ
		MT_PET_SHOW_OFF_INFO_SC				= 2230,	// ��ҫ��Ϣ
		MT_PET_LEARN_SKILL_SC				= 2232,	// ѧϰ���ܽ��
		MT_PET_FORGET_SKILL_SC				= 2233,	// �������ܽ��
		MT_PET_MARK_SKILL_SC				= 2234,	// ��ӡ���ܽ��
		MT_PET_RAND_SKILL_SC				= 2235,	// ���ˢ�¼��ܽ��
		MT_PET_SKILL_LIST_ACK_SC			= 2236,	// ���＼���б�
		MT_PET_PROMOTE_GROWTH_SC			= 2237,	// �����ɳ�
		MT_PET_PROMOTE_PERCEPTION_SC		= 2238,	// ��������
		MT_PET_INHERIT_SC					= 2239,	// �ں�
		MT_PET_CLASS_INFO_SC				= 2240,	// ����ͼ����Ϣ

		//MT_PET_LIST_REQ_CS				= 2250,	// ��������б�(����)
		MT_PET_CALLOUT_REQ_CS				= 2251,	// �����ٻ�����
		MT_PET_CALLBACK_REQ_CS				= 2252,	// �����ջس���
		MT_PET_DISCARD_REQ_CS				= 2253,	// �������
		MT_PET_RENAME_REQ_CS				= 2255,	// ����������		
		MT_PET_PROMOTE_GROWTH_CS			= 2256,	// ��������ɳ�
		MT_PET_PROMOTE_PERCEPTION_CS		= 2257,	// ������������
		MT_PET_LEARN_SKILL_CS				= 2260,	// ѧϰ����
		MT_PET_FORGET_SKILL_CS				= 2261,	// ��������
		MT_PET_MARK_SKILL_CS				= 2262,	// ��ӡ����
		MT_PET_RAND_SKILL_CS				= 2263,	// �������
		MT_PET_INHERIT_CS					= 2264,	// �����ں�
		MT_PET_MERGE_CS						= 2267,	// �������
		MT_PET_MERGE_CANCEL_CS				= 2268,	// ȡ������
		MT_PET_SHOW_OFF_CS					= 2269,	// ��ҫ
		MT_PET_SHOW_OFF_INFO_CS				= 2270,	// ��ҫ��Ϣ
		MT_PET_CHANGE_AI_MODE_CS			= 2271,	// �ı乥��ģʽ
		// ����
		MT_SIGNIN_INFO_SC					= 2700,	// ǩ�������Ϣ����
		MT_SIGNIN_REWARDS_SC				= 2701,	// ǩ��������Ϣ
		MT_NEILI_INFO_SC					= 2702,	// ������Ϣ����
		MT_NEILI_CHANGE_SC					= 2703,	// ����ֵ�����ı�
		MT_PUT_ON_TITLE_INFO_SC				= 2704,	// ��װ���ƺ���Ϣ
		MT_OWN_TITLE_INFO_SC				= 2705,	// ����ӵ�еĳƺ���Ϣ
		MT_OWN_TITLE_STATUS_SC				= 2706,	// �����ƺ�״̬�����ı䣨����orɾ����
		MT_ONLINE_REWARD_INFO_SC			= 2707,	// ���߽�����Ϣ����
		MT_MONEY_TREE_SC					= 2708,	// �в�����Ϣ����
		MT_CONSUME_GIFT_BAG_INFO_SC			= 2709, // ���������Ϣ����
		MT_CONSUME_GIFT_BAG_CHANGE_SC		= 2710, // ��Ϣ���״̬�ı�
		MT_MYSTERY_SHOP_INFO_SC				= 2711, // �����̵���Ϣ����
		MT_MYSTERY_SHOP_BUY_ITEM_SC			= 2712,	// �����̵깺����Ʒ����
		MT_AIM_INFO_SC						= 2713,	// Ŀ����Ϣ����
		MT_AIM_STATE_CHANGE_SC				= 2714, // Ŀ��״̬�ı�
		MT_HUNT_INFO_SC						= 2715, // Ѱ�����˸ſ�����
		MT_ADD_HUNT_INFO_SC					= 2716, // Ѱ�����Ӹ��˸ſ�
		MT_VIP_LEVEL_REWARD_STATE_SC		= 2717,	// VIP�ȼ�����״̬
		MT_YELLOW_VIP_PANEL_INFO_SC			= 2718,	// ���������Ϣ
		MT_OSP_INFO_SC						= 2719, // �����Ź���Ϣ
		MT_FIRST_RECHARGE_INFO_SC			= 2720,	// �׳���Ϣ����
		MT_SEVEN_DAY_GIFT_INFO_SC			= 2721,	// 7�콱����Ϣ����
		MT_HUNT_RARE_TIME_SC				= 2722, // ��Ѱ��N�λ�������Ʒ
		MT_OSC_INFO_SC						= 2723, // ����������Ϣ����
		MT_OPR_RESULT_SC					= 2724, // �����������(1722->2724)
		MT_ICON_OPEN_SC						= 2725,	// �Ϸ�ͼ�꿪��֪ͨ
		MT_TITLE_PUT_ON_CHANGE				= 2726,	// ͷ���ƺŸı�
		MT_YELLOW_VIP_INFO_CHANGE_SC		= 2727,	// �㲥������Ϣ�ı�
		MT_VIP_TODAY_RECHARGE_STATE_SC		= 2728, // ���ճ�ֵ���״̬
		MT_VIP_SEVEN_DAY_REBATE_STATE_SC	= 2729, // ���췵��״̬
		MT_OTHER_ACTIVITY_ICON_STATE_SC		= 2730,	// ��ʱ�ͼ��״̬
		MT_LOGIN_ACTIVITY_GIFTBAG_STATE_SC	= 2731,	// ��¼����״̬
		MT_WEDDING_FERE_INFO_SC				= 2732, // ��������Ϣ
		MT_WEDDING_RING_INFO_SC				= 2733, // ��ָ��Ϣ
		MT_WEDDING_FERE_INFO_BROADCAST_SC	= 2734, // ������Ϣ�㲥
		MT_ASSIGN_MONSTER_ACTIVITY_SC		= 2735,	// ָ������˫���

		MT_LIANQI_UPGRADE_CS				= 2750, // ��������
		MT_SIGNIN_REQ_CS					= 2751,	// ǩ������
		MT_SIGNIN_PATCH_CS					= 2752,	// ��ǩ����
		MT_SIGNIN_GET_REWARDS_CS			= 2753,	// ��ȡǩ���������
		MT_NEILI_BREAK_CS					= 2754,	// ����ͻ��
		MT_NEILI_UPGRADE_CS					= 2755,	// ��������
		MT_PUT_ON_TITLE_CS					= 2756,	// װ���ƺ�
		MT_TAKE_OFF_TITLE_CS				= 2757,	// ���سƺ�
		MT_ONLINE_REWARD_INFO_CS			= 2758,	// �������߽�����Ϣ
		MT_GET_ONLINE_REWARD_CS				= 2759,	// ��ȡ���߽���
		MT_MONEY_TREE_GET_COIN_CS			= 2760,	// ʹ���в����в�
		MT_TREASURE_HUNT_CS					= 2761,	// ����Ѱ��
		MT_EXCHANGE_ITEM_CS					= 2762,	// �һ���Ʒ
		MT_RECHARGE_10_GIFT_CS				= 2763,	// ��ȡ�׳�10Ԫ
		MT_MONEY_TREE_GET_INFO_CS			= 2764,	// ����в�����Ϣ
		MT_CONSUME_GIFT_BAG_INFO_CS			= 2765, // �������
		MT_GET_CONSUME_GIFT_BAG_CS			= 2766, // ��ȡ�������
		MT_MYSTERY_SHOP_INFO_CS				= 2767, // ���������̵���Ϣ
		MT_MYSTERY_SHOP_REFRESH_CS			= 2768, // ����ˢ�������̵�
		MT_MYSTERY_SHOP_BUY_ITEM_CS			= 2769, // �����̵깺����Ʒ
		MT_AIM_GET_INFO_CS					= 2770,	// ���Ŀ����Ϣ
		MT_AIM_GET_REWARD_CS				= 2771,	// ��ȡĿ�꽱��
		MT_GET_HUNT_INFO_CS					= 2772, // ��ø���Ѱ���ſ�
		MT_TRADE_LOCK_ITEM_CS				= 2773, // ������Ʒ
		MT_SIGNIN_GET_REWARD_PET_CS			= 2774,	// ��ȡǩ����������
		MT_VIP_GET_LEVEL_REWARD_CS			= 2775,	// ��ȡVip�ȼ�����
		MT_YELLOW_VIP_GET_XINSHOU_GIFT_CS	= 2776,	// ��ȡ�����������
		MT_YELLOW_VIP_GET_DAILY_GIFT_CS		= 2777,	// ��ȡ����ÿ�����
		MT_YELLOW_VIP_GET_GROWTH_GIFT_CS	= 2778,	// ��ȡ����ɳ����
		MT_YELLOW_VIP_GET_PET_GIFT_CS		= 2779,	// ��ȡ����������
		MT_YELLOW_VIP_INFO_CS				= 2780,	// ������Ϣ
		MT_CAMP_POINTS_EXCHANGE_ITEM_CS		= 2781,	// ��Ӫս���ֶһ���Ʒ(���� 2014.06.11)
		MT_SEVEN_DAY_GIFT_INFO_CS			= 2782,	// 7�������Ϣ
		MT_SEVEN_DAY_GIFT_GET_GIFT_CS		= 2783, // ��ȡ7�����
		MT_OSP_BUY_MOUNT_CS					= 2784, // �����Ź���������
		MT_OSP_BUY_WING_CS					= 2785,	// �����Ź�������
		MT_FIRST_RECHARGE_INFO_CS			= 2786,	// �׳���Ϣ
		MT_FIRST_RECHARGE_GET_GIFT_CS		= 2787,	// ��ȡ�׳佱��
		MT_OSP_INFO_CS						= 2788,	// �����Ź���Ϣ
		MT_BUY_POWER_CS						= 2789, // ��������
		MT_USE_LOUDSPEAKER_CS				= 2790,	// ʹ��С����
		MT_OSC_INFO_CS						= 2791, // ����������Ϣ
		MT_OSC_GET_REWARD_CS				= 2792,	// ��ȡ�������׽���
		MT_VIP_GET_TODAY_RECHARGE_GIFT_CS	= 2793, // ��ȡ���ճ�ֵ����
		MT_VIP_GET_REBATE_CS				= 2794,	// ��ȡ����
		MT_LOGIN_ACTIVITY_GET_GIFTBAG_CS	= 2795,	// ��ȡ��¼����
		MT_WEDDING_RING_UPGRADE_CS			= 2796, // ��ָ����	
		MT_USE_RAND_PAPER_CS				= 2797,	// ʹ�������

		// �̳�
		MT_SHOP_GLOD_BUY_CS					= 2850,	// �̳ǹ���
		// �̵�
		MT_STORE_BUY_ITEM_CS				= 2851,	// �̵깺��
		MT_STORE_SELL_ITEM_CS				= 2852, // �̵����

		// ����2
		MT_LUCKY_COMPASS_RESULT_SC			= 2900,	// ת�̽��

		MT_LUCKY_COMPASS_ROTATE_CS			= 2950,	// ת��ת��

		// ����ϵͳ
		MT_MOUNT_INFO_SC					= 5200,	// �����ӦЭ��
		MT_MOUNT_AVATAR_LIST_SC				= 5201,	// ���������б�
		MT_MOUNT_OVER_SC					= 5202,	// �����ﷵ��
		MT_MOUNT_OFF_SC						= 5203,	// �����ﷵ��
		MT_MOUNT_COLLECTION_SC				= 5204,	// �����ռ��������
		MT_MOUNT_ADD_MOUNT_SC				= 5205,	// ����µĻû�����

		MT_MOUNT_INFO_REQ_CS				= 5250,	// ��������Э��
		MT_MOUNT_UPGRADE_EXP_CS				= 5251,	// ��������
		MT_MOUNT_UPGRADE_HUASHEN_CS			= 5252,	// ��������
		MT_MOUNT_UPGRADE_TRAIN_CS			= 5253,	// ��������
		MT_MOUNT_CTEATE_REQ_CS				= 5254,	// ���Դ�������
		MT_MOUNT_CHANGE_AVATAR_CS			= 5255,	// ����
		MT_MOUNT_OVER_CS					= 5256,	// ������
		MT_MOUNT_OFF_CS						= 5257,	// ������
		MT_MOUNT_UPGRADE_EXP_TEN_CS			= 5258, // ����10�ξ���
		// ���ϵͳ
		MT_WING_INFO_SC						= 5300,	// ������
		MT_WING_SKILL_LIST_SC				= 5301,	// �����б�
		MT_WING_INFO_REQ_CS					= 5350,	// �ͻ���
		MT_WING_UPGRADE_REQ_CS				= 5351,	// ����
		MT_WING_STAR_UP_REQ_CS				= 5352,	// ����
		MT_WING_UPGRADE_SKILL_REQ_CS		= 5353,	// ������
		MT_WING_CHANGE_AVATAR_REQ_CS		= 5354,	// ����
		MT_WING_CREATE_REQ_CS				= 5355,	// �������
		MT_WING_MOUNT_ON_OFF_CS				= 5356,	// ���³��
		// �ʼ�
		MT_MAIL_SEND_CS						= 5371,	// �����ʼ�
		// ����
		MT_ARMY_CREATE_REQ_CS				= 5400, // ��������
		MT_ARMY_IMPEACH_LEADER_CS			= 5401,	// ��������
		MT_ARMY_DONATE_CS					= 5402,	// ���ɾ���
		MT_ARMY_SHENTAN_SHANGXIANG_CS		= 5403, // ������̳����
		MT_ARMY_STORAGE_DEPOSIT_CS			= 5404,	// ���ɲֿ������Ʒ
		MT_ARMY_STORAGE_GET_ITEM_CS			= 5405,	// ��ȡ���ɲֿ���Ʒ
		MT_ARMY_ENTER_BOSS_SCENE_CS			= 5406, // ������ɳ���
		// ����
		MT_FABAO_INFO_REQ_CS				= 5500,	// ������Ϣ����
		MT_FABAO_SOUL_GRID_INFO_CS			= 5501,	// ����������Ϣ
		MT_FABAO_ADDEXP_CS					= 5502,	// ��������
		MT_FABAO_CALL_SOUL_CS				= 5503, // �����ٻ�
		MT_FABAO_HUNT_SOUL_CS				= 5504, // �����Ի�
		MT_FABAO_ONE_KEY_HUNT_SOUL_CS		= 5505, // һ���Ի�
		MT_FABAO_SOUL_MOVE_CS				= 5506, // �ƶ�ս��
		MT_FABAO_ONE_KEY_DEVOUR_HOUL_CS		= 5507, // һ������ս��
		MT_FABAO_UNLOCK_SOUL_GRID_CS		= 5508, // ����������
		MT_FABAO_SOUL_EXCHANGE_CS			= 5509, // ս��һ�
		MT_FABAO_INFO_SC					= 5550, // ����������Ϣ
		MT_FABAO_SOUL_GRID_INFO_SC			= 5551,	// ����������Ϣ
		MT_FABAO_EXP_CHANGE_SC				= 5552,	// ��������ı�
		MT_FABAO_HUNT_SOUL_STATE_SC			= 5553,	// �����Ի�״̬
		MT_FABAO_SOUL_GRID_CHANGE_SC		= 5554,	// �������������Ʒ�ı�
		MT_FABAO_SOUL_GRID_ADD_SC			= 5555, // ����������ø�������
		MT_FABAO_CAPABILITY_SC				= 5556, // ս������
		MT_FABAO_SOUL_FRAGMENT_NUM_SC		= 5557, // ս����Ƭ��������

		// �
		MT_FRUIT_BATTLE_CS					= 5600, // ����ˮ����ս
		MT_FRUIT_BATTLE_USE_FRUIT_CS		= 5601,	// ʹ��ˮ��
		MT_FRUIT_BATTLE_USE_AOE_FRUIT_CS	= 5602, // ʹ��AOEˮ��
		MT_FRUIT_BATTLE_REWARD_CS			= 5603,	// ��ȡˮ����ս����
		MT_CAMP_BATTLE_ENTER_CS				= 5604, // ������Ӫս
		MT_CAMP_BATTLE_REWARD_CS			= 5605,	// ��ȡ��Ӫս����
		MT_MIDAUTUMN_GET_LOGIN_GIFT_CS		= 5606, // ��ȡ�����¼����
		MT_MIDAUTUMN_BUY_LUXURY_GIFT_CS		= 5607,	// ��������������
		MT_MIDAUTUMN_PANEL_INFO_CS			= 5608,	// ���������Ϣ
		MT_BAGUA_ENTER_CS					= 5609,	// ���������
		MT_BAGUA_GET_REWARD_CS				= 5610, // ��ȡ����������
		MT_NATIONALDAY_PAEEL_INFO_CS		= 5611, // ���������Ϣ
		MT_NATIONALDAY_BUY_LUXURY_GIFT_CS	= 5612,	// ��������������
		MT_NATIONALDAY_GET_LOGIN_GIFT_CS	= 5613, // ������ȡ���
		MT_WORLD_FIRST_ENTER_CS				= 5614, // �������µ�һ
		MT_WORLD_FIRST_REWARD_CS			= 5615, // ��ȡ���µ�һ����
		MT_BUY_ACTIVITY_GIFT_BAG_CS			= 5616, // �������	
		MT_ARMY_BATTLE_ENTER_CS				= 5617,	// �������ս
		MT_ARMY_BATTLE_REWARD_CS			= 5618, // ��ȡ����ս����

		MT_FRUIT_BATTLE_INFO_SC				= 5650,	// ˮ����ս�����Ϣ
		MT_FRUIT_BATTLE_FRUIT_INFO_SC		= 5651,	// ˮ����ս������Ϣ
		MT_FRUIT_BATTLE_ALL_FRUIT_INFO_SC	= 5652, // ˮ����ս���м�����Ϣ
		MT_FRUIT_BATTLE_SKILL_SC			= 5653,	// �㲥����
		MT_FRUIT_BATTLE_ROLE_HP_SC			= 5654, // ����Ѫ��
		MT_FRUIT_BATTLE_RANK_LIST_SC		= 5655,	// ʹ��ˮ���ɹ�
		MT_FRUIT_BATTLE_REWARD_SC			= 5656,	// ˮ����ս����
		MT_FRUIT_BATTLE_REWARD_RESULT_SC	= 5657,	// ��������
		MT_CAMP_BATTLE_PANEL_INFO_SC		= 5658,	// ��Ӫս�����Ϣ
		MT_CAMP_BATTLE_PERSONAL_INFO_SC		= 5659, // ��Ӫս������Ϣ
		MT_CAMP_BATTLE_REWARD_SC			= 5660,	// ��Ӫս����
		MT_CAMP_BATTLE_CAMP_INFO_SC			= 5661, // ��Ӫ��Ϣ
		MT_CAMP_BATTLE_CAMP_POINT_SC		= 5662, // ��Ӫ����
		MT_MIDAUTUMN_LOGIN_GIFT_INFO_SC		= 5663, // ������¼�����Ϣ
		MT_MIDAUTUMN_LUXURY_GIFT_INFO_SC	= 5664, // �������������Ϣ
		MT_MIDAUTUMN_LUXURY_GIFT_CHANGE_SC	= 5665,	// �������������Ϣ�ı�
		MT_BAGUA_TASK_SC					= 5666,	// ����������
		MT_BAGUA_ALL_TASK_SC				= 5667,	// ��������������
		MT_BAGUA_GET_REWARD_ERR_SC			= 5668, // ��ȡ�������������󷵻�
		MT_NATIONALDAY_LOGIN_GIFT_INFO_SC	= 5669, // �����¼�����Ϣ
		MT_NATIONALDAY_LUXURY_GIFT_INFO_SC	= 5670, // ������������Ϣ
		MT_NATIONALDAY_LUXURYGIFT_CHANGE_SC	= 5671,	// ������������Ϣ�ı�
		MT_WORLD_FIRST_PANEL_INFO_SC		= 5672, // ���µ�һ�����Ϣ
		MT_WORLD_FIRST_PERSONAL_INFO_SC		= 5673,	// ���µ�һ������Ϣ
		MT_WORLD_FIRST_REWARD_SC			= 5674,	// ���µ�һ����
		MT_ARMY_BATTLE_PERSONAL_INFO_SC		= 5675,	// ����ս������Ϣ
		MT_ARMY_BATTLE_PANEL_INFO_SC		= 5676,	// ����ս�����Ϣ
		MT_ARMY_BATTLE_FIRST_ARMY_INFO_SC	= 5677,	// ������һ������Ϣ
		MT_ARMY_BATTLE_ARMY_INFO_SC			= 5678, // ��������Ϣ
		MT_ARMY_BATTLE_REWARD_SC			= 5679,	// ����ս����


		/************************************************************************/
		// login server
		MT_LOGIN_ACK_SC						= 7000,	// ��½����ظ�
		MT_LOGIN_ERR_SC						= 7001,	// ��¼����ظ�
		MT_LOGIN_REQ_CS						= 7050,	// ��½����
		MT_LOGIN_CREATE_ROLE_CS				= 7150,	// ������ɫ
		/************************************************************************/
		// chat server
		MT_USER_LOGIN_ACK_SC				= 8000,	// ��¼���������
		MT_USER_BE_DESTROY_SC				= 8001,	// �û�������
		MT_INTO_CHANNEL_SC					= 8002,	// �û�����Ƶ��
		MT_OUT_OF_CHANNEL_SC				= 8003,	// �û��Ƴ�Ƶ��
		MT_NOTICE_ONLINE_SC					= 8004,	// ����֪ͨ
		MT_NOTICE_OFFLINE_SC				= 8005,	// ����֪ͨ
		MT_USER_LOGIN_CS					= 8050,	// ��¼�����
		MT_MUTE_USER_CS						= 8051,	// ����
		MT_UNMUTE_USER_CS					= 8052,	// ȡ������
		MT_CHANNEL_CHAT_SC					= 8100,	// Ƶ������
		MT_SINGLE_CHAT_SC					= 8101,	// ˽��
		MT_SINGLE_CHAT_USET_NOT_EXIST_SC	= 8102,	// �û�������
		MT_CHANNEL_CHAT_CS					= 8150,	// Ƶ������
		MT_SINGLE_CHAT_CS					= 8151,	// ˽��
		/************************************************************************/
		// global server
		MT_ENTER_GLOBAL_SERVER_ACK_SC		= 9000,	// ��½ȫ�ַ������ظ�
		MT_TIME_ACK_SC						= 9001,	// ������ʱ��
		MT_WALLOW_NOTICE_SC					= 9002,	// �����Է���
		MT_USER_KICKOUT_SC					= 9003,	// ��ұ�����
		MT_PUBLIC_NOTICE_SC					= 9004,	// ȫ������
		MT_ENTER_GLOBAL_SERVER_REQ_CS		= 9050,	// �����½ȫ�ַ�����
		MT_TIME_REQ_CS						= 9051,	// ���������ʱ��
		// ���
		MT_TEAM_INFO_SC						= 9100,	// ������Ϣ
		MT_TEAM_TEAM_LIST_SC				= 9101,	// ����������Ϣ
		MT_TEAM_USER_LIST_SC				= 9102,	// ���������Ϣ
		MT_TEAM_CREATE_SC					= 9103,	// �������
		MT_TEAM_JOIN_SC						= 9104,	// ת�����ӳ��������
		MT_TEAM_RSP_JOIN_SC					= 9105,	// ���������
		MT_TEAM_QUIT_SC						= 9106,	// �˳�������
		MT_TEAM_INVITE_SC					= 9107,	// �������
		MT_TEAM_RSP_INVITE_SC				= 9108,	// ����������
		MT_TEAM_KICK_SC						= 9109,	// ���͸��������
		MT_TEAM_TEAM_STATE_SC				= 9110, // ����״̬����
		MT_TEAM_ENTER_TEAM_FB_ERROR_SC		= 9111,	// ������Ӹ���������Ϣ
		MT_TEAM_INFO_CS						= 9150,	// ���������Ϣ
		MT_TEAM_USER_LIST_CS				= 9152,	// ���󸽽����
		MT_TEAM_CREATE_CS					= 9153,	// ���󴴽�����
		MT_TEAM_JOIN_CS						= 9154,	// ����������
		MT_TEAM_RSP_JOIN_CS					= 9155,	// �ظ���Ҽ����������
		MT_TEAM_QUIT_CS						= 9156,	// �����˳�����
		MT_TEAM_RSP_INVITE_CS				= 9158,	// �ظ������������
		MT_TEAM_KICK_CS						= 9159,	// �����޳����
		MT_TEAM_APPOINT_LEADER_CS			= 9160,	// ί�ζӳ�
		MT_TEAM_SET_TEAM_STATE_CS			= 9161, // �������״̬���Ƿ����������ӵȣ�
		MT_TEAM_ENTER_TEAM_FB_CS			= 9162,	// ������Ӹ���
		// ����
		MT_ARMY_LIST_SC						= 9200,	// �����б�
		MT_ARMY_INFO_SC						= 9201,	// ������Ϣ����
		MT_ARMY_APPLY_LIST_SC				= 9202,	// ���������б���
		MT_ARMY_INVITE_INFO_SC				= 9203,	// ������������Ϣ����
		MT_ARMY_POST_CHANGE_SC				= 9204,	// ְλ�������
		MT_ARMY_MODIFY_YY_SC				= 9205,	// �޸�yy����(����2015.04.24)
		MT_ARMY_MODIFY_QQ_SC				= 9206,	// �޸�qq����(����2015.04.24)
		MT_ARMY_MODIFY_NOTICE_SC			= 9207,	// �޸Ĺ��淵��
		MT_ARMY_ADD_MEMBER_SC				= 9208,	// ��ӳ�Ա
		MT_ARMY_REMOVE_MEMBER_SC			= 9209,	// ɾ����Ա
		MT_ARMY_AGREE_JOIN_ARMY_SC			= 9210,	// ͬ��������
		MT_ARMY_REFUSE_JOIN_ARMY_SC			= 9211,	// �ܾ��������
		MT_ARMY_MONEY_CHANGE_SC				= 9212,	// �����ʽ�ı�
		MT_ARMY_PERSONAL_INFO_SC			= 9213,	// ���������Ϣ
		MT_ARMY_APPLY_LIST_ADD_SC			= 9214,	// �����б����ӳ�Ա
		MT_ARMY_APPLY_LIST_DELETE_SC		= 9215,	// �����б�ɾ����Ա
		MT_ARMY_MEMBER_UPGRADE_SC			= 9216,	// ��Ա����
		MT_ARMY_MEMBER_LOGIN_SC				= 9217,	// ��Ա����
		MT_ARMY_MEMBER_LOGOUT_SC			= 9218,	// ��Ա����
		MT_ARMY_MEMBER_CAPACITY_SC			= 9219,	// ��Աս�����ı�
		MT_ARMY_LIST_ADD_SC					= 9220,	// �����б�����
		MT_ARMY_LIST_DELETE_SC				= 9221,	// �����б�ɾ��
		MT_ARMY_LIST_CHANGE_SC				= 9222,	// �����б�ı�
		MT_ARMY_SHENTAN_INFO_SC				= 9223,	// ��̳��Ϣ����
		MT_ARMY_SHENTAN_EVENT_LIST_SC		= 9224,	// ��̳�¼��б���
		MT_ARMY_SHENTAN_EVENT_ADD_SC		= 9225,	// ��̳�¼�����
		MT_ARMY_BASE_INFO_CHANGE_SC			= 9226,	// ���ɻ�����Ϣ����
		MT_ARMY_EVENT_LIST_SC				= 9227,	// �����¼�����
		MT_ARMY_EVENT_ADD_SC				= 9228,	// �����¼�����
		MT_ARMY_PERSONAL_CONTRIBUTION_SC	= 9229,	// ���˹��׷���
		MT_ARMY_GET_WELFARE_STATE_SC		= 9230,	// ��ȡ����״̬
		MT_ARMY_BUILD_INFO_SC				= 9231,	// ���ɽ����ȼ�����
		MT_ARMY_STORAGE_INFO_SC				= 9232,	// ���ɲֿ���Ϣ����
		MT_ARMY_STORAGE_ITEM_CHANGE_SC		= 9233,	// ���ɲֿ���Ʒ�ı�
		MT_ARMY_STORAGE_GET_ITEM_TIME_SC	= 9234,	// ���ɻ�ȡ��Ʒ����
		MT_ARMY_SHENTAN_LEVEL_SC			= 9235,	// ��̳�ȼ������ڿͻ�����ʾbuff
		MT_ARMY_MEMBER_CONTRIB_CHANGE_SC	= 9236,	// �ﹱ�仯
		MT_ARMY_JOIN_TIME_COOL_DOWN_SC		= 9237,	// ���������ȴʱ�䣬�˳����ɵڶ����������
		MT_ARMY_BOSS_STATE_SC				= 9238, // ����BOSS״̬
		MT_ARMY_SHANGXIANG_COUNT_SC			= 9239,	// �������

		MT_ARMY_LIST_CS						= 9250,	// ��������б�
		MT_ARMY_INFO_REQ_CS					= 9251,	// ���������Ϣ
		MT_ARMY_APPLY_LIST_REQ_CS			= 9252,	// ����鿴�����б�
		MT_ARMY_REFUSE_APPLY_CS				= 9253,	// �ܾ�����������
		MT_ARMY_DELETE_REQ_CS				= 9254,	// ����ɾ������
		MT_ARMY_APPLY_REQ_CS				= 9255,	// ����������
		MT_ARMY_AGREE_APPLY_CS				= 9256,	// ͬ������������
		MT_ARMY_AGREE_ALL_CS				= 9257,	// ͬ����������
		MT_ARMY_REFUSE_ALL_CS				= 9258,	// �ܾ���������
		MT_ARMY_QUIT_REQ_CS					= 9259,	// �����˳�����
		MT_ARMY_INVITE_CS					= 9260,	// ����������
		MT_ARMY_INVITE_REPLY_CS				= 9261,	// ���������ɻظ�
		MT_ARMY_APPOINT_POST_CS				= 9262,	// ����ְλ
		MT_ARMY_DISMISS_POST_CS				= 9263,	// ����ְλ
		MT_ARMY_KICK_OUT_MEMBER_CS			= 9264,	// �߳���Ա
		MT_ARMY_MODIFY_YY_CS				= 9265,	// �޸�yy(����2015.04.24)
		MT_ARMY_MODIFY_QQ_CS				= 9266,	// �޸�qq(����2015.04.24)
		MT_ARMY_MODIFY_NOTICE_CS			= 9267,	// �޸Ĺ���
		MT_ARMY_GET_WELFARE_CS				= 9268,	// ��ȡ���ɸ���
		MT_ARMY_MAIN_UPGRADE_CS				= 9269,	// ��������
		MT_ARMY_SMITHY_UPGRADE_CS			= 9270,	// ����������
		MT_ARMY_KONGFU_UPGRADE_CS			= 9271,	// ����������
		MT_ARMY_SHOP_UPGRADE_CS				= 9272,	// �̵�����
		MT_ARMY_ALTAR_UPGRADE_CS			= 9273,	// ��̳����
		MT_ARMY_SHENTAN_INFO_REQ_CS			= 9274,	// ������̳��Ϣ
		MT_ARMY_EVENT_LIST_REQ_CS			= 9275,	// �����¼�
		MT_ARMY_BUILD_INFO_REQ_CS			= 9276,	// ������Ϣ����
		MT_ARMY_STORAGE_INFO_REQ_CS			= 9277,	// ������ɲֿ���Ϣ
		MT_ARMY_STORAGE_ARRANGE_CS			= 9278,	// ���ɲֿ�����
		MT_ARMY_CALL_BOSS_CS				= 9279,	// �����ٻ�BOSS
		MT_ARMY_BUY_SHOP_ITEM_CS			= 9280,	// ���ɹ�����Ʒ

		// ���а�
		MT_RANK_LIST_ROLE_CAPACITY_SC		= 9300,	// ����ս����������
		MT_RANK_LIST_ROLE_LEVEL_SC			= 9301,	// ����ȼ���������
		MT_RANK_LIST_FABAO_CAPACITY_SC		= 9302,	// ����ս����������
		MT_RANK_LIST_WING_CAPACITY_SC		= 9303,	// ���ս����������
		MT_RANK_LIST_PET_CAPACITY_SC		= 9304,	// ����ս����������
		MT_RANK_LIST_MOUNT_CAPACITY_SC		= 9305,	// ����ս����������
		MT_RANK_OWN_RANK_SC					= 9306, // ����������Ϣ
		MT_RANK_LIST_ROLE_CHARM_SC			= 9307, // ����������������
		MT_RANK_DETAIL_PERSON_SC			= 9308,	// ������ϸ��Ϣ
		MT_RANK_DETAIL_FABAO_SC				= 9309, // ������ϸ��Ϣ
		//MT_RANK_DETAIL_PET_SC				= 9310, // ������ϸ��Ϣ

		MT_RANK_LIST_REQ_CS					= 9350,	// �������а�����
		MT_RANK_OWN_RANK_CS					= 9351,	// �鿴��������
		MT_RANK_DETAIL_INFO_CS				= 9352, // ������ϸ��Ϣ

		// ������
		MT_ARENA_ROLE_INFO_SC				= 9400,	// ������������Ϣ
		MT_ARENA_HERO_RANK_SC				= 9401,	// ������Ӣ�۰�
		MT_ARENA_KEEP_WIN_RANK_SC			= 9402,	// ��������ʤ��
		MT_ARENA_OPPONENT_LIST_SC			= 9403,	// �����б�
		MT_ARENA_FIGHT_MSG_SC				= 9404,	// ��ս��Ϣ
		MT_ARENA_REWARD_RANK_SC				= 9405,	// ������

		MT_ARENA_INFO_REQ_CS				= 9450,	// ���󾺼�����Ϣ
		MT_ARENA_BROCAST_CS					= 9451, // �������㲥
		MT_ARENA_GET_REWARD_CS				= 9452,	// ��ȡ���߾���������
		MT_ARENA_ON_FIGHT_CS				= 9453,	// �����ս
		MT_ARENA_CLEAR_CHALLENGE_TIME_CS	= 9454,	// ������սʱ��
		MT_ARENA_ADD_CHALLENGE_COUNT_CS		= 9455,	// ������ս����

		// �ʼ�
		MT_MAIL_LIST_SC						= 9800,	// �ʼ��б�
		MT_MAIL_DETAIL_SC					= 9801,	// �ʼ�����
		MT_MAIL_DELETE_SC					= 9803,	// ɾ�����
		MT_MAIL_GET_EXTRA_SC				= 9804,	// ��ȡ���
		MT_MAIL_GET_EXTRA_ALL_SC			= 9805,	// ��ȡȫ�����
		MT_MAIL_NEW_MAIL_SC					= 9806,	// ���ʼ�
		MT_MAIL_EXTRA_NORMAL_SC				= 9807,	// ��ͨ��Ʒ����
		MT_MAIL_EXTRA_EQUIP_SC				= 9808,	// װ������
		MT_MAIL_FLASH_SC					= 9810,	// ��ʾ�ʼ���˸
		MT_MAIL_SEND_RESULT_SC				= 9811,	// �����ʼ����
		MT_MAIL_LIST_CS						= 9850,	// �����ʼ�
		MT_MAIL_DETAIL_CS					= 9851,	// �����ʼ�����
		MT_MAIL_DELETE_CS					= 9853,	// ����ɾ���ʼ�
		MT_MAIL_GET_EXTRA_CS				= 9854,	// ������ȡ����
		MT_MAIL_GET_EXTRA_ALL_CS			= 9855,	// ������ȡȫ������
		// ����
		MT_FRIEND_MEMBER_LIST_SC			= 9900,	// �����б����Ϣ
		MT_FRIEND_ADD_REQ_SC				= 9901,	// ����ӶԷ�Ϊ����
		MT_FRIEND_ADD_REPLY_SC				= 9902,	// �𸴼Ӻ��ѽ��������
		MT_FRIEND_ADD_MEMBER_SC				= 9903,	// �б���ӳ�Ա����
		MT_FRIEND_DEL_MEMBER_SC				= 9904,	// ɾ������
		MT_FRIEND_LOGIN_SC					= 9905,	// ��������
		MT_FRIEND_LOGOUT_SC					= 9906,	// ��������
		MT_FRIEND_UPGRADE_SC				= 9907,	// ��������
		MT_FRIEND_CHAT_SC					= 9908, // �������췵��
		MT_FRIEND_SHAKE_SC					= 9909, // ���Ѵ��ڶ�������
		MT_FRIEND_CHAT_INFO_SC				= 9910,	// ����ʱ����Է���Ϣ����	
		MT_FRIEND_MEMBER_LIST_REQ_CS		= 9950,	// �򿪺���ϵͳ���
		MT_FRIEND_ADD_REQ_CS				= 9951,	// ��Ӻ���
		MT_FRIEND_ADD_REPLY_CS				= 9952,	// �Է��ظ��������
		MT_FRIEND_DEL_MEMBER_CS				= 9953,	// ɾ����Ա
		MT_FRIEND_CONGRATULATE_CS			= 9954,	// ף�غ�������
		MT_FRIEND_BATCH_ADD_REQ_CS			= 9955,	// �����Ӻ���
		MT_FRIEND_CHAT_CS					= 9956,	// ��������
		MT_FRIEND_SHAKE_CS					= 9957,	// ���Ѵ��ڶ���
		MT_FRIEND_CHAT_INFO_CS				= 9958, // ����ʱ����Է���Ϣ
		// �г�
		MT_MARKET_ALL_GOODS_SC				= 10000,
		MT_MARKET_ALL_MY_GOODS_SC			= 10001,
		MT_MARKET_ON_SHELF_GOODS_SC			= 10002,
		MT_MARKET_ON_SHELF_MY_GOODS_SC		= 10003,
		MT_MARKET_OFF_SHELF_GOODS_SC		= 10004,
		MT_MARKET_ALL_GOODS_CS				= 10050,
		MT_MARKET_ALL_MY_GOODS_CS			= 10051,
		MT_MARKET_BUY_GOODS_CS				= 10052,
		MT_MARKET_ON_SHELF_ITEM_CS			= 10053,
		MT_MARKET_ON_SHELF_MONEY_CS			= 10054,
		MT_MARKET_OFF_SHELF_GOODS_CS		= 10055,
		// ����
		MT_MYSTERY_SHOP_EVENT_INFO_SC		= 10100,// ��������Ϣ����
		MT_MYSTERY_SHOP_ADD_EVENT_SC		= 10101,// ������������Ŀ
		MT_TREASURE_HUNT_EVENT_INFO_SC		= 10102,// Ѱ����Ʒ��¼��Ϣ����
		MT_TREASURE_HUNT_ADD_EVENT_SC		= 10103,// Ѱ����Ʒ��¼������Ŀ
		MT_FLOWER_OFFLINE_SC				= 10104,// �Է�����
		MT_FLOWER_GIVE_SUCCESS_SC			= 10105,// ���ͳɹ�
		MT_FLOWER_GIVE_SUCCESS_BROADCAST_SC	= 10106,// ���������ʻ���Ч
		MT_VIEW_ROLE_INFO_RET_SC			= 10107,// �鿴���Ϸ���
		MT_SEND_LOUDSPEAKER_MSG_SC			= 10108,// ����С������Ϣ
		MT_OTHER_LOGOUT_SC					= 10109,// �Է����߷���
		MT_SERVER_NOTICE_SC					= 10110,// ����������
		MT_ACTIVITY_STATE_NOTICE_SC			= 10111,// ���ʼ����
		MT_ARMY_NOTICE_SC					= 10112,// ���ɹ���
		MT_TL_ACTIVITY_ICON_STATE_SC		= 10113,// ��ʱ�ͼ��״̬
		MT_SEND_COMMAND_TO_CLIENT_SC		= 10114,// ����������ͻ���
		MT_WAS_FINISH_TIME_SC				= 10115,// ȫ�����ɴ���

		MT_TREASURE_HUNT_EVENT_INFO_CS		= 10150,// ����Ѱ���䱦��¼
		MT_FLOWER_GIVE_CS					= 10151,// �����ʻ�
		MT_VIEW_ROLE_INFO_CS				= 10152,// �鿴����
		// ����ϵͳ
		MT_TRADE_REQ_CS						= 10200, // ������
		MT_TRADE_REPLY_REQ_CS				= 10201, // �ظ�����
		MT_TRADE_AFFIRM_TRADE_CS			= 10202, // ȷ�Ͻ���
		MT_TRADE_CANCEL_CS					= 10203, // ȡ������
		MT_TRADE_REQ_SC						= 10250, // ������
		MT_TRADE_REPLY_REQ_SC				= 10251, // �ظ�����
		MT_TRADE_LOCK_ITEM_SC				= 10252, // ������Ʒ
		MT_TRADE_AFFIRM_TRADE_SC			= 10253, // ȷ�Ͻ���
		MT_TRADE_CANCEL_SC					= 10254, // ȡ������

		// ���
		MT_WEDDING_PROPOSAL_REQ_CS			= 10300,// ������
		MT_WEDDING_PROPOSAL_REPLY_CS		= 10301,// �ظ�������
		MT_WEDDING_DIVORCE_CS				= 10302,// ���

		MT_WEDDING_PROPOSAL_REQ_SC			= 10350,// ������
		MT_WEDDING_NOTICE_SC				= 10351,// �����Ϣ����
		// ϵͳ��Ϣ
		MT_SYSTEM_ERROR_CODE_SC				= 60000,// �����뷵��
		MT_SYSTEM_OPERATION_RESULT_SC		= 60001,// ��������
	};
}

#endif

