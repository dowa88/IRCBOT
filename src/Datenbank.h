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
#include <vector>

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
    std::vector<eintrag> readDB();
    std::vector<eintrag> readFromTo(int fyear, int fmonth, int fday, int fhour, int fminute, int tyear, int tmonth, int tday, int thour, int tminute);
    std::vector<eintrag> readFromToday(int fhour, int fminute, int thour, int tminute);
    void writeDB(eintrag e);
    void closeDB();

    private:
    sqlite3* db;
    std::string tablename;

};
