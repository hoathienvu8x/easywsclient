#include <iostream>
#include <thread>
#include <signal.h>
#include <string>
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <winsock2.h>
#endif
#include <assert.h>
#include "easywsclient.h"

using easywsclient::WebSocket;

bool m_running = false;
std::string url = "";
WebSocket * ws = NULL;

void websocket_listen() {
  #ifdef _WIN32
  INT rc;
  WSADATA wsaData;

  rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (rc) {
    std::cout << "WSAStartup Failed.\n";
    return 1;
  }
  #endif
  while (1) {
    while (
      ws == NULL || ws->getReadyState() == WebSocket::CLOSED
    ) {
      if (ws != NULL) {
        delete(ws);
      }
      ws = WebSocket::from_url(url);
    }
    while (ws->getReadyState() != WebSocket::CLOSED) {
      ws->poll();
      WebSocket::pointer wsp = &*ws;
      ws->dispatch([wsp](const std::string msg) {
        std::cout << msg << std::endl;
      });
    }
  }
  #ifdef _WIN32
  WSACleanup();
  #endif
}

void signal_ctrl_c(int sig) {
  std::cout << "signal: " << sig << std::endl;  
  exit(sig);
}

int main(int argc, char ** argv) {
  signal(SIGINT, signal_ctrl_c);
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <url>" << std::endl;
    return -1;
  }
  url = std::string(argv[1]);
  if (url.size() == 0) {
    std::cout << "Invalid url" << std::endl;
    return -1;
  }
  m_running = true;
  std::thread * th = new std::thread(&websocket_listen);
  assert(th);
  th->join();
  return 0;
}
