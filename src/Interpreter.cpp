///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Interpreter.cpp

Autor: Dominic Wanner

Beschreibung:
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Interpreter.h"

Interpreter::Interpreter()
{
    BF = new SQL();
    BF->openDB("../DB/BF");
    BF->createTable("Befehl");
}

Interpreter::~Interpreter()
{
    BF->closeDB();
    delete BF;
    BF = NULL;
}

int Interpreter::searchBF(std::string s, std::string name)
{
    std::string dp = ":";
    std::string sname = name + dp;

    if (s.find(sname) != std::string::npos)
    {
        s.erase(0, strlen(sname.c_str()) +1);
        printf("%s\n", s.c_str());
        return BF->search(s);
    }
    else
        return 0;
}
