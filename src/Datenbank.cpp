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

int SQL::search(std::string name)
{
    sqlite3_stmt *stmt;
    std::string s = "SELECT Inhal FROM " + tablename +"WHERE Name = " + name;
    sqlite3_prepare_v2(db, s.c_str(), -1, &stmt, NULL);
    int i;

    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::ostringstream isst;
        isst << sqlite3_column_text(stmt, 0);
        i = atoi( isst.str().c_str() );
    }
    return i;
}

std::vector<eintrag> SQL::readDB()
{
    std::vector<eintrag> e;
    sqlite3_stmt *stmt;
	std::string s = "SELECT * FROM " + tablename;

	sqlite3_prepare_v2(db, s.c_str(), -1, &stmt, NULL);

	while(sqlite3_step(stmt) != SQLITE_DONE)
	{
	    std::ostringstream string;

        eintrag a;

        string << sqlite3_column_text(stmt, 0);
        a.name = string.str();
        string.str("");

        string << sqlite3_column_text(stmt, 1);
        a.inhalt = string.str();
        string.str("");

        string << sqlite3_column_text(stmt, 2);
        a.date = string.str();
        string.str("");

        string << sqlite3_column_text(stmt, 3);
        a.time = string.str();
        string.str("");

        e.push_back(a);
	}

	sqlite3_finalize(stmt);

    return e;
}

std::vector<eintrag> SQL::readFromTo(std::string fromtime, std::string totime, std::string fromdate, std::string todate)
{
     std::vector<eintrag> e;

     sqlite3_stmt *stmt;
     std::string s = "SELECT * FROM (SELECT * FROM " + tablename + " WHERE Datum BETWEEN '"+fromdate+"' AND '"+todate+"')" + tablename + " WHERE Uhr BETWEEN '"+fromtime+"' AND '"+totime+"'";

     sqlite3_prepare_v2(db, s.c_str(), -1, &stmt, NULL);

     while(sqlite3_step(stmt) != SQLITE_DONE)
     {
         std::ostringstream string;

         eintrag a;

         string << sqlite3_column_text(stmt, 0);
         a.name = string.str();
         string.str("");

         string << sqlite3_column_text(stmt, 1);
         a.inhalt = string.str();
         string.str("");

         string << sqlite3_column_text(stmt, 2);
         a.date = string.str();
         string.str("");

         string << sqlite3_column_text(stmt, 3);
         a.time = string.str();
         string.str("");

         e.push_back(a);
     }
     sqlite3_finalize(stmt);

     return e;

}

std::vector<eintrag> SQL::readFromToday(std::string fromtime, std::string totime)
{
     std::vector<eintrag> e;

     sqlite3_stmt *stmt;
     std::string s = "SELECT * FROM (SELECT * FROM " + tablename + " WHERE Datum = date())" + tablename + " WHERE Uhr BETWEEN '"+fromtime+"' AND '"+totime+"'";

     sqlite3_prepare_v2(db, s.c_str(), -1, &stmt, NULL);

     while(sqlite3_step(stmt) != SQLITE_DONE)
     {
         std::ostringstream string;

         eintrag a;

         string << sqlite3_column_text(stmt, 0);
         a.name = string.str();
         string.str("");

         string << sqlite3_column_text(stmt, 1);
         a.inhalt = string.str();
         string.str("");

         string << sqlite3_column_text(stmt, 2);
         a.date = string.str();
         string.str("");

         string << sqlite3_column_text(stmt, 3);
         a.time = string.str();
         string.str("");

         e.push_back(a);
     }
     sqlite3_finalize(stmt);

     return e;
}

















