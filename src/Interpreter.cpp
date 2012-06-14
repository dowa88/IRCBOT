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

int Interpreter::searchBF(std::string s, std::string name, std::string* bs)
{
    std::string dp = ":";
    std::string sname = name + dp;
    std::vector<eintrag> e;

    if (s.find(sname) != std::string::npos)
    {
        s.erase(0, strlen(sname.c_str()) +1);
        int i = s.find("\"");
        if(i != std::string::npos)
        {
            char c[256];
            int len = s.copy(c, strlen(s.c_str())-(strlen(s.c_str())-i+3)-1, strlen(s.c_str())-i+3);
            c[len] ='\0';
            *bs = c;
            s.erase(i-1, strlen(bs->c_str())+6);
        }
        printf("%s %s\n", s.c_str(), bs->c_str());
        e = BF->search(s);
        int ret = 0;
        if(!e.empty())
            ret = atoi( e[0].inhalt.c_str() );
        return ret;
    }
    else
    {
        bs = NULL;
        return 0;
    }
}
