
#ifndef BRIDGE_H
#define BRIDGE_H

class CPU
{
public:
	CPU()
	{
		name = (char *)malloc(32);
	};
	~CPU()
	{
		free(name);
	};

private:
	char *name;
};

class Computer
{
public:
	Computer(){};
	~Computer(){};

	CPU	&GetCPU1(){ return m_cpu; }

	CPU	*GetCPU2(){ return &m_cpu; }

private:
	CPU m_cpu;
};

#endif