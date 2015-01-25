
#ifndef SCENEFRAME_H
#define SCENEFRAME_H

#include "frame.h"
#include "libsocket.h"

class SceneFrame : Frame
{
public:
	SceneFrame(){}
	~SceneFrame(){}

private:
	InCom	m_in_com;
};


#endif // !SCENEFRAME_H
