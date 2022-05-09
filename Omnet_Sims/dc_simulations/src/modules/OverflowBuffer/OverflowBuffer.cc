#include "./OverflowBuffer.h"
#include <algorithm>
#include "inet/common/Simsignals.h"
#include "inet/common/StringFormat.h"
#include "inet/queueing/buffer/PacketBuffer.h"

namespace inet {
namespace queueing {

Define_Module(OverflowBuffer);

void OverflowBuffer::addPacket(Packet *packet)
{
    std::cout << "Inside addPacket, and buffer capacity is: " << getMaxTotalLength() << endl;
    // std::cout << "Packet dropper function is : " << packetDropperFunction << endl;
    Enter_Method("addPacket");
    EV_INFO << "Adding packet " << packet->getName() << " to the buffer.\n";
    // std::cout << "Trying Adding packet " << packet->getName() <<endl;
    emit(packetAddedSignal, packet);
    totalLength += packet->getTotalLength();
    // std::cout << "Before push_back" <<endl;
    packets.push_back(packet);
    // std::cout << "After push_back, buffer size: " << packets.size() <<endl;
    if (isOverloaded()) {
        std::cout << "Getting overloaded!" << endl;
        if (packetDropperFunction != nullptr) {
            std::cout << "Before drop: " << getTotalLength() << endl;
            packetDropperFunction->dropPackets(this);
            std::cout << "After drop: " << getTotalLength() << endl;
        }
        else
            throw cRuntimeError("Buffer is overloaded but packet dropper function is not specified");
    }
    // std::cout << "After check overloaded" << endl;
    // updateDisplayString();
    // std::cout << "After update displaystring" <<endl;
    // std::cout << "Test V: " << testV << endl;
    // std::cout << "Test S: " << testS << endl;
}

void OverflowBuffer::removePacket(Packet *packet)
{
        std::cout << "Entered removePacket" << endl;
    Enter_Method("removePacket");
         std::cout << "45" << endl;
    EV_INFO << "Removing packet " << packet->getName() << " from the buffer.\n";
        // std::cout << "Removing packet " << packet->str() << endl;
    emit(packetRemovedSignal, packet);
        std::cout << "52" << endl;
    totalLength -= packet->getTotalLength();
    packets.erase(find(packets.begin(), packets.end(), packet));
            std::cout << "55" << endl;
    // updateDisplayString();
    // ICallback *callback = check_and_cast<ICallback *>(packet->getOwner()->getOwner());
                // std::cout << "57" << endl;
    // callback->handlePacketRemoved(packet);
            std::cout << "End of removePacket" << endl;
}



} // namespace queueing
} // namespace inet
