
#include "websocket/sendframe.h"
#include "websocket/dataframeheader.h"
#include "libcommon/memorypool.h"

REGISTER_MEMORYPOOL(memorypool, SendFrame, 64);

SendFrame::SendFrame(NetID _net_id, const char* src, unsigned int src_len, bool mask)
: net_id(_net_id)
{				
// 	static char extend_data[FrameHeader::MID_EXTEND_LEN] = { 0 };		// 一般没有数据
// 	static char mask_data[FrameHeader::MASK_LEN] = { 0 };			// 一般没有数据
// 	unsigned char extend_len = 0;
// 	unsigned char mask_len = 0;
// 	unsigned char pl_len = (unsigned char)src_len;		// pay load
// 
// 	if (src_len >= 126 && src_len < 65536)
// 	{
// 		pl_len = 126;
// 		extend_len = FrameHeader::MID_EXTEND_LEN;
// 	}
// 	else if (src_len >= 65536)
// 	{
// 		// 数据太大
// 		//pl_len = 127;
// 		return;
// 	}
// 	if (mask)
// 	{
// 		mask_len = FrameHeader::MASK_LEN;
// 	}
// 	unsigned int frame_length = FrameHeader::HEADER_LEN + extend_len + mask_len + src_len;
// 	if (!MemoryVL::Instance().Malloc(frame_length, data_frame))
// 	{
// 		return;
// 	}
// 	FrameHeader header(true, false, false, false, 1, mask, src_len);
// 	header.Header(data_frame.mem);
// 	if (extend_len > 0)
// 	{
// 		memcpy(data_frame.mem + FrameHeader::HEADER_LEN, extend_data, extend_len);
// 	}
// 	if (mask_len > 0)
// 	{
// 		memcpy(data_frame.mem + FrameHeader::HEADER_LEN + extend_len, mask_data, FrameHeader::MASK_LEN);
// 	}
}

SendFrame::~SendFrame()
{
	MemoryVL::Instance().Free(data_frame);
}
