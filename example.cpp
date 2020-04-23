#include "websocket.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>

int main() {
    using wsclient::WebSocket;
    std::unique_ptr<WebSocket> ws(WebSocket::from_url("ws://localhost:8126/foo"));
    assert(ws);
    ws->send("goodbye");
    ws->send("hello");
    while (ws->getReadyState() != WebSocket::CLOSED) {
        WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
        ws->poll();
        ws->dispatch([wsp](const std::string & message) {
            printf(">>> %s\n", message.c_str());
            if (message == "world") { wsp->close(); }
        });
    }
    return 0;
}
