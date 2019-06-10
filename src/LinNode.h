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

#ifndef LINNODE_H_
#define LINNODE_H_

#include <omnetpp.h>
#include "LinRequestFrame_m.h"
#include "LinResponseFrame_m.h"

using namespace omnetpp;

//ranges for message ids
/**
 * 40 unconditional frames. For simplicity, message #i is
 * handled by ECU #i
 */
#define FIRST_UNCONDITIONAL     0
#define LAST_UNCONDITIONAL      39

/**
 * 10 sporadic frames
 */
#define FIRST_SPORADIC          40
#define LAST_SPORADIC           49

/**
 * 10 event triggered frames: for simplicity, 1 for 4 ECUs.
 * For example, E.T. frame #50, is for ECUs #0, 1, 2 and 3
 * E.T. frame #51 is for ECUs #4, 5, 6 and 7 and so on
 */
#define UNCONDITIONALS_PER_EVENT_TRIGGERED 4
#define FIRST_EVENT_TRIGGERED   50
#define LAST_EVENT_TRIGGERED    59


enum FRAME_TYPE {
    UNCONDITIONAL_FRAME,
    EVENT_TRIGGERED_FRAME,
    SPORADIC_FRAME,
    UNKNOWN
};

class LinNode: public cSimpleModule {
public:
    LinNode();
    virtual ~LinNode();

protected:
    virtual void initialize() {};
    virtual void handleMessage(cMessage *msg);
    virtual void handleSelfMessage(cMessage *msg);
    virtual void finish() {};

    /**
     * Invoked when a LIN frame is received
     */
    virtual void receiveFrame(cMessage *msg);

    /**
     * Send down a LIN request message with the given id.
     * Used by master node
     */
    virtual void sendLinRequest(int messageId);

    /**
     * Send down a LIN response message with the given
     * response.
     * Used by slave nodes
     */
    virtual void sendLinResponse(int messageId, int response);


    /**
     * Tells the type of the give message id (unconditional, event
     * triggered, or sporadic)
     */
    enum FRAME_TYPE getFrameType(int messageId) {
        if (isUnconditional(messageId)) {
            return UNCONDITIONAL_FRAME;
        }
        else {
            if (isEventTriggered(messageId)) {
                return EVENT_TRIGGERED_FRAME;
            }
            else {
                if (isSporadic(messageId)) {
                    return SPORADIC_FRAME;
                }
                else {
                    return UNKNOWN;
                }
            }
        }
    }

    /**
     * Given the id of an event triggered message, returns
     * the set of message ids that the event triggered message
     * regards. Basically, given the id, the list contains
     * the ECUs that might reply
     */
    std::vector<int> getEventTriggeredIds(int messageId) {

    	std::vector<int> ids;

    	if (!isEventTriggered(messageId)) {
    		ASSERT2(false, "Bad programmer! This should never happen!");
    	}

    	/* for simplicity, we assume that each event triggered message
    	 * regards four unconditional messages, so we map each event
    	 * triggered id with four unconditional ids
    	 */

    	messageId -= FIRST_EVENT_TRIGGERED;
    	messageId *= UNCONDITIONALS_PER_EVENT_TRIGGERED;
    	for (int i = 0; i < UNCONDITIONALS_PER_EVENT_TRIGGERED; i++)
    		ids.push_back(messageId + i);

    	return ids;

    }

    /**
     * Given the id of an event triggered message
     * tells whether the ECU is responsible
     * for the message
     */
    bool isResponsibleForEventTriggered(int messageId) {

    	if (!isEventTriggered(messageId)) {
    		ASSERT2(false, "Bad programmer! This should never happen!");
    	}

    	messageId -= FIRST_EVENT_TRIGGERED;
    	messageId *= UNCONDITIONALS_PER_EVENT_TRIGGERED;

    	//check whether the ECU id is within the range of messages that the event
    	//triggered message regards
    	if (getIndex() >= messageId && getIndex() < messageId + UNCONDITIONALS_PER_EVENT_TRIGGERED) {
    		return true;
    	}
    	else {
    		return false;
    	}

    }
private:
    /**
     * Tells whether the given message id is an unconditional frame
     */
    bool isUnconditional(int messageId) {
        return (messageId >= FIRST_UNCONDITIONAL && messageId <= LAST_UNCONDITIONAL);
    }
    /**
     * Tells whether the given message id is an event triggered frame
     */
    bool isEventTriggered(int messageId) {
        return (messageId >= FIRST_EVENT_TRIGGERED && messageId <= LAST_EVENT_TRIGGERED);
    }
    /**
     * Tells whether the given message id is a sporadic frame
     */
    bool isSporadic(int messageId) {
        return (messageId >= FIRST_SPORADIC && messageId <= LAST_SPORADIC);
    }

};

#endif /* LINNODE_H_ */
