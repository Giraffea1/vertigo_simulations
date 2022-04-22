#ifndef OVERFLOWBUFFER_H
#define OVERFLOWBUFFER_H

#include "inet/queueing/buffer/PacketBuffer.h"

#include "inet/queueing/base/PacketBufferBase.h"
#include "inet/queueing/contract/IPacketBuffer.h"
#include "inet/queueing/contract/IPacketCollection.h"
#include "inet/queueing/contract/IPacketDropperFunction.h"

namespace inet {
namespace queueing {

// ? use inet_api
class INET_API OverflowBuffer : public PacketBuffer
{
  protected:
    int packetCapacity = -1;
    b dataCapacity = b(-1);

    b totalLength = b(0);
    std::vector<Packet *> packets;

    IPacketDropperFunction *packetDropperFunction = nullptr;

  protected:
    virtual void initialize(int stage) override;

    virtual bool isOverloaded();

  public:
    virtual int getMaxNumPackets() override { return packetCapacity; }
    virtual int getNumPackets() override { return packets.size(); }

    virtual b getMaxTotalLength() override { return dataCapacity; }
    virtual b getTotalLength() override { return totalLength; }

    virtual Packet *getPacket(int index) override;
    virtual bool isEmpty() override { return packets.size() == 0; }

    virtual void addPacket(Packet *packet) override;
    virtual void removePacket(Packet *packet) override;

    virtual bool supportsPushPacket(cGate *gate) override { return false; }
    virtual bool supportsPopPacket(cGate *gate) override { return false; }
};

} // namespace queueing
} // namespace inet

#endif // ifndef __INET_PACKETBUFFER_H
