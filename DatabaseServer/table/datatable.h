#ifndef DATATABLE_H
#define DATATABLE_H

#include "database/gamemysql.h"
#include "database/gamemysqlstmt.h"
#include "globalvariable.h"

namespace Table
{
    GameMysql new_table("new_table");
    namespace NEW_TABLE
    {
        enum Field
        {
            Name,
            Age,
            School
        };
        const char * Fields[] = {"name","age","school"};
    }

    GameMysql gametime("gametime");
    namespace GAMETIME
    {
        enum Field
        {
            OpenServerTime,
            ActiveDate,
            PetLiveTime,
            Time
        };
        const char * Fields[] = {"openservertime","activedate","petlivetime","time"};
    }

    GameMysqlStmt smt("smt");
    namespace SMT
    {
        enum Field
        {
            Id,
            Name,
            MAX_FIELD
        };
        const char * Fields[] = {"id", "name"};
        MYSQL_BIND params[SMT::MAX_FIELD];
    }
}


#endif // DATATABLE_H
