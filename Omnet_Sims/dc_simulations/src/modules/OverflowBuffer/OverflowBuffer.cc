#include "./OverflowBuffer.h"
#include <algorithm>
#include "inet/common/Simsignals.h"
#include "inet/common/StringFormat.h"
#include "inet/queueing/buffer/PacketBuffer.h"

namespace inet {
namespace queueing {

Define_Module(OverflowBuffer);

void OverflowBuffer::initialize(int stage)
{
    PacketBuffer::initialize(stage);
}

bool OverflowBuffer::isOverloaded()
{
    return (packetCapacity != -1 && getNumPackets() > packetCapacity) ||
           (dataCapacity != b(-1) && getTotalLength() > dataCapacity);
}

void OverflowBuffer::addPacket(Packet *packet)
{
    std::cout << "Inside addPacket" << endl;
    Enter_Method("addPacket");
    EV_INFO << "Adding packet " << packet->getName() << " to the buffer.\n";
    std::cout << "Trying Adding packet " << packet->getName() <<endl;
    emit(packetAddedSignal, packet);
    totalLength += packet->getTotalLength();
    std::cout << "Before push_back" <<endl;
    packets.push_back(packet);
    std::cout << "After push_back, packets size: " << packets.size() <<endl;
    if (isOverloaded()) {
        if (packetDropperFunction != nullptr)
            packetDropperFunction->dropPackets(this);
        else
            throw cRuntimeError("Buffer is overloaded but packet dropper function is not specified");
    }
    std::cout << "After check overloaded" << endl;
    // updateDisplayString();
    std::cout << "After update displaystring" <<endl;
}

void OverflowBuffer::removePacket(Packet *packet)
{
    Enter_Method("removePacket");
    EV_INFO << "Removing packet " << packet->getName() << " from the buffer.\n";
    emit(packetRemovedSignal, packet);
    totalLength -= packet->getTotalLength();
    packets.erase(find(packets.begin(), packets.end(), packet));
    updateDisplayString();
    ICallback *callback = check_and_cast<ICallback *>(packet->getOwner()->getOwner());
    callback->handlePacketRemoved(packet);
}

Packet *OverflowBuffer::getPacket(int index)
{
    if (index < 0 || (size_t)index >= packets.size())
        throw cRuntimeError("index %i out of range", index);
    return packets[index];
}



} // namespace queueing
} // namespace inet
