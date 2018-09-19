#include "../../../UDP/Socket/UDPSocket.h"

int main(int argc, char *argv[]) {

  assert(argc!=3);

  std::string mcAdr = argv[1];

  auto test=(int)strtol(argv[1], (char **)nullptr, 10);

  try {

      UDPSocket sock(static_cast<unsigned short>(test));

    sock.joinGroup(mcAdr);

    char rcv[_BSZ + 1];

    std::string sourceAddress;

    unsigned short sourcePort;

    int rcvd = sock.recvFrom(rcv, _BSZ, sourceAddress,sourcePort);

    rcv[rcvd] = '\0';

    std::cout << "Received " << rcv << " from " << sourceAddress << ": " << sourcePort << std::endl;

  }
  catch (SocketException &e) {

    std::cerr << e.what() << std::endl;

    exit(1);

  }
  return 0;
}
