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
    /*
     * todo: delete all cMessages
     */
}

void LinMaster::initialize() {


    needSporadic = false;
    changeSporadic = new cMessage("changeSporadic");
    scheduleAt(simTime() + 2 + dblrand() * 2, changeSporadic);

    /*
     * todo: initialize all variables needed
     */

}

void LinMaster::finish() {
    /*
     * Record final statistics
     */
}

void LinMaster::handleSelfMessage(cMessage *msg) {

    if (msg == changeSporadic) {
        needSporadic = true;
        scheduleAt(simTime() + 2 + dblrand() * 2, changeSporadic);
    }

    /*
     * todo: handle Self Messages in order to send next packet or check timeouts
     */

}

void LinMaster::receiveFrame(cMessage *msg) {

    /*
     * todo: handle received Frames, check for collisions
     */
}

