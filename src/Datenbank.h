///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Datenbank.h

Autor: Dominic Wanner

Beschreibung:
-------------
In diesem teil des Programms ist alles enthalten um auf eine Datenbank zuzugreife und zu erstellen so wie diese zu Löschen
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sqlite3.h>
#include <string>

struct eintrag
{
    std::string name;
    std::string inhalt;
};

class SQL {
    public:
    SQL();
    ~SQL();

    void openDB(const char name[]);
    void createTable(std::string name);
    void deleteDB();
    void readDB();
    void writeDB(eintrag e);
    void closeDB();

    private:
    sqlite3* db;
    std::string tablename;

};
