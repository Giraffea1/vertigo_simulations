//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

package dc_simulations.modules.OverflowBuffer;

import inet.queueing.buffer.PacketBuffer;
import inet.queueing.contract.IPacketBuffer;

//
// This module provides an overflow packet storage for the originally deflected packets
// between multiple packet queues. When a packet buffer becomes overloaded, the
// packet dropping strategy can drop any number of packets from any number of
// connected packet queues.
//
//
simple OverflowBuffer extends PacketBuffer
{
    parameters:
        // int testV = 2;
        // dataCapacity = b(7000);
        dropperClass = default("inet::queueing::PacketAtCollectionBeginDropper"); // determines which packets are dropped when the buffer is overloaded, packets are not dropped by default; the parameter must be the name of a C++ class which implements the IPacketDropperFunction C++ interface and is registered via Register_Class
}
