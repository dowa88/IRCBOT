///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Datenbank.h

Autor: Dominic Wanner

Beschreibung:
-------------
In diesem teil des Programms ist alles enthalten um auf eine Datenbank zuzugreife und zu erstellen so wie diese zu Löschen
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _Datenbank_H_
#define _Datenbank_H_

#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

struct eintrag
{
    std::string name;
    std::string inhalt;
    std::string date;
    std::string time;
};

class SQL {
    public:
    SQL();
    ~SQL();

    void openDB(const char name[]);
    void createTable(std::string name);
    std::vector<eintrag> search(std::string name);
    void deleteDB();
    std::vector<eintrag> readDB();
    std::vector<eintrag> readFromTo(std::string fromtime, std::string totime, std::string fromdate, std::string todate);
    std::vector<eintrag> readFromToday(std::string fromtime, std::string totime);
    void writeDB(eintrag e);
    void closeDB();

    private:
    sqlite3* db;
    std::string tablename;

};

#endif
