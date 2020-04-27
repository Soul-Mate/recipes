#include <iostream>
#include <thread>
#include <chrono>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <csignal>

#include <event2/buffer.h>
#include <event2/thread.h>
void parseSock4(struct evbuffer *evbuf)
{
    for (;;)
    {
        size_t sz = ::evbuffer_get_length(evbuf);
        if (sz == 0 || sz % 32 != 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        else
        {
            if (sz == 32)
            {
                ::evbuffer_lock(evbuf);
                unsigned char *data = ::evbuffer_pullup(evbuf, 32);

                uint16_t port;
                char ip[INET_ADDRSTRLEN];
                memcpy(&port, data, 16);
                memcpy(ip, data + 16, 16);

                std::printf("parse result %s:%d\n", ip, port);

                ::evbuffer_drain(evbuf, 32);
                ::evbuffer_unlock(evbuf);
            }
            else
            {
                ::evbuffer_lock(evbuf);
                unsigned char *data = ::evbuffer_pullup(evbuf, sz);

                // TODO FIXME
                for (int i = 0, n = sz / 32; i < n; i++)
                {
                    uint16_t port;
                    char ip[INET_ADDRSTRLEN];
                    memcpy(&port, data + (i * 32), 16);
                    memcpy(ip, data + 16 + (i * 32), 16);

                    std::printf("parse result %s:%d\n", ip, port);
                }
                ::evbuffer_drain(evbuf, sz);
                ::evbuffer_unlock(evbuf);
            }
        }
    }
}

void runClient()
{
    int servFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (servFd == -1)
    {
        perror("socket");
        return;
    }

    struct sockaddr_in serverAddr;
    ::bzero(&serverAddr, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ::htons(19999);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    int ret = ::connect(servFd, (const struct sockaddr *)&serverAddr, sizeof serverAddr);
    if (ret == -1)
    {
        perror("connect");
    }
    char ack = 'n';
    int rn, wn;
    wn = send(servFd, &ack, 1, 0);
    if (wn != 1)
    {
        perror("send");
        return;
    }

    rn = recv(servFd, &ack, 1, 0);
    if (rn != 1)
    {
        perror("recv");
        return;
    }

    if (ack == 'y')
    {
        ::shutdown(servFd, SHUT_RDWR);
        std::printf("%lld trhead done.\n", std::this_thread::get_id());
    }
}

int main()
{

    signal(SIGHUP, SIG_IGN);
    int servFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (servFd == -1)
    {
        perror("socket");
        return 0;
    }

    struct sockaddr_in serverAddr;
    ::bzero(&serverAddr, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = ::htons(19999);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int ret = ::bind(servFd, (const sockaddr *)&serverAddr, sizeof serverAddr);
    if (ret == -1)
    {
        perror("bind");
        return 0;
    }

    if ((ret = ::listen(servFd, 5)) == -1)
    {
        perror("listen");
        return 0;
    }

    struct evbuffer *evbuf = ::evbuffer_new();

    for (int i = 0; i < 50; i++)
    {
        std::thread clientThread(runClient);
        clientThread.detach();
    }

    int cnt = 0;

    std::thread parseThread(parseSock4, evbuf);
    parseThread.detach();

    while (true)
    {
        struct sockaddr_in remoteAddr;
        socklen_t remoteAddrLen = 0;
        int remoteFd = ::accept(servFd, (struct sockaddr *)&remoteAddr, &remoteAddrLen);
        if (remoteFd == -1)
        {
            perror("accpet");
            continue;
        }

        uint16_t port = ntohs(remoteAddr.sin_port) + (++cnt);
        char ip[INET_ADDRSTRLEN];
        ::inet_ntop(AF_INET, &remoteAddr.sin_addr.s_addr, ip, INET_ADDRSTRLEN);

        // packed port, addr data add to evbuffer 16 + 32
        char data[32];
        memcpy(data, &port, 16);
        memcpy(data + 16, ip, 16);
        ::evbuffer_lock(evbuf);
        if (::evbuffer_add(evbuf, data, 32) != 0)
        {
            ::evbuffer_unlock(evbuf);
            ::evbuffer_free(evbuf);
            perror("evbuffer_add");
            abort();
        }
        ::evbuffer_unlock(evbuf);

        char ack;
        int rn, wn;
        for (;;)
        {
            rn = recv(remoteFd, &ack, 1, 0);
            if (rn == 0)
            {
                ::shutdown(remoteFd, SHUT_WR);
                char buf[256];
                while (recv(servFd, buf, sizeof buf, 0) > 0)
                {
                }
                break;
            }

            if (ack == 'n')
            {
                ack = 'y';
            }
            else
            {
                std::printf("invalid protocol\n");
                break;
            }

            if (send(remoteFd, &ack, 1, 0) != 1)
            {
                perror("send");
            }
        }
        ::close(remoteFd);
    }

    evbuffer_free(evbuf);
}