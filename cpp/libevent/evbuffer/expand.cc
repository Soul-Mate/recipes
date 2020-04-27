#include <event2/buffer.h>
#include <iostream>
#include <cstring>

int main()
{
    struct evbuffer *evBuf = evbuffer_new();
    const int mib = 1024 * 1024;
    char data[mib];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < mib; j++) // 1mib
        {
            data[j] = "0123456789ABCDE"[j % 16];
        }

        if (evbuffer_add(evBuf, data, mib) == -1)
        {
            perror("evbuffer_add");
            abort();
        }
    }

    auto sz = evbuffer_get_length(evBuf);
    std::printf("buffer size: %dbit\n", sz);

    // expand
    if (evbuffer_expand(evBuf, sz * 2) == -1)
    {
        perror("evbuffer_expand");
        abort();
    }

    unsigned char *pullData = evbuffer_pullup(evBuf, sz);
    char tmp[sz];
    std::memcpy(tmp, pullData, sz);
    evbuffer_add(evBuf, tmp, sz);
    evbuffer_add(evBuf, tmp, sz);

    std::printf("expand after, buffer size: %d\n", evbuffer_get_length(evBuf));

    evbuffer_free(evBuf);
}
