///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Interpreter.h

Autor: Dominic Wanner

Beschreibung:
--------------
Diese Klasse Schaut ob es sich bei der eingabe um einen Befehl handelt
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @class Interpreter
*
* @brief Diese Klasse Interpritiert Behfele
*
* Der Interpreter schaut ob ein Befehl eingeben wurde und gibt einen wert der zum Befehl gehört weiter an den Kommunikater.
* Für eine einfache erweiterung beinhaltet er eine Datenbank mit Befehlen die werweitert werden kann, oder um Befehle umzubennen.
*
*/
#ifndef _Interpreter_H_
#define _Interpreter_H_

#include "Datenbank.h"
#include <string.h>
#include <stdio.h>

class Interpreter {
    public:
    Interpreter();
    ~Interpreter();

    /**
    * @brief searchBF() Sucht in Datenbank nach Befehl
    * @param s für Channel eingabe
    * @param bs Falls befehl einen Zusatz hatte wird dieser zurück gegeben über diesen string pointer
    * Sucht in datenbank nach passenden Befehl und gibt Befehls wert zurück.
    */
    int searchBF(std::string s, std::string name, std::string* bs);

    private:
    SQL *BF;
};

#endif

