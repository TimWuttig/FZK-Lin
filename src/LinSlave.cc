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

#include "LinSlave.h"

Define_Module(LinSlave)

LinSlave::LinSlave()
{}

LinSlave::~LinSlave()
{}

void LinSlave::receiveFrame(cMessage *msg) {
    LinRequestFrame *frame = (LinRequestFrame*) msg;

    int message_id = frame->getMessageId();
    /*
     * todo: handle received Frames, send responses
     */
    FRAME_TYPE type = getFrameType(message_id);

    switch(type){
        case UNCONDITIONAL_FRAME:
            if(getId() == message_id){
                int response = intuniform(0, INT32_MAX);
                sendLinResponse(message_id, response);
            }
            break;
        case SPORADIC_FRAME:
            if(getId() == message_id){
                int response = intuniform(0, 1);
                sendLinResponse(message_id, response);
            }
            break;
        case EVENT_TRIGGERED_FRAME:
            if(isResponsibleForEventTriggered(message_id)){
                sendLinResponse(message_id, 0);
            }
            break;
    }
}
