
#ifndef LOG_FILE_H
#define LOG_FILE_H

class LogFile
{
public:
	LogFile();
	~LogFile();

	void	Normal(char *log, ...);

	void	Warn(char *log, ...);

	void	Error(char *log, ...);

private:
	//FILE		*m_log_fp;
};


#endif