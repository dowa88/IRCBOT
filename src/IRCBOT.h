///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
IRCBOT.h

Autor: Dominic Wanner

Beschreibung:
-------------

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* @mainpage IRCBOT
* @author Dominic Wanner
*
* Dies ist ein IRCBOT denn man über eingaben in den Channel steuern kann. <br>>
* Befehle werden wie folgt gesenndet:<br>
* BOTNAME: BEFEHL "ZUSATZ"<br><br>
* Es gibt folgende Befehle:<br><br>
* LOG -> gibt alle Log einsträge aus<br>
* Start LOG -> startet Log führung (standart mässig an)<br>
* Stop LOG -> stop Log führung<br>
* Last seen "NICKNAME" -> gibt alle Log einträge von NICKNAME aus<br>
* Stop -> Stopt den BOT und beendet ihn<br>
*
*/


/**
* @class IRCBOT
*
* @brief Diese Klasse ist der Bot
*
* IRCBOT der der Bot dieser muss anglegt werden um einen Bot zuerstellen. Mit der Funktion initBot() bekommt der Bot informationen über das struct Iam auf welchen Server er gehen soll, in welchen Channel und seinen nick
*/
#ifndef _IRCBOT_H_
#define _IRCBOT_H_

#include "Kommunikater.h"

class IRCBOT{
    public:
    IRCBOT();
    ~IRCBOT();

    /**
    * @brief initBot() angebe von Serverinformationen
    * @param _iam ist das beinhaltet jeweils einen string zu Server, Channel und Nickname
    *
    * Mit dem struct Iam wird hier dem Bot mitgeteilt werlchen Server und Chandel er besuchen soll und wie er heist
    */
    void initBot(Iam _iam);
    /**
    * @brief startBot() Startet den Bot
    *
    * Hier Starte der Bot seine Arbeit
    */
    void startBot();

    private:
    /**
    * Private Variable.
    * Kommunikater für Kommunikation
    */
    Kommunikater* Kom;
};

#endif
