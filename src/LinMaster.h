//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef LINMASTER_H_
#define LINMASTER_H_

#include "LinNode.h"
#include <queue>

class LinMaster: public LinNode {
public:
    LinMaster();
    virtual ~LinMaster();
protected:

    /* this is a message to simulate some kind of system dynamics.
     * the master changes the need for sporadic messages every now and then
     * using this selfmsg
     */
    cMessage *changeSporadic;

    //this bolean value holds the information whether a sporadic message should be sent
    bool needSporadic;

    virtual void initialize();
    virtual void handleSelfMessage(cMessage *msg);
    virtual void receiveFrame(cMessage *msg);
    virtual void finish();


    /*
     * todo: declare needed member variables
     */
    int eventtriggeredCounter;
    int sporadicCounter;
    int eventCounter;

    int event_id;
    int collisions;

    bool sporadicPositiv;

    simtime_t sended_sporadic;
    cMessage *clockTimer;
    cMessage *eventTimer;

    cOutVector sporadic_delay;
    cOutVector collision_vec;
    cOutVector unconditional_vec;
    cOutVector sporadic_vec;
    cOutVector event_vec;
};

#endif /* LINMASTER_H_ */
