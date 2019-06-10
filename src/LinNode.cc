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

#include "LinNode.h"

Define_Module(LinNode)

LinNode::LinNode() {

}

LinNode::~LinNode() {

}

void LinNode::handleMessage(cMessage *msg) {

	if (msg->isSelfMessage()) {
		handleSelfMessage(msg);
	}
	else {
		receiveFrame(msg);
	}

}

void LinNode::handleSelfMessage(cMessage *msg) {
    //supposed to be overridden by master and slave classes
}

void LinNode::receiveFrame(cMessage *frame) {
    //supposed to be overridden by master and slave classes
    delete frame;
}

void LinNode::sendLinRequest(int messageId) {

    std::cerr << "sending " << messageId << std::endl;
	int n = gateSize("outgate");
    for (int i = 0; i < n; i++) {
    	LinRequestFrame *frame = new LinRequestFrame();
    	frame->setMessageId(messageId);
    	send(frame, "outgate", i);

    }

}

void LinNode::sendLinResponse(int messageId, int response) {
    std::cerr << "sending response for " << messageId << " with " << response << std::endl;
    LinResponseFrame* frame = new LinResponseFrame();
    frame->setMessageId(messageId);
    frame->setResponse(response);

    send(frame, "outgate");

}

