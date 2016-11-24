
#ifndef THREAD_SYS_ID
#define THREAD_SYS_ID


#define BASE_THREAD_MSG_TYPE(ThreadType) (ThreadType) * 256

namespace ThreadSysID
{
	enum
	{
		TSID_MAX_ID = 10000,
		TSID_CLASS,				// 基于类来执行
		TSID_RPC,
		TSID_EXIT,
		TSID_THREAD_CMD,
		
	};
}

#endif // !THREAD_SYS_ID
