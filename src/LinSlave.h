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

#ifndef LINSLAVE_H_
#define LINSLAVE_H_

#include "LinNode.h"

class LinSlave : public LinNode
{
	public:
		LinSlave();
		virtual ~LinSlave();

	protected:

		//this is the only function a slave have to implement. intelligence
		//is inside the master
		virtual void receiveFrame(cMessage *msg);

};

#endif /* LINSLAVE_H_ */
