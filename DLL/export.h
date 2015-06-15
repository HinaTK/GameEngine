
#ifndef EXPORT_H
#define	EXPORT_H

//__declspec(dllexport) void Register(Interface* interface);
class DLL;

class Test
{
public:
	Test(){};
	~Test(){};

	void	Show();
private:

};

__declspec(dllexport) void Register();

__declspec(dllexport) void Register( DLL **dll);

__declspec(dllexport) void Register( int &a);

__declspec(dllexport) void Register(Test &test);

#endif