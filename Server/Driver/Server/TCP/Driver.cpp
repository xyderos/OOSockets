#include "../../../TCP/Socket/TCPSocket.h"
#include "../../../TCP/ServerSocket/TCPServerSocket.h"

void HandleTCPClient(TCPSocket *sock);

void *ThreadMain(void *arg);

int main(int argc, char *argv[]) {

  assert(argc==2);

  auto test=(int)strtol(argv[1], (char **)nullptr, 10);

  try {
    TCPServerSocket sc(static_cast<unsigned short>(test));

    for (;;) {

      TCPSocket *clSc = sc.accept();

      pthread_t threadID;pthread_create(&threadID, nullptr, ThreadMain, (void *) clSc);

    }
  } catch (SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
}

void HandleTCPClient(TCPSocket *sock) {

  char buffer[_BSZ];

  size_t sz;

  while ((sz = static_cast<size_t>(sock->recv(buffer, _BSZ))) > 0)
    sock->send(buffer, static_cast<int>(sz));

}

void *ThreadMain(void *arg) {

  pthread_detach(pthread_self());

  HandleTCPClient((TCPSocket *) arg);

  delete (TCPSocket *) arg;

  return nullptr;
}
