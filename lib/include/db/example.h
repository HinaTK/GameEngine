
#ifndef DB_EXAMPLE_H
#define DB_EXAMPLE_H

#include "field.h"
#include "fieldmanager.h"

// #define DB_FIELD_INFO(XX)       	\
// 	XX(id, IDField) 		\
// 	XX(rank, RankData) 		\
// 
// 
// enum db_field
// {
// #define XX(name, fun) FIELD_##name,
// 	DB_FIELD_INFO(XX)
// #undef XX
// };
// 
// static const char *field_strings[] =
// {
// #define XX(name, fun) #name,
// 	DB_FIELD_INFO(XX)
// #undef XX
// };
// 
// class IDField : public Field
// {
// public:
// 	const char *GetName(){ return field_strings[FIELD_id]; }
// 	FieldIndex GetIndex() { return FIELD_id; };
// 
// 	int id;
// };
// 
// CreateField rd_fields[] =
// {
// #define XX(name, fun) {#name, NewField(fun)},	
// 	DB_FIELD_INFO(XX)
// #undef XX	
};
#endif // !DB_EXAMPLE_H

