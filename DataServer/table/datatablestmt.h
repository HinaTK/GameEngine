
#ifndef DATATABLE_STMT_H
#define DATATABLE_STMT_H

#include <stdio.h>
#include <string>

#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#endif

#include "include/mysql.h"

/*
	mysql 预处理
	1、mysql的预处理读出与写入都会绑定地址
*/

class Father
{
public:
	Father(){}
	virtual ~Father(){}

	virtual bool Insert()
	{
		std::string insertSql = "";
		std::string *fields = GetField();
		int maxField = GetMaxField();
		std::string val;
		insertSql = "INSERT INTO " + m_table_name + " (";
		for (int i = 0; i < maxField; ++i)
		{
			insertSql += fields[i] + ",";
			val += "?,";
		}
		insertSql.replace(insertSql.size() - 1, 1, ") VALUES (");
		val.replace(val.size() - 1, 1, ");");
		insertSql += val; 
		return true;
	}

	virtual bool Select()
	{
		std::string selectSql = "";
		std::string *fields = GetField();
		selectSql = "SELECT * FROM " + m_table_name + ";";
		int maxField = GetMaxField();
		return true;
	}

	virtual bool			Update(){return true;}
	virtual int				GetMaxField() = 0;
	virtual std::string *	GetField() = 0;
	virtual void			SetSelectCondition(int key, int val)
	{
		m_select_condition += m_select_condition
	};
protected:
	std::string m_table_name;
	std::string m_select_condition;
private:

};

class Son:public Father
{
public:
	~Son(){}
	static Son &Instance()
	{
		static Son instance("son");
		return instance;
	}
	enum Field
	{
		Id,
		Name,
		MAX_FIELD,
	};
	int id;
	char name[32];
	MYSQL_BIND param[MAX_FIELD];
	int GetMaxField(){ return Son::MAX_FIELD;}
	bool Update(){return true;};
	std::string * GetField()
	{
		return m_fieldname;
	}
private:
	Son(std::string tablename)
	{
		m_table_name = tablename;
		m_fieldname[Son::Id] = "id";
		m_fieldname[Son::Name] = "name";

		param[Son::Id].buffer_type = MYSQL_TYPE_LONG;
		param[Son::Id].buffer = &id;
		
		param[Son::Name].buffer_type = MYSQL_TYPE_STRING;
		param[Son::Name].buffer = name;
		param[Son::Name].buffer_length = strlen(name);
	};
	std::string m_fieldname[MAX_FIELD];
	
};

#endif