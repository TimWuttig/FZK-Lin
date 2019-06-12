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

#include "LinMaster.h"

Define_Module(LinMaster)

LinMaster::LinMaster() {
}

LinMaster::~LinMaster() {
    delete clockTimer;
    delete eventTimer;
    delete changeSporadic;
}

void LinMaster::initialize() {


    needSporadic = false;
    changeSporadic = new cMessage("changeSporadic");
    scheduleAt(simTime() + 2 + dblrand() * 2, changeSporadic);

    /*
     * initialize all variables needed
     */
    timeCounter = 0;
    collisions = 0;
    eventCounter = 0;

    sporadicPositiv = true;

    sporadic_vec.setName("Sporadic Frame Ids");
    unconditional_vec.setName("Unconditional Frame Ids");
    event_vec.setName("Eventtriggered Frame Ids");
    sporadic_delay.setName("Sporadic Frame delay");
    collision_vec.setName("Number of collisions");

    eventTimer = new cMessage("eventTimer");
    clockTimer = new cMessage("clockTimer");
    scheduleAt(simTime() + 0.01, clockTimer);
}

void LinMaster::finish() {
    /*
     * Record final statistics
     */
    collision_vec.record(collisions);
}

void LinMaster::handleSelfMessage(cMessage *msg) {

    if (msg == changeSporadic) {
        needSporadic = true;
        scheduleAt(simTime() + 2 + dblrand() * 2, changeSporadic);
    }

    /*
     * handle Self Messages in order to send next packet or check timeouts
     */
    if (msg == clockTimer){
        timeCounter = (timeCounter + 1) % 6;
        switch(timeCounter){
            case 3:
                if(needSporadic){
                    int id = intuniform(40,49);
                    sendLinRequest(id);
                    sporadic_vec.record(id);
                    if(sporadicPositiv){
                        sended_sporadic = simTime();
                        sporadicPositiv = false;
                    }
                }
                break;
            case 5:
                event_id = intuniform(50, 59);
                sendLinRequest(event_id);
                scheduleAt(simTime() + 0.001, eventTimer);
                event_vec.record(event_id);
                break;
            default:
                int id = intuniform(0, 39);
                sendLinRequest(id);
                unconditional_vec.record(id);
                break;
        }

        scheduleAt(simTime()+ 0.01, clockTimer);
    }

    if(msg = eventTimer){
        if(eventCounter > 1){
            std::vector<int> responsible = getEventTriggeredIds(event_id);
            for(int id: responsible){
                sendLinRequest(id);
            }
        }

        eventCounter = 0;
    }
}

void LinMaster::receiveFrame(cMessage *msg) {

    /*
     * handle received Frames, check for collisions
     */
    LinResponseFrame* frame = (LinResponseFrame*) msg;
    FRAME_TYPE type = getFrameType(frame->getMessageId());
    switch(type){
        case SPORADIC_FRAME:
            if(frame->getResponse() == 1){
                needSporadic = false;
                sporadic_delay.record(simTime() - sended_sporadic);
                sporadicPositiv = true;
            }
            else needSporadic = true;
            break;
        case EVENT_TRIGGERED_FRAME:
            eventCounter++;
            collisions++;
    }
}

