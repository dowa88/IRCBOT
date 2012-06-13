///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Kommunikater.h

Autor: Dominic Wanner

Beschreibung:
------------------
Dieser teil wählt sich im Server ein und gibt nachrichten nach ausen und hört zu
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../bib/libircclient-1.6/include/libircclient.h"
#include "Datenbank.h"

struct Im
{
    char 	* channel;
	char 	* nick;
	char    * server;
};

class Kommunikater {
    public:
    Kommunikater();
    ~Kommunikater();

    void commitServer();
    void commitChanel();

    void chanceChanel();
    void chanceServer();

    void sendMassage();
    void listen();

    private:
    SQL* Kom;
    SQL* Doc;
};
