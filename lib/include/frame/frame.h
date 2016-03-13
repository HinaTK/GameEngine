
#ifndef FRAME_H
#define FRAME_H

class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual void		Exit() = 0;
	virtual	void		Wait() = 0;

	void				SetExit();
	bool				IsRun(){ return m_is_run; }

private:
	bool		m_is_run;

};



#endif // !SCENEFRAME_H
