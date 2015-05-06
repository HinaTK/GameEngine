
#pragma once

#ifndef MSG_CODE_H
#define MSG_CODE_H

namespace EProtocol
{
	enum
	{
		/************************************************************************/
		MT_TEST_GM_COMMAND					= 500,	// 测试命令
		// 登录
		MT_SERVER_ENTER_SC					= 1000,	// 进入场景服务器
		MT_SERVER_CHANGE_SC					= 1001,	// 切换场景服务器
		MT_SERVER_INFO_SC					= 1002,	// 服务器信息
		MT_SERVER_ENTER_CS					= 1050,	// 请求进入场景服务器
		MT_SERVER_HEARTBEAT_CS				= 1053,	// 客户端心跳包
		// 场景
		MT_SCENE_ENTER_SC					= 1100,	// 进入场景
		MT_SCENE_LEAVE_SC					= 1101,	// 离开场景
		MT_SCENE_VISIBLE_ENTER_ROLE_SC		= 1102,	// Role对象进入可视区域
		MT_SCENE_VISIBLE_LEAVE_SC			= 1103,	// 对象退出可视区域
		MT_SCENE_OBJ_MOVE_SC				= 1104,	// 对象位置移动同步
		MT_SCENE_VISIBLE_ENTER_FALLING_SC	= 1105,	// 掉落对象进入可视区域
		MT_SCENE_VISIBLE_ENTER_MONSTER_SC	= 1106,	// 怪物对象进入可视区域
		MT_SCENE_VISIBLE_ENTER_PET_SC		= 1107,	// 宠物对象进入可视区域
		MT_SCENE_VISIBLE_ENTER_TRUCK_SC		= 1108,	// 镖车对象进入可视区域
		MT_SCENE_VISIBLE_ENTER_GATHER_SC	= 1109,	// 采集物品进入可视区域
		MT_SCENE_SMALL_SHOE_SC				= 1110,	// 使用小飞鞋结果
		MT_SCENE_RESET_POSI_SC				= 1111,	// 重置自己位置
		MT_FB_PANEL_INFO_SC					= 1112,	// 副本面板信息返回
		MT_FB_ENTER_TIME_INFO_SC			= 1113, // 副本信息次数返回
		MT_FB_VDEMON_INFO_SC				= 1114,	// 降魔伏妖副本信息返回
		MT_FB_VDEMON_INFO_CHANGE_SC			= 1115, // 降魔伏妖副本信息改变返回
		MT_FB_VDEMON_FINISH_SC				= 1116,	// 扫荡结束，通知玩家领取奖励
		MT_FB_VDEMON_SWEEP_INFO_SC			= 1117,	// 扫荡信息
		MT_FB_DELEGATION_INFO_SC			= 1118,	// 委托信息返回
		MT_FB_DELEGATION_FINISH_SC			= 1119,	// 委托完成
		MT_SCENE_GATHER_RSP_SC				= 1120,	// 开始采集
		MT_SCENE_GATHER_SUCCESS_SC			= 1123,	// 采集成功
		MT_SCENE_OBJ_UPGRADE_SC				= 1124,	// 升级广播
		MT_FB_MONSTER_INFO_SC				= 1125,	// 怪物副本信息
		MT_FB_MONSTER_DIE_SC				= 1126,	// 副本怪物死亡
		MT_IS_ACCELERATING_SC				= 1127,	// 玩家正在加速

		MT_FB_ALL_ENTER_TIME_INFO_SC		= 1130,	// 所有副本进入次数信息返回
		MT_FB_VDEMON_HAS_GET_REWARD_SC		= 1131, // 降魔伏妖副本领取奖励返回(用于清空面板信息)
		MT_FB_DELEGATION_GET_REWARD_SC		= 1132, // 委托领奖返回
		MT_FB_FINISH_SC						= 1133,	// 副本通关完成
		MT_SCENE_FALLING_OWNER_CHANGE_SC	= 1136,	// 掉落归属变化
		MT_SCENE_REST_START_CS				= 1141,	// 请求开始打坐
		MT_SCENE_REST_START_SC				= 1142,	// 开始打坐结果
		MT_SCENE_REST_STOP_CS				= 1143,	// 请求结束打坐
		MT_SCENE_REST_STOP_SC				= 1144,	// 结束打坐结果
		MT_SCENE_REST_INVITE_CS				= 1145,	// 邀请双修
		MT_SCENE_REST_INVITE_SC				= 1146,	// 邀请双修 转发
		MT_SCENE_REST_INVITE_RESULT_CS		= 1147,	// 邀请结果C-S
		MT_SCENE_REST_INVITE_RESULT_SC		= 1148,	// 邀请结果S-C
		MT_SCENE_SING_STATUS_SC				= 1149,	// 吟唱状态

		MT_SCENE_ENTER_HOOK_CS				= 1152,	// 请求进入挂机地图
		MT_SCENE_TRANSPORT_CS				= 1153,	// 请求传送
		MT_SCENE_OBJ_MOVE_CS				= 1154,	// 玩家移动
		MT_SCENE_SMALL_SHOE_CS				= 1155,	// 使用小飞鞋
		MT_FB_TRIAL_ENTER_CS				= 1156, // 进入试炼副本
		MT_FB_EXP_ENTER_CS					= 1157,	// 进入经验副本
		MT_FB_PET_ENTER_CS					= 1158, // 进入宠物副本
		MT_FB_BOUNTY_ENTER_CS				= 1159, // 进入赏金副本
		MT_FB_BABEL_ENTER_CS				= 1160, // 进入通天秘境副本
		MT_FB_DREAMLAND_ENTER_CS			= 1161,	// 进入试炼幻境副本
		MT_FB_FABAO_ENTER_CS				= 1162,	// 进入法宝副本
		MT_FB_ENTER_TIME_INFO_CS			= 1163, // 进入副本次数信息请求
		MT_FB_EXIT_FB_CS					= 1164, // 请求退出副本
		MT_FB_ENTER_NEXT_SCENE_CS			= 1165, // 请求进入下一层
		MT_FB_DEFEND_ENTER_CS				= 1166,	// 进入防守副本
		MT_FB_VDEMON_ENTER_CS				= 1167,	// 进入降魔伏妖副本
		MT_FB_VDEMON_SWEEP_CS				= 1168, // 扫荡降魔伏妖副本
		MT_FB_VDEMON_CANCEL_SWEEP_CS		= 1169, // 取消扫荡
		MT_FB_VDEMON_INFO_CS				= 1170, // 请求降魔伏妖副本信息
		MT_FB_VDEMON_GET_REWARD_CS			= 1171,	// 请求领取降魔伏妖副本扫荡奖励
		MT_FB_DELEGATION_BEGIN_CS			= 1172,	// 副本委托开始
		MT_FB_DELEGATION_GET_REWARD_CS		= 1173, // 领取委托奖励
		MT_SCENE_ENTER_FIND_TREASURE_CS		= 1174,	// 进入打宝地图
		MT_FB_VDEMON_SWEEP_INFO_CS			= 1175,	// 打开扫荡面板
		MT_FB_DELEGATION_FINISH_NOW_CS		= 1176, // 立即完成委托
		MT_FB_DELEGATION_INFO_CS			= 1177,	// 打开委托副本面板（开始Update）
		MT_FB_DAYBREAK_ENTER_CS				= 1178,	// 进入试炼仙境
		MT_FB_NEWBIE_ENTER_CS				= 1179,	// 进入新手副本
		MT_SCENE_GATHER_REQ_CS				= 1180,	// 请求采集
		MT_FB_SHURA_ENTER_CS				= 1181, // 进入修罗道场
		MT_FB_MONSTERTOWER_ENTER_CS			= 1182,	// 进入镇妖塔
		MT_FB_OLDCEMETERY_ENTER_CS			= 1183,	// 进入葬神古域
		

		// 战斗相关
		MT_FIGHT_CHANGE_HP_SC				= 1300,	// 广播hp变化
		MT_FIGHT_PERFORM_SKILL_SC			= 1301,	// 释放技能
		MT_FIGHT_CHARA_DEAD_SC				= 1302,	// 死亡
		MT_FIGHT_ROLE_REALIVE_SC			= 1303,	// 重生
		MT_FIGHT_PERFORM_AOE_SKILL_SC		= 1304,	// 施放AOE技能，带目标地点
		MT_FIGHT_CHANGE_MP_SC				= 1305,	// 广播mp变化
		MT_FIGHT_BUFF_ADD_SC				= 1306,	// 增加buff
		MT_FIGHT_BUFF_DEL_SC				= 1307,	// 删除buff
		MT_FIGHT_FLY_SKY_SKILL_POS_SC		= 1308,	// 飞天连斩
		MT_FIGHT_PERFORM_SKILL_EX_SC		= 1312,	// 释放技能，带上播技能后人物位置，跳
		

		MT_FIGHT_PERFORM_AOE_SKILL_CS		= 1350,	// 释放AOE技能
		MT_FIGHT_PERFORM_SKILL_CS			= 1351,	// 施放技能
		MT_FIGHT_ROLE_REALIVE_CS			= 1352,	// 请求角色重生
		MT_FIGHT_CHANGE_PK_MODE_CS			= 1353,	// 改变pk模式

		// 角色信息相关
		MT_ROLE_BAS_INFO_SC					= 1400,	// 请求角色基本信息返回
		MT_ROLE_SKILL_INFO_SC				= 1401,	// 请求角色技能信息返回
		MT_ROLE_ATTR_VALUE_SC				= 1402,	// 角色属性数值通知
		MT_ROLE_SKILL_LEARN_SC				= 1403,	// 技能学习返回											已经作废*
		MT_ROLE_SKILL_UPGRADE_SC			= 1404,	// 技能升级返回											已经作废*
		MT_ROLE_EXP_CHANGE_SC				= 1405,	// 经验变更通知
		MT_ROLE_LEVEL_UPGRADE_SC			= 1406,	// 经验升级广播
		MT_ROLE_HP_MP_PACK_SC				= 1407,	// 红蓝包变化
		MT_ROLE_ARMY_INFO_SC				= 1408,	// 帮派信息
		MT_ROLE_EFFECT_LIST_SC				= 1409,	// buff列表
		MT_ROLE_EXP_DAN_INFO_SC				= 1410,	// 经验丹
		MT_ROLE_INFO_OTHER_SC				= 1415,	// 查看个人信息返回

		MT_ROLE_BASE_INFO_CS				= 1450,	// 请求角色基本信息
		MT_ROLE_SKILL_INFO_CS				= 1451,	// 请求角色技能信息
		MT_ROLE_SKILL_UPGRADE_ENTIRE_CS		= 1452,	// 一键升级技能
		MT_ROLE_SKILL_LEARN_REQ_CS			= 1453,	// 请求技能学习
		MT_ROLE_SKILL_UPGRADE_REQ_CS		= 1454,	// 请求技能升级
		MT_ROLE_SET_ATTACK_MODE_CS			= 1455,	// 设置攻击模式
		MT_ROLE_ALL_INFO_REQ_CS				= 1458,	// 用于登陆时请求一系列消息(原各模块的单独请求消息保留)
		// 物品操作相关
		MT_KNAPSACK_INFO_ACK_SC				= 1500,	// 请求背包信息返回
		MT_KNAPSACK_GRID_CHANGE_SC			= 1501,	// 背包单个格子变化
		MT_KNAPSACK_PARAM_SC				= 1502,	// 背包参数列表
		MT_KNAPSACK_GRID_CHANGE_PARAM_SC	= 1503,	// 有参数的格子变化
		MT_STROAGE_COIN_CHANGE_SC			= 1504,	// 仓库铜钱发生改变
		MT_USE_ITEM_SUC_SC					= 1505,	// 使用物品成功
		MT_KNAPSACK_MAX_GRID_NUM_SC			= 1506,	// 背包格子数量上限
		MT_FUNCTION_NEW_ITEM_NOTICE_SC		= 1507,	// 新物品通知
		MT_TEAM_MEMBER_PICK_ITEM_SC			= 1508,	// 队伍成员拾取掉落物品
		MT_TEAM_MEMBER_PICK_COIN_SC			= 1509,	// 队伍成员拾取掉落铜币
		MT_KNAPSACK_ACQUIRE_SC				= 1510,	// 获取物品消息
		MT_KNAPSACK_INFO_REQ_CS				= 1550,	// 请求背包信息
		MT_USE_ITEM_CS						= 1551,	// 使用物品
		MT_MOVE_ITEM_CS						= 1552,	// 移动背包单元
		MT_DICARD_ITEM_CS					= 1553,	// 丢弃物品
		MT_KNAPSACK_ARRANGE_CS				= 1554,	// 整理背包
		MT_ITEM_PICK_CS						= 1555,	// 捡起掉落物品
		MT_SPLIT_ITEM_CS					= 1556,	// 拆分背包物品
		MT_NPC_STROAGE_MOVE_CS				= 1557,	// 通过npc移动仓库物品
		MT_NPC_STROAGE_COIN_MOVE_CS			= 1558,	// 通过npc移动仓库铜钱
		MT_ARMY_PUT_STORE_ITEM_CS			= 1559,	// 请求把背包的物品放入仓库
		MT_EXTEND_KNAPSACK_NUM_CS			= 1560,	// 扩展背包或仓库
		MT_TWISTEGG_STORAGE_CS				= 1570,	// 请求扭蛋仓库
		MT_MOVE_GASHAPON_ALL_TO_KNAPSACK_CS	= 1571,	// 移动寻宝所有物品
		MT_ITEM_LINK_INFO_CS				= 1572,	// 请求物品超链接
		MT_TWIST_OTHER_INFOGET_CS			= 1573,// 请求其他玩家的扭蛋炫耀信息， 只在玩家第一次打开的时候获取
		MT_MERGER_ITEM_CS					= 1574,// 合并某个位置的物品
		MT_SELL_ITEM_CS						= 1575,// 出售物品
		MT_WALLOW_PERCENT_CHANGE_CS			= 1576,// 防沉迷信息改变，要求服务器向数据库查询
		MT_MERGER_ALL_ITEM_CS				= 1577,// 合并背包所有物品
		MT_ITEM_COMPOSITE_ITEM_CS			= 1578,// 合成物品（2013.12.28）
		MT_ITEM_BATCH_COMPOSITE_ITEM_CS		= 1579,// 批量合成物品（2013.12.28）
		MT_ITEM_COMPOSITE_ALL_JEWEL_CS		= 1580,// 一键合成所有的宝石
		MT_ITEM_TRANSFORM_CS				= 1581,// 物品转换
		// 装备相关
		MT_EQUIPMENT_INFO_ACK_SC			= 1700,	// 获取装备信息返回
		MT_EQUIPMENT_ITEM_CHANGE_SC			= 1701,	// 装备信息改变
		MT_EQUIPMENT_BATCH_PURIFY_SC		= 1720,	// 批量洗炼属性返回
		MT_EQUIPMENT_STRENGTHEN_WISHES_SC	= 1721,	// 返回强化祝福值
		
		MT_EQUIPMENT_INFO_REQ_CS			= 1750,	// 请求装备信息
		MT_EQUIPMENT_TAKE_OFF_CS			= 1751,	// 除下装备
		MT_EQUIPMENT_TAKE_OFF_FASHION_CS	= 1752,	// 脱下时装
		MT_EQUIPMENT_STRENGTHEN_CS			= 1786,	// 装备强化
		MT_EQUIPMENT_MOUNT_JEWEL_CS			= 1787,	// 镶嵌宝石
		MT_EQUIPMENT_UNMOUNT_JEWEL_CS		= 1788,	// 摘除宝石
		MT_EQUIPMENT_UPGRADE_CS				= 1789,	// 装备升级
		MT_EQUIPMENT_PROMOTE_QUALITY_CS		= 1790,	// 装备升阶
		MT_EQUIPMENT_RECAST_CS				= 1791,	// 装备重铸
		MT_EQUIPMENT_WASH_CS				= 1792,	// 装备洗炼
		MT_EQUIPMENT_BATCH_WASH_CS			= 1793,	// 装备批量洗炼
		MT_EQUIPMENT_SAVE_WASH_CS			= 1794,	// 保存批量洗炼结果
		MT_EQUIPMENT_MARK_CS				= 1795,	// 装备铭刻
		// NPC 任务
		MT_TASK_LIST_RSP_SC					= 1800,	// 发送任务列表返回
		MT_TASK_RECORDER_LIST_SC			= 1801,	// 发送任务记录列表
		MT_TASK_ACCEPT_SC					= 1802,	// 接受任务返回
		MT_TASK_COMMIT_SC					= 1803,	// 提交任务返回
		MT_TASK_GIVEUP_SC					= 1804,	// 放弃任务返回
		MT_TASK_CHANGE_SC					= 1805,	// 任务改变返回
		MT_TASK_RECORDER_CHANGE_SC			= 1806,	// 单条任务记录信息
		MT_TASK_LOOP_SC						= 1807,	// 循环任务
		MT_TASK_BOARD_SC					= 1808,	// 悬赏任务
		MT_TASK_COIN_SC						= 1809,	// 银两任务
		MT_TASK_ARMY_SC						= 1810,	// 帮派任务
		MT_TASK_XLIAN_SC					= 1811,	// 修炼卷任务
		MT_TASK_BOARD_LIST_SC				= 1812,	// 悬赏任务列表
		MT_TASK_BOARD_ITEM_CHANGE_SC		= 1813,	// 悬赏列表改变
		MT_TASK_DAY_COUNT_CHANGE_SC			= 1814,	// 日常任务每日次数变化
		MT_TASK_XLIAN_FINISH_REWARD_SC		= 1815,	// 修炼卷全部完成奖励
		MT_TASK_LIST_REQ_CS					= 1850,	// 请求任务列表
		MT_TASK_RECORDER_LIST_CS			= 1851,	// 请求任务记录列表
		MT_TASK_ACCEPT_CS					= 1852,	// 请求接收任务
		MT_TASK_COMMIT_CS					= 1853,	// 请求提交任务
		MT_TASK_GIVEUP_CS					= 1854,	// 请求放弃任务
		MT_TASK_TALK_CS						= 1855,	// 跟NPC对话
		MT_TASK_BOARD_LIST_CS				= 1856,	// 请求悬赏信息
		MT_TASK_BOARD_FRESH_CS				= 1857,	// 刷新悬赏任务
		MT_TASK_BOARD_FINISH_CS				= 1858,	// 立即完成悬赏任务
		MT_TASK_XLIAN_INFO_CS				= 1859,	// 请求修炼卷信息
		MT_TASK_XLIAN_FRESH_CS				= 1860,	// 刷新修炼卷任务
		MT_TASK_XLIAN_TOP_QUALITY_CS		= 1861,	// 一键满星修炼卷任务
		MT_TASK_XLIAN_FINISH_ALL_CS			= 1862,	// 一键完成全部修炼卷
		MT_TASK_XLIAN_FINISH_CS				= 1863,	// 立即完成修炼卷任务
		MT_TASK_XLIAN_FINISH_ALL_REWARD_CS	= 1864,	// 领取完成奖励
		// 金钱相关
		MT_MONEY_SC							= 2000,	// 钱
		// 宠物相关
		MT_PET_LIST_ACK_SC					= 2200,	// 请求宠物列表回复
		MT_PET_CALL_INDEX_CHANGE_SC			= 2201,	// 出战宠物变化
		MT_PET_ATTR_CHANGE_SC				= 2202,	// 宠物属性变化
		MT_PET_INFO_SC						= 2203,	// 单个宠物的完整信息
		MT_PET_LEVEL_UPGRADE_SC				= 2204,	// 宠物经验升级广播
		MT_PET_PERCEPTION_UPGRADE_SC		= 2205,	// 宠物悟性提升广播
		MT_PET_RENAME_SC					= 2213,	// 宠物改名--Leon Add 12-02-29
		MT_PET_DISCARD_SC					= 2214,	// 宠物放生--Leon Add 12-02-29
		MT_PET_SHOW_OFF_SC					= 2229,	// 炫耀
		MT_PET_SHOW_OFF_INFO_SC				= 2230,	// 炫耀信息
		MT_PET_LEARN_SKILL_SC				= 2232,	// 学习技能结果
		MT_PET_FORGET_SKILL_SC				= 2233,	// 遗忘技能结果
		MT_PET_MARK_SKILL_SC				= 2234,	// 刻印技能结果
		MT_PET_RAND_SKILL_SC				= 2235,	// 随机刷新技能结果
		MT_PET_SKILL_LIST_ACK_SC			= 2236,	// 宠物技能列表
		MT_PET_PROMOTE_GROWTH_SC			= 2237,	// 提升成长
		MT_PET_PROMOTE_PERCEPTION_SC		= 2238,	// 提升悟性
		MT_PET_INHERIT_SC					= 2239,	// 融合
		MT_PET_CLASS_INFO_SC				= 2240,	// 宠物图鉴信息

		//MT_PET_LIST_REQ_CS				= 2250,	// 请求宠物列表(废弃)
		MT_PET_CALLOUT_REQ_CS				= 2251,	// 请求召唤宠物
		MT_PET_CALLBACK_REQ_CS				= 2252,	// 请求收回宠物
		MT_PET_DISCARD_REQ_CS				= 2253,	// 宠物放生
		MT_PET_RENAME_REQ_CS				= 2255,	// 请求宠物改名		
		MT_PET_PROMOTE_GROWTH_CS			= 2256,	// 提升宠物成长
		MT_PET_PROMOTE_PERCEPTION_CS		= 2257,	// 提升宠物悟性
		MT_PET_LEARN_SKILL_CS				= 2260,	// 学习技能
		MT_PET_FORGET_SKILL_CS				= 2261,	// 遗忘技能
		MT_PET_MARK_SKILL_CS				= 2262,	// 刻印技能
		MT_PET_RAND_SKILL_CS				= 2263,	// 随机技能
		MT_PET_INHERIT_CS					= 2264,	// 宠物融合
		MT_PET_MERGE_CS						= 2267,	// 宠物合体
		MT_PET_MERGE_CANCEL_CS				= 2268,	// 取消合体
		MT_PET_SHOW_OFF_CS					= 2269,	// 炫耀
		MT_PET_SHOW_OFF_INFO_CS				= 2270,	// 炫耀信息
		MT_PET_CHANGE_AI_MODE_CS			= 2271,	// 改变攻击模式
		// 其他
		MT_SIGNIN_INFO_SC					= 2700,	// 签到面板信息返回
		MT_SIGNIN_REWARDS_SC				= 2701,	// 签到奖励信息
		MT_NEILI_INFO_SC					= 2702,	// 内力信息返回
		MT_NEILI_CHANGE_SC					= 2703,	// 内力值发生改变
		MT_PUT_ON_TITLE_INFO_SC				= 2704,	// 已装备称号信息
		MT_OWN_TITLE_INFO_SC				= 2705,	// 所有拥有的称号信息
		MT_OWN_TITLE_STATUS_SC				= 2706,	// 单个称号状态发生改变（增加or删除）
		MT_ONLINE_REWARD_INFO_SC			= 2707,	// 在线奖励信息返回
		MT_MONEY_TREE_SC					= 2708,	// 招财树信息返回
		MT_CONSUME_GIFT_BAG_INFO_SC			= 2709, // 消费礼包信息返回
		MT_CONSUME_GIFT_BAG_CHANGE_SC		= 2710, // 消息礼包状态改变
		MT_MYSTERY_SHOP_INFO_SC				= 2711, // 神秘商店信息返回
		MT_MYSTERY_SHOP_BUY_ITEM_SC			= 2712,	// 神秘商店购买物品返回
		MT_AIM_INFO_SC						= 2713,	// 目标信息返回
		MT_AIM_STATE_CHANGE_SC				= 2714, // 目标状态改变
		MT_HUNT_INFO_SC						= 2715, // 寻宝个人概况返回
		MT_ADD_HUNT_INFO_SC					= 2716, // 寻宝增加个人概况
		MT_VIP_LEVEL_REWARD_STATE_SC		= 2717,	// VIP等级奖励状态
		MT_YELLOW_VIP_PANEL_INFO_SC			= 2718,	// 黄钻面板信息
		MT_OSP_INFO_SC						= 2719, // 开服炫购信息
		MT_FIRST_RECHARGE_INFO_SC			= 2720,	// 首充信息返回
		MT_SEVEN_DAY_GIFT_INFO_SC			= 2721,	// 7天奖励信息返回
		MT_HUNT_RARE_TIME_SC				= 2722, // 再寻宝N次获得珍贵物品
		MT_OSC_INFO_SC						= 2723, // 开服巨献信息返回
		MT_OPR_RESULT_SC					= 2724, // 操作结果返回(1722->2724)
		MT_ICON_OPEN_SC						= 2725,	// 上方图标开启通知
		MT_TITLE_PUT_ON_CHANGE				= 2726,	// 头顶称号改变
		MT_YELLOW_VIP_INFO_CHANGE_SC		= 2727,	// 广播黄钻信息改变
		MT_VIP_TODAY_RECHARGE_STATE_SC		= 2728, // 今日充值礼包状态
		MT_VIP_SEVEN_DAY_REBATE_STATE_SC	= 2729, // 七天返利状态
		MT_OTHER_ACTIVITY_ICON_STATE_SC		= 2730,	// 限时活动图标状态
		MT_LOGIN_ACTIVITY_GIFTBAG_STATE_SC	= 2731,	// 登录活动礼包状态
		MT_WEDDING_FERE_INFO_SC				= 2732, // 结婚伴侣信息
		MT_WEDDING_RING_INFO_SC				= 2733, // 戒指信息
		MT_WEDDING_FERE_INFO_BROADCAST_SC	= 2734, // 伴侣信息广播
		MT_ASSIGN_MONSTER_ACTIVITY_SC		= 2735,	// 指定怪物双倍活动

		MT_LIANQI_UPGRADE_CS				= 2750, // 炼气升级
		MT_SIGNIN_REQ_CS					= 2751,	// 签到请求
		MT_SIGNIN_PATCH_CS					= 2752,	// 补签请求
		MT_SIGNIN_GET_REWARDS_CS			= 2753,	// 领取签到奖励礼包
		MT_NEILI_BREAK_CS					= 2754,	// 内力突破
		MT_NEILI_UPGRADE_CS					= 2755,	// 内力升级
		MT_PUT_ON_TITLE_CS					= 2756,	// 装备称号
		MT_TAKE_OFF_TITLE_CS				= 2757,	// 隐藏称号
		MT_ONLINE_REWARD_INFO_CS			= 2758,	// 请求在线奖励信息
		MT_GET_ONLINE_REWARD_CS				= 2759,	// 领取在线奖励
		MT_MONEY_TREE_GET_COIN_CS			= 2760,	// 使用招财树招财
		MT_TREASURE_HUNT_CS					= 2761,	// 请求寻宝
		MT_EXCHANGE_ITEM_CS					= 2762,	// 兑换物品
		MT_RECHARGE_10_GIFT_CS				= 2763,	// 领取首冲10元
		MT_MONEY_TREE_GET_INFO_CS			= 2764,	// 获得招财树信息
		MT_CONSUME_GIFT_BAG_INFO_CS			= 2765, // 消费礼包
		MT_GET_CONSUME_GIFT_BAG_CS			= 2766, // 领取消费礼包
		MT_MYSTERY_SHOP_INFO_CS				= 2767, // 请求神秘商店信息
		MT_MYSTERY_SHOP_REFRESH_CS			= 2768, // 请求刷新神秘商店
		MT_MYSTERY_SHOP_BUY_ITEM_CS			= 2769, // 神秘商店购买物品
		MT_AIM_GET_INFO_CS					= 2770,	// 获得目标信息
		MT_AIM_GET_REWARD_CS				= 2771,	// 领取目标奖励
		MT_GET_HUNT_INFO_CS					= 2772, // 获得个人寻宝概况
		MT_TRADE_LOCK_ITEM_CS				= 2773, // 锁定物品
		MT_SIGNIN_GET_REWARD_PET_CS			= 2774,	// 领取签到奖励宠物
		MT_VIP_GET_LEVEL_REWARD_CS			= 2775,	// 领取Vip等级奖励
		MT_YELLOW_VIP_GET_XINSHOU_GIFT_CS	= 2776,	// 领取黄钻新手礼包
		MT_YELLOW_VIP_GET_DAILY_GIFT_CS		= 2777,	// 领取黄钻每日礼包
		MT_YELLOW_VIP_GET_GROWTH_GIFT_CS	= 2778,	// 领取黄钻成长礼包
		MT_YELLOW_VIP_GET_PET_GIFT_CS		= 2779,	// 领取黄钻宠物礼包
		MT_YELLOW_VIP_INFO_CS				= 2780,	// 黄钻信息
		MT_CAMP_POINTS_EXCHANGE_ITEM_CS		= 2781,	// 阵营战积分兑换物品(废弃 2014.06.11)
		MT_SEVEN_DAY_GIFT_INFO_CS			= 2782,	// 7天豪礼信息
		MT_SEVEN_DAY_GIFT_GET_GIFT_CS		= 2783, // 领取7天豪礼
		MT_OSP_BUY_MOUNT_CS					= 2784, // 开服炫购购买坐骑
		MT_OSP_BUY_WING_CS					= 2785,	// 开服炫购购买翅膀
		MT_FIRST_RECHARGE_INFO_CS			= 2786,	// 首充信息
		MT_FIRST_RECHARGE_GET_GIFT_CS		= 2787,	// 领取首充奖励
		MT_OSP_INFO_CS						= 2788,	// 开服炫购信息
		MT_BUY_POWER_CS						= 2789, // 购买体力
		MT_USE_LOUDSPEAKER_CS				= 2790,	// 使用小喇叭
		MT_OSC_INFO_CS						= 2791, // 开服巨献信息
		MT_OSC_GET_REWARD_CS				= 2792,	// 领取开服巨献奖励
		MT_VIP_GET_TODAY_RECHARGE_GIFT_CS	= 2793, // 领取今日充值奖励
		MT_VIP_GET_REBATE_CS				= 2794,	// 领取返利
		MT_LOGIN_ACTIVITY_GET_GIFTBAG_CS	= 2795,	// 领取登录活动礼包
		MT_WEDDING_RING_UPGRADE_CS			= 2796, // 戒指升级	
		MT_USE_RAND_PAPER_CS				= 2797,	// 使用随机卷

		// 商场
		MT_SHOP_GLOD_BUY_CS					= 2850,	// 商城购买
		// 商店
		MT_STORE_BUY_ITEM_CS				= 2851,	// 商店购买
		MT_STORE_SELL_ITEM_CS				= 2852, // 商店出售

		// 其它2
		MT_LUCKY_COMPASS_RESULT_SC			= 2900,	// 转盘结果

		MT_LUCKY_COMPASS_ROTATE_CS			= 2950,	// 转动转盘

		// 坐骑系统
		MT_MOUNT_INFO_SC					= 5200,	// 坐骑回应协议
		MT_MOUNT_AVATAR_LIST_SC				= 5201,	// 特殊外形列表
		MT_MOUNT_OVER_SC					= 5202,	// 上坐骑返回
		MT_MOUNT_OFF_SC						= 5203,	// 下坐骑返回
		MT_MOUNT_COLLECTION_SC				= 5204,	// 坐骑收集结果返回
		MT_MOUNT_ADD_MOUNT_SC				= 5205,	// 获得新的幻化坐骑

		MT_MOUNT_INFO_REQ_CS				= 5250,	// 坐骑请求协议
		MT_MOUNT_UPGRADE_EXP_CS				= 5251,	// 升级经验
		MT_MOUNT_UPGRADE_HUASHEN_CS			= 5252,	// 提升化神
		MT_MOUNT_UPGRADE_TRAIN_CS			= 5253,	// 提升培养
		MT_MOUNT_CTEATE_REQ_CS				= 5254,	// 测试创建坐骑
		MT_MOUNT_CHANGE_AVATAR_CS			= 5255,	// 化形
		MT_MOUNT_OVER_CS					= 5256,	// 上坐骑
		MT_MOUNT_OFF_CS						= 5257,	// 下坐骑
		MT_MOUNT_UPGRADE_EXP_TEN_CS			= 5258, // 升级10次经验
		// 翅膀系统
		MT_WING_INFO_SC						= 5300,	// 服务器
		MT_WING_SKILL_LIST_SC				= 5301,	// 技能列表
		MT_WING_INFO_REQ_CS					= 5350,	// 客户端
		MT_WING_UPGRADE_REQ_CS				= 5351,	// 升级
		MT_WING_STAR_UP_REQ_CS				= 5352,	// 升阶
		MT_WING_UPGRADE_SKILL_REQ_CS		= 5353,	// 升技能
		MT_WING_CHANGE_AVATAR_REQ_CS		= 5354,	// 化形
		MT_WING_CREATE_REQ_CS				= 5355,	// 创建翅膀
		MT_WING_MOUNT_ON_OFF_CS				= 5356,	// 上下翅膀
		// 邮件
		MT_MAIL_SEND_CS						= 5371,	// 发送邮件
		// 帮派
		MT_ARMY_CREATE_REQ_CS				= 5400, // 创建帮派
		MT_ARMY_IMPEACH_LEADER_CS			= 5401,	// 弹劾帮主
		MT_ARMY_DONATE_CS					= 5402,	// 帮派捐献
		MT_ARMY_SHENTAN_SHANGXIANG_CS		= 5403, // 帮派神坛上香
		MT_ARMY_STORAGE_DEPOSIT_CS			= 5404,	// 帮派仓库存入物品
		MT_ARMY_STORAGE_GET_ITEM_CS			= 5405,	// 获取帮派仓库物品
		MT_ARMY_ENTER_BOSS_SCENE_CS			= 5406, // 进入帮派场景
		// 法宝
		MT_FABAO_INFO_REQ_CS				= 5500,	// 法宝信息请求
		MT_FABAO_SOUL_GRID_INFO_CS			= 5501,	// 法宝炼魂信息
		MT_FABAO_ADDEXP_CS					= 5502,	// 法宝升级
		MT_FABAO_CALL_SOUL_CS				= 5503, // 法宝召唤
		MT_FABAO_HUNT_SOUL_CS				= 5504, // 法宝猎魂
		MT_FABAO_ONE_KEY_HUNT_SOUL_CS		= 5505, // 一键猎魂
		MT_FABAO_SOUL_MOVE_CS				= 5506, // 移动战魂
		MT_FABAO_ONE_KEY_DEVOUR_HOUL_CS		= 5507, // 一键吞噬战魂
		MT_FABAO_UNLOCK_SOUL_GRID_CS		= 5508, // 解封炼魂格子
		MT_FABAO_SOUL_EXCHANGE_CS			= 5509, // 战魂兑换
		MT_FABAO_INFO_SC					= 5550, // 法宝基础信息
		MT_FABAO_SOUL_GRID_INFO_SC			= 5551,	// 法宝炼魂信息
		MT_FABAO_EXP_CHANGE_SC				= 5552,	// 法宝经验改变
		MT_FABAO_HUNT_SOUL_STATE_SC			= 5553,	// 法宝猎魂状态
		MT_FABAO_SOUL_GRID_CHANGE_SC		= 5554,	// 法宝炼魂格子物品改变
		MT_FABAO_SOUL_GRID_ADD_SC			= 5555, // 法宝炼魂可用格子增加
		MT_FABAO_CAPABILITY_SC				= 5556, // 战力返回
		MT_FABAO_SOUL_FRAGMENT_NUM_SC		= 5557, // 战魂碎片个数返回

		// 活动
		MT_FRUIT_BATTLE_CS					= 5600, // 进入水果大战
		MT_FRUIT_BATTLE_USE_FRUIT_CS		= 5601,	// 使用水果
		MT_FRUIT_BATTLE_USE_AOE_FRUIT_CS	= 5602, // 使用AOE水果
		MT_FRUIT_BATTLE_REWARD_CS			= 5603,	// 领取水果大战奖励
		MT_CAMP_BATTLE_ENTER_CS				= 5604, // 进入阵营战
		MT_CAMP_BATTLE_REWARD_CS			= 5605,	// 领取阵营战奖励
		MT_MIDAUTUMN_GET_LOGIN_GIFT_CS		= 5606, // 领取中秋登录奖励
		MT_MIDAUTUMN_BUY_LUXURY_GIFT_CS		= 5607,	// 购买中秋豪华礼包
		MT_MIDAUTUMN_PANEL_INFO_CS			= 5608,	// 中秋活动面板信息
		MT_BAGUA_ENTER_CS					= 5609,	// 进入八卦阵
		MT_BAGUA_GET_REWARD_CS				= 5610, // 领取八卦任务奖励
		MT_NATIONALDAY_PAEEL_INFO_CS		= 5611, // 国庆活动面板信息
		MT_NATIONALDAY_BUY_LUXURY_GIFT_CS	= 5612,	// 国庆活动购买豪华礼包
		MT_NATIONALDAY_GET_LOGIN_GIFT_CS	= 5613, // 国庆活动领取礼包
		MT_WORLD_FIRST_ENTER_CS				= 5614, // 进入天下第一
		MT_WORLD_FIRST_REWARD_CS			= 5615, // 领取天下第一奖励
		MT_BUY_ACTIVITY_GIFT_BAG_CS			= 5616, // 购买活动礼包	
		MT_ARMY_BATTLE_ENTER_CS				= 5617,	// 进入帮派战
		MT_ARMY_BATTLE_REWARD_CS			= 5618, // 领取帮派战奖励

		MT_FRUIT_BATTLE_INFO_SC				= 5650,	// 水果大战面板信息
		MT_FRUIT_BATTLE_FRUIT_INFO_SC		= 5651,	// 水果大战技能信息
		MT_FRUIT_BATTLE_ALL_FRUIT_INFO_SC	= 5652, // 水果大战所有技能信息
		MT_FRUIT_BATTLE_SKILL_SC			= 5653,	// 广播技能
		MT_FRUIT_BATTLE_ROLE_HP_SC			= 5654, // 人物血量
		MT_FRUIT_BATTLE_RANK_LIST_SC		= 5655,	// 使用水果成功
		MT_FRUIT_BATTLE_REWARD_SC			= 5656,	// 水果大战奖励
		MT_FRUIT_BATTLE_REWARD_RESULT_SC	= 5657,	// 活动奖励结果
		MT_CAMP_BATTLE_PANEL_INFO_SC		= 5658,	// 阵营战面板信息
		MT_CAMP_BATTLE_PERSONAL_INFO_SC		= 5659, // 阵营战个人信息
		MT_CAMP_BATTLE_REWARD_SC			= 5660,	// 阵营战奖励
		MT_CAMP_BATTLE_CAMP_INFO_SC			= 5661, // 阵营信息
		MT_CAMP_BATTLE_CAMP_POINT_SC		= 5662, // 阵营积分
		MT_MIDAUTUMN_LOGIN_GIFT_INFO_SC		= 5663, // 中秋活动登录礼包信息
		MT_MIDAUTUMN_LUXURY_GIFT_INFO_SC	= 5664, // 中秋活动豪华礼包信息
		MT_MIDAUTUMN_LUXURY_GIFT_CHANGE_SC	= 5665,	// 中秋活动豪华礼包信息改变
		MT_BAGUA_TASK_SC					= 5666,	// 八卦阵任务
		MT_BAGUA_ALL_TASK_SC				= 5667,	// 八卦阵所有任务
		MT_BAGUA_GET_REWARD_ERR_SC			= 5668, // 领取八卦任务奖励错误返回
		MT_NATIONALDAY_LOGIN_GIFT_INFO_SC	= 5669, // 国庆登录礼包信息
		MT_NATIONALDAY_LUXURY_GIFT_INFO_SC	= 5670, // 国庆豪华礼包信息
		MT_NATIONALDAY_LUXURYGIFT_CHANGE_SC	= 5671,	// 国庆豪华礼包信息改变
		MT_WORLD_FIRST_PANEL_INFO_SC		= 5672, // 天下第一面板信息
		MT_WORLD_FIRST_PERSONAL_INFO_SC		= 5673,	// 天下第一个人信息
		MT_WORLD_FIRST_REWARD_SC			= 5674,	// 天下第一奖励
		MT_ARMY_BATTLE_PERSONAL_INFO_SC		= 5675,	// 帮派战个人信息
		MT_ARMY_BATTLE_PANEL_INFO_SC		= 5676,	// 帮派战面板信息
		MT_ARMY_BATTLE_FIRST_ARMY_INFO_SC	= 5677,	// 排名第一帮派信息
		MT_ARMY_BATTLE_ARMY_INFO_SC			= 5678, // 本帮派信息
		MT_ARMY_BATTLE_REWARD_SC			= 5679,	// 帮派战奖励


		/************************************************************************/
		// login server
		MT_LOGIN_ACK_SC						= 7000,	// 登陆请求回复
		MT_LOGIN_ERR_SC						= 7001,	// 登录错误回复
		MT_LOGIN_REQ_CS						= 7050,	// 登陆请求
		MT_LOGIN_CREATE_ROLE_CS				= 7150,	// 创建角色
		/************************************************************************/
		// chat server
		MT_USER_LOGIN_ACK_SC				= 8000,	// 登录聊天服返回
		MT_USER_BE_DESTROY_SC				= 8001,	// 用户被销毁
		MT_INTO_CHANNEL_SC					= 8002,	// 用户进入频道
		MT_OUT_OF_CHANNEL_SC				= 8003,	// 用户移出频道
		MT_NOTICE_ONLINE_SC					= 8004,	// 上线通知
		MT_NOTICE_OFFLINE_SC				= 8005,	// 下线通知
		MT_USER_LOGIN_CS					= 8050,	// 登录聊天服
		MT_MUTE_USER_CS						= 8051,	// 禁言
		MT_UNMUTE_USER_CS					= 8052,	// 取消禁言
		MT_CHANNEL_CHAT_SC					= 8100,	// 频道聊天
		MT_SINGLE_CHAT_SC					= 8101,	// 私聊
		MT_SINGLE_CHAT_USET_NOT_EXIST_SC	= 8102,	// 用户不存在
		MT_CHANNEL_CHAT_CS					= 8150,	// 频道聊天
		MT_SINGLE_CHAT_CS					= 8151,	// 私聊
		/************************************************************************/
		// global server
		MT_ENTER_GLOBAL_SERVER_ACK_SC		= 9000,	// 登陆全局服务器回复
		MT_TIME_ACK_SC						= 9001,	// 服务器时间
		MT_WALLOW_NOTICE_SC					= 9002,	// 防沉迷返回
		MT_USER_KICKOUT_SC					= 9003,	// 玩家被顶号
		MT_PUBLIC_NOTICE_SC					= 9004,	// 全服公告
		MT_ENTER_GLOBAL_SERVER_REQ_CS		= 9050,	// 请求登陆全局服务器
		MT_TIME_REQ_CS						= 9051,	// 请求服务器时间
		// 组队
		MT_TEAM_INFO_SC						= 9100,	// 队伍信息
		MT_TEAM_TEAM_LIST_SC				= 9101,	// 附近队伍信息
		MT_TEAM_USER_LIST_SC				= 9102,	// 附近玩家信息
		MT_TEAM_CREATE_SC					= 9103,	// 创建结果
		MT_TEAM_JOIN_SC						= 9104,	// 转发给队长请求加入
		MT_TEAM_RSP_JOIN_SC					= 9105,	// 申请加入结果
		MT_TEAM_QUIT_SC						= 9106,	// 退出队伍结果
		MT_TEAM_INVITE_SC					= 9107,	// 邀请别人
		MT_TEAM_RSP_INVITE_SC				= 9108,	// 邀请结果返回
		MT_TEAM_KICK_SC						= 9109,	// 发送给被踢玩家
		MT_TEAM_TEAM_STATE_SC				= 9110, // 队伍状态返回
		MT_TEAM_ENTER_TEAM_FB_ERROR_SC		= 9111,	// 进入组队副本错误信息
		MT_TEAM_INFO_CS						= 9150,	// 请求队伍信息
		MT_TEAM_USER_LIST_CS				= 9152,	// 请求附近玩家
		MT_TEAM_CREATE_CS					= 9153,	// 请求创建队伍
		MT_TEAM_JOIN_CS						= 9154,	// 请求加入队伍
		MT_TEAM_RSP_JOIN_CS					= 9155,	// 回复玩家加入队伍请求
		MT_TEAM_QUIT_CS						= 9156,	// 请求退出队伍
		MT_TEAM_RSP_INVITE_CS				= 9158,	// 回复组队邀请请求
		MT_TEAM_KICK_CS						= 9159,	// 请求剔除玩家
		MT_TEAM_APPOINT_LEADER_CS			= 9160,	// 委任队长
		MT_TEAM_SET_TEAM_STATE_CS			= 9161, // 设置组队状态（是否接受邀请入队等）
		MT_TEAM_ENTER_TEAM_FB_CS			= 9162,	// 进入组队副本
		// 帮派
		MT_ARMY_LIST_SC						= 9200,	// 帮派列表
		MT_ARMY_INFO_SC						= 9201,	// 帮派信息返回
		MT_ARMY_APPLY_LIST_SC				= 9202,	// 帮派申请列表返回
		MT_ARMY_INVITE_INFO_SC				= 9203,	// 邀请加入帮派信息返回
		MT_ARMY_POST_CHANGE_SC				= 9204,	// 职位变更返回
		MT_ARMY_MODIFY_YY_SC				= 9205,	// 修改yy返回(废弃2015.04.24)
		MT_ARMY_MODIFY_QQ_SC				= 9206,	// 修改qq返回(废弃2015.04.24)
		MT_ARMY_MODIFY_NOTICE_SC			= 9207,	// 修改公告返回
		MT_ARMY_ADD_MEMBER_SC				= 9208,	// 添加成员
		MT_ARMY_REMOVE_MEMBER_SC			= 9209,	// 删除成员
		MT_ARMY_AGREE_JOIN_ARMY_SC			= 9210,	// 同意加入帮派
		MT_ARMY_REFUSE_JOIN_ARMY_SC			= 9211,	// 拒绝加入帮派
		MT_ARMY_MONEY_CHANGE_SC				= 9212,	// 帮派资金改变
		MT_ARMY_PERSONAL_INFO_SC			= 9213,	// 家族个人信息
		MT_ARMY_APPLY_LIST_ADD_SC			= 9214,	// 申请列表增加成员
		MT_ARMY_APPLY_LIST_DELETE_SC		= 9215,	// 申请列表删除成员
		MT_ARMY_MEMBER_UPGRADE_SC			= 9216,	// 成员升级
		MT_ARMY_MEMBER_LOGIN_SC				= 9217,	// 成员上线
		MT_ARMY_MEMBER_LOGOUT_SC			= 9218,	// 成员下线
		MT_ARMY_MEMBER_CAPACITY_SC			= 9219,	// 成员战斗力改变
		MT_ARMY_LIST_ADD_SC					= 9220,	// 帮派列表增加
		MT_ARMY_LIST_DELETE_SC				= 9221,	// 帮派列表删除
		MT_ARMY_LIST_CHANGE_SC				= 9222,	// 帮派列表改变
		MT_ARMY_SHENTAN_INFO_SC				= 9223,	// 神坛信息返回
		MT_ARMY_SHENTAN_EVENT_LIST_SC		= 9224,	// 神坛事件列表返回
		MT_ARMY_SHENTAN_EVENT_ADD_SC		= 9225,	// 神坛事件增加
		MT_ARMY_BASE_INFO_CHANGE_SC			= 9226,	// 帮派基础信息返回
		MT_ARMY_EVENT_LIST_SC				= 9227,	// 帮派事件返回
		MT_ARMY_EVENT_ADD_SC				= 9228,	// 帮派事件增加
		MT_ARMY_PERSONAL_CONTRIBUTION_SC	= 9229,	// 个人贡献返回
		MT_ARMY_GET_WELFARE_STATE_SC		= 9230,	// 领取福利状态
		MT_ARMY_BUILD_INFO_SC				= 9231,	// 帮派建筑等级返回
		MT_ARMY_STORAGE_INFO_SC				= 9232,	// 帮派仓库信息返回
		MT_ARMY_STORAGE_ITEM_CHANGE_SC		= 9233,	// 帮派仓库物品改变
		MT_ARMY_STORAGE_GET_ITEM_TIME_SC	= 9234,	// 帮派获取物品次数
		MT_ARMY_SHENTAN_LEVEL_SC			= 9235,	// 神坛等级，用于客户端显示buff
		MT_ARMY_MEMBER_CONTRIB_CHANGE_SC	= 9236,	// 帮贡变化
		MT_ARMY_JOIN_TIME_COOL_DOWN_SC		= 9237,	// 加入帮派冷却时间，退出帮派第二天才能申请
		MT_ARMY_BOSS_STATE_SC				= 9238, // 帮派BOSS状态
		MT_ARMY_SHANGXIANG_COUNT_SC			= 9239,	// 上香次数

		MT_ARMY_LIST_CS						= 9250,	// 请求帮派列表
		MT_ARMY_INFO_REQ_CS					= 9251,	// 请求帮派信息
		MT_ARMY_APPLY_LIST_REQ_CS			= 9252,	// 请求查看申请列表
		MT_ARMY_REFUSE_APPLY_CS				= 9253,	// 拒绝申请加入帮派
		MT_ARMY_DELETE_REQ_CS				= 9254,	// 请求删除帮派
		MT_ARMY_APPLY_REQ_CS				= 9255,	// 请求加入帮派
		MT_ARMY_AGREE_APPLY_CS				= 9256,	// 同意申请加入帮派
		MT_ARMY_AGREE_ALL_CS				= 9257,	// 同意所有申请
		MT_ARMY_REFUSE_ALL_CS				= 9258,	// 拒绝所有申请
		MT_ARMY_QUIT_REQ_CS					= 9259,	// 请求退出帮派
		MT_ARMY_INVITE_CS					= 9260,	// 邀请加入帮派
		MT_ARMY_INVITE_REPLY_CS				= 9261,	// 邀请加入帮派回复
		MT_ARMY_APPOINT_POST_CS				= 9262,	// 任命职位
		MT_ARMY_DISMISS_POST_CS				= 9263,	// 罢免职位
		MT_ARMY_KICK_OUT_MEMBER_CS			= 9264,	// 踢出成员
		MT_ARMY_MODIFY_YY_CS				= 9265,	// 修改yy(废弃2015.04.24)
		MT_ARMY_MODIFY_QQ_CS				= 9266,	// 修改qq(废弃2015.04.24)
		MT_ARMY_MODIFY_NOTICE_CS			= 9267,	// 修改公告
		MT_ARMY_GET_WELFARE_CS				= 9268,	// 领取帮派福利
		MT_ARMY_MAIN_UPGRADE_CS				= 9269,	// 主殿升级
		MT_ARMY_SMITHY_UPGRADE_CS			= 9270,	// 铁匠铺升级
		MT_ARMY_KONGFU_UPGRADE_CS			= 9271,	// 练功房升级
		MT_ARMY_SHOP_UPGRADE_CS				= 9272,	// 商店升级
		MT_ARMY_ALTAR_UPGRADE_CS			= 9273,	// 祭坛升级
		MT_ARMY_SHENTAN_INFO_REQ_CS			= 9274,	// 请求神坛信息
		MT_ARMY_EVENT_LIST_REQ_CS			= 9275,	// 帮派事件
		MT_ARMY_BUILD_INFO_REQ_CS			= 9276,	// 建筑信息请求
		MT_ARMY_STORAGE_INFO_REQ_CS			= 9277,	// 请求帮派仓库信息
		MT_ARMY_STORAGE_ARRANGE_CS			= 9278,	// 帮派仓库整理
		MT_ARMY_CALL_BOSS_CS				= 9279,	// 帮派召唤BOSS
		MT_ARMY_BUY_SHOP_ITEM_CS			= 9280,	// 帮派购买物品

		// 排行榜
		MT_RANK_LIST_ROLE_CAPACITY_SC		= 9300,	// 人物战力排行数据
		MT_RANK_LIST_ROLE_LEVEL_SC			= 9301,	// 人物等级排行数据
		MT_RANK_LIST_FABAO_CAPACITY_SC		= 9302,	// 法宝战力排行数据
		MT_RANK_LIST_WING_CAPACITY_SC		= 9303,	// 翅膀战力排行数据
		MT_RANK_LIST_PET_CAPACITY_SC		= 9304,	// 宠物战力排行数据
		MT_RANK_LIST_MOUNT_CAPACITY_SC		= 9305,	// 坐骑战力排行数据
		MT_RANK_OWN_RANK_SC					= 9306, // 个人排名信息
		MT_RANK_LIST_ROLE_CHARM_SC			= 9307, // 人物魅力排行数据
		MT_RANK_DETAIL_PERSON_SC			= 9308,	// 人物详细信息
		MT_RANK_DETAIL_FABAO_SC				= 9309, // 法宝详细信息
		//MT_RANK_DETAIL_PET_SC				= 9310, // 宠物详细信息

		MT_RANK_LIST_REQ_CS					= 9350,	// 请求排行榜数据
		MT_RANK_OWN_RANK_CS					= 9351,	// 查看个人排名
		MT_RANK_DETAIL_INFO_CS				= 9352, // 请求详细信息

		// 竞技场
		MT_ARENA_ROLE_INFO_SC				= 9400,	// 竞技场个人信息
		MT_ARENA_HERO_RANK_SC				= 9401,	// 竞技场英雄榜
		MT_ARENA_KEEP_WIN_RANK_SC			= 9402,	// 竞技场连胜榜
		MT_ARENA_OPPONENT_LIST_SC			= 9403,	// 对手列表
		MT_ARENA_FIGHT_MSG_SC				= 9404,	// 对战信息
		MT_ARENA_REWARD_RANK_SC				= 9405,	// 奖励榜

		MT_ARENA_INFO_REQ_CS				= 9450,	// 请求竞技场信息
		MT_ARENA_BROCAST_CS					= 9451, // 竞技场广播
		MT_ARENA_GET_REWARD_CS				= 9452,	// 领取离线竞技场奖励
		MT_ARENA_ON_FIGHT_CS				= 9453,	// 请求对战
		MT_ARENA_CLEAR_CHALLENGE_TIME_CS	= 9454,	// 消除挑战时间
		MT_ARENA_ADD_CHALLENGE_COUNT_CS		= 9455,	// 增加挑战次数

		// 邮件
		MT_MAIL_LIST_SC						= 9800,	// 邮件列表
		MT_MAIL_DETAIL_SC					= 9801,	// 邮件内容
		MT_MAIL_DELETE_SC					= 9803,	// 删除结果
		MT_MAIL_GET_EXTRA_SC				= 9804,	// 提取结果
		MT_MAIL_GET_EXTRA_ALL_SC			= 9805,	// 提取全部结果
		MT_MAIL_NEW_MAIL_SC					= 9806,	// 新邮件
		MT_MAIL_EXTRA_NORMAL_SC				= 9807,	// 普通物品附件
		MT_MAIL_EXTRA_EQUIP_SC				= 9808,	// 装备附件
		MT_MAIL_FLASH_SC					= 9810,	// 提示邮件闪烁
		MT_MAIL_SEND_RESULT_SC				= 9811,	// 发送邮件结果
		MT_MAIL_LIST_CS						= 9850,	// 请求邮件
		MT_MAIL_DETAIL_CS					= 9851,	// 请求邮件内容
		MT_MAIL_DELETE_CS					= 9853,	// 请求删除邮件
		MT_MAIL_GET_EXTRA_CS				= 9854,	// 请求提取附件
		MT_MAIL_GET_EXTRA_ALL_CS			= 9855,	// 请求提取全部附件
		// 好友
		MT_FRIEND_MEMBER_LIST_SC			= 9900,	// 返回列表的信息
		MT_FRIEND_ADD_REQ_SC				= 9901,	// 请求加对方为好友
		MT_FRIEND_ADD_REPLY_SC				= 9902,	// 答复加好友结果给请求方
		MT_FRIEND_ADD_MEMBER_SC				= 9903,	// 列表添加成员返回
		MT_FRIEND_DEL_MEMBER_SC				= 9904,	// 删除好友
		MT_FRIEND_LOGIN_SC					= 9905,	// 好友上线
		MT_FRIEND_LOGOUT_SC					= 9906,	// 好友下线
		MT_FRIEND_UPGRADE_SC				= 9907,	// 好友升级
		MT_FRIEND_CHAT_SC					= 9908, // 好友聊天返回
		MT_FRIEND_SHAKE_SC					= 9909, // 好友窗口抖动返回
		MT_FRIEND_CHAT_INFO_SC				= 9910,	// 聊天时请求对方信息返回	
		MT_FRIEND_MEMBER_LIST_REQ_CS		= 9950,	// 打开好友系统面板
		MT_FRIEND_ADD_REQ_CS				= 9951,	// 添加好友
		MT_FRIEND_ADD_REPLY_CS				= 9952,	// 对方回复添加请求
		MT_FRIEND_DEL_MEMBER_CS				= 9953,	// 删除成员
		MT_FRIEND_CONGRATULATE_CS			= 9954,	// 祝贺好友升级
		MT_FRIEND_BATCH_ADD_REQ_CS			= 9955,	// 批量加好友
		MT_FRIEND_CHAT_CS					= 9956,	// 好友聊天
		MT_FRIEND_SHAKE_CS					= 9957,	// 好友窗口抖动
		MT_FRIEND_CHAT_INFO_CS				= 9958, // 聊天时请求对方信息
		// 市场
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
		// 其它
		MT_MYSTERY_SHOP_EVENT_INFO_SC		= 10100,// 手气榜信息返回
		MT_MYSTERY_SHOP_ADD_EVENT_SC		= 10101,// 手气榜增加条目
		MT_TREASURE_HUNT_EVENT_INFO_SC		= 10102,// 寻宝珍品记录信息返回
		MT_TREASURE_HUNT_ADD_EVENT_SC		= 10103,// 寻宝珍品记录增加条目
		MT_FLOWER_OFFLINE_SC				= 10104,// 对方离线
		MT_FLOWER_GIVE_SUCCESS_SC			= 10105,// 赠送成功
		MT_FLOWER_GIVE_SUCCESS_BROADCAST_SC	= 10106,// 播放赠送鲜花特效
		MT_VIEW_ROLE_INFO_RET_SC			= 10107,// 查看资料返回
		MT_SEND_LOUDSPEAKER_MSG_SC			= 10108,// 发送小喇叭信息
		MT_OTHER_LOGOUT_SC					= 10109,// 对方下线返回
		MT_SERVER_NOTICE_SC					= 10110,// 服务器公告
		MT_ACTIVITY_STATE_NOTICE_SC			= 10111,// 活动开始公告
		MT_ARMY_NOTICE_SC					= 10112,// 帮派公告
		MT_TL_ACTIVITY_ICON_STATE_SC		= 10113,// 限时活动图标状态
		MT_SEND_COMMAND_TO_CLIENT_SC		= 10114,// 发送命令给客户端
		MT_WAS_FINISH_TIME_SC				= 10115,// 全服活动完成次数

		MT_TREASURE_HUNT_EVENT_INFO_CS		= 10150,// 请求寻宝珍宝记录
		MT_FLOWER_GIVE_CS					= 10151,// 赠送鲜花
		MT_VIEW_ROLE_INFO_CS				= 10152,// 查看资料
		// 交易系统
		MT_TRADE_REQ_CS						= 10200, // 请求交易
		MT_TRADE_REPLY_REQ_CS				= 10201, // 回复请求
		MT_TRADE_AFFIRM_TRADE_CS			= 10202, // 确认交易
		MT_TRADE_CANCEL_CS					= 10203, // 取消交易
		MT_TRADE_REQ_SC						= 10250, // 请求交易
		MT_TRADE_REPLY_REQ_SC				= 10251, // 回复请求
		MT_TRADE_LOCK_ITEM_SC				= 10252, // 锁定货品
		MT_TRADE_AFFIRM_TRADE_SC			= 10253, // 确认交易
		MT_TRADE_CANCEL_SC					= 10254, // 取消交易

		// 结婚
		MT_WEDDING_PROPOSAL_REQ_CS			= 10300,// 请求结婚
		MT_WEDDING_PROPOSAL_REPLY_CS		= 10301,// 回复请求结婚
		MT_WEDDING_DIVORCE_CS				= 10302,// 离婚

		MT_WEDDING_PROPOSAL_REQ_SC			= 10350,// 请求结婚
		MT_WEDDING_NOTICE_SC				= 10351,// 结婚信息返回
		// 系统消息
		MT_SYSTEM_ERROR_CODE_SC				= 60000,// 错误码返回
		MT_SYSTEM_OPERATION_RESULT_SC		= 60001,// 操作码结果
	};
}

#endif

