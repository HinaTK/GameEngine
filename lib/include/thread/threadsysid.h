
#ifndef THREAD_SYS_ID
#define THREAD_SYS_ID


#define BASE_THREAD_MSG_TYPE(ThreadType) (ThreadType) * 256

namespace ThreadSysID
{
	enum
	{
		TSID_CLASS = 1,			// 基于类来执行
		TSID_RPC,
		TSID_EXIT,
		TSID_THREAD_CMD,
		TSID_MAX_ID = 100,
	};
}

#endif // !THREAD_SYS_ID
