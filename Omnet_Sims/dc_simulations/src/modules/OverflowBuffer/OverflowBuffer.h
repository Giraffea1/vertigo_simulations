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
    // test variable
    int testV = 3;
    // const char *testS;
    IPacketDropperFunction *packetDropperFunction = check_and_cast<IPacketDropperFunction *>(createOne("inet::queueing::PacketAtCollectionBeginDropper"));;

  public:
    virtual void addPacket(Packet *packet) override;
    virtual void removePacket(Packet *packet) override;
    virtual void setLenCapacity(int length) {dataCapacity = b(length);};
};

} // namespace queueing
} // namespace inet

#endif // ifndef __INET_PACKETBUFFER_H
