#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in target;

    std::string ip;
    std::cout << "Enter target IP: ";
    std::cin >> ip;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }

    for (int port = 1; port <= 1024; port++) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) continue;

        target.sin_family = AF_INET;
        target.sin_addr.s_addr = inet_addr(ip.c_str());
        target.sin_port = htons(port);

        if (connect(sock, (sockaddr*)&target, sizeof(target)) == 0) {
            std::cout << "Port " << port << " is OPEN\n";
        }
        closesocket(sock);
    }

    WSACleanup();
    return 0;
}
