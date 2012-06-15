///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Datenbank.h

Autor: Dominic Wanner

Beschreibung:
-------------
In diesem teil des Programms ist alles enthalten um auf eine Datenbank zuzugreife und zu erstellen so wie diese zu Löschen
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @class SQL
*
* @brief Diese Klasse ist eine Datenbank
*
* Hier bei handelt es sich um einen Datenbank Klasse die mit SQLite arbeitet. Die Tabellen der Datenbank werden immer nach dem gleichen Schema erzeugt.
* Jede Tabele hat ein Splate name, Inhalt, Date und Uhr. Wobei Date und Uhr automatisch gefühlt beim erstellen mit Inhalt gefühlt werden.
*
*/
#ifndef _Datenbank_H_
#define _Datenbank_H_

#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

/**
* Ein struct das eine Zeile der Datenbank darstellt. Wird zum lesen und schreiben, der Datenbank, benötigt.
 */
struct eintrag
{
    /*@{*/
    std::string name; /**< enthält inhalt der Spalte name*/
    std::string inhalt; /**< enthält inhalt der Spalte Inahlt*/
    std::string date; /**< enthält inhalt der Spalte Date*/
    std::string time; /**< enthält inhalt der Spalte Uhr*/
    /*@}*/
};

class SQL {
    public:
    SQL();
    ~SQL();

    /**
    * @brief openDB() Öffnet oder erstellt Datenbank
    * @param name Name der Datenbank
    *
    * Diese Funktion öffnet oder erstellt eine neue Datenbank, mit dem Namen der in name übergeben wird.
    */
    void openDB(const char name[]);

    /**
    * @brief createTable() Öffnet oder erstellt Tabelle
    * @param name Name der Tabelle
    *
    * Diese Funktion öffnet oder erstellt eine neue Tabelle in der Datenbank, mit dem Namen der in name übergeben wird.
    */
    void createTable(std::string name);

    /**
    * @brief search() Sucht in der Datenbank nach name
    * @param name Name nach dem gesucht wird
    *
    * Diese Funktion gibt alle Datenbank einträge in einen std::vector<eintrag> zurück, die in der Spalte name den in parameter stehenden name haben.
    */
    std::vector<eintrag> search(std::string name);

    /**
    * @brief deleteDB() Löscht Datenbank inhalt
    *
    *
    * Leert die komplete Datenbank
    */
    void deleteDB();

    /**
    * @brief readDB() liest alle eintrage der Datenbank
    *
    *
    * Diese Funktion gibt alle Datenbank eintrage als std::vector<eintrag> zurück
    */
    std::vector<eintrag> readDB();

    /**
    * @brief readFromTo() liest Datum und Zeit abhangig eintrage aus der Datenbank
    * @param fromtime die Zeit von
    * @param totime die Zeit bis
    * @param fromdate das Datum von
    * @param todate das Datum bis
    *
    * Diese Funktion gibt alle eintrage von einen Bestimmten Zeit abschnit als std::vector<eintrag> aus. VORSICHT FUNKTION WIRD IM IRCBOT NOCH NICHT VERWENDET!
    */
    std::vector<eintrag> readFromTo(std::string fromtime, std::string totime, std::string fromdate, std::string todate);

    /**
    * @brief readFromToday() liest Zeit abhängig alle Einträge von Heute
    * @param fromtime die Zeit von
    * @param totime die Zeit bis
    *
    * Diese Funktion gibt alle Einträge von einen Bestimmten Zeit abschnitt vom Akktuellen Tag als std::vector<eintrag> aus. VORSICHT FUNKTION WIRD IM IRCBOT NOCH NICHT VERWENDET!
    */
    std::vector<eintrag> readFromToday(std::string fromtime, std::string totime);

    /**
    * @brief writeDB() Schreibt einen Datenbank eintrag
    * @param e beinhaltet zu schreibende Daten
    *
    * mit dieser Funktion wird in die Datenbank geschrieben.
    */
    void writeDB(eintrag e);

    /**
    * @brief closeDB() schliesst Datenbank
    *
    *
    * mit dieser Funktion wird die Datenbank geschlossen.
    */
    void closeDB();

    private:
    sqlite3* db;
    std::string tablename;

};

#endif
