///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Datenbank.cpp

Autor: Dominic Wanner

Beschreibung:
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Datenbank.h"

SQL::SQL()
{
    db = NULL;
}

SQL::~SQL()
{
    if(db != NULL)
    {
        sqlite3_close(db);
        db = NULL;
    }
}

void SQL::openDB(const char name[])
{
    sqlite3_open(name, &db);
}

void SQL::deleteDB()
{
    std::string s = "drop table " + tablename;
    sqlite3_exec(db, s.c_str(), NULL, NULL, NULL);
}

void SQL::createTable(std::string name)
{
    tablename = name;
    std::string s = "CREATE TABLE " + name + " (name text, Inhalt text, Datum date, Uhr time);";
    sqlite3_exec(db, s.c_str(), NULL, NULL, NULL);
}

void SQL::closeDB()
{
     if(db != NULL)
    {
        sqlite3_close(db);
        db = NULL;
    }
}

void SQL::writeDB(eintrag e)
{
    std::string s = "INSERT INTO " + tablename + " (name, Inhalt, Datum, Uhr) VALUES ('"+e.name+"','"+e.inhalt+"', date(), time());";
    sqlite3_exec(db, s.c_str(), NULL, NULL, NULL);
}

std::vector<eintrag> SQL::readDB()
{
    std::vector<eintrag> e;

}


















