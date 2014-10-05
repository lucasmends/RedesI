#ifndef NETUTILS_H_INCLUDED
#define NETUTILS_H_INCLUDED

#include <netinet/in.h>

uint64_t htonll(uint64_t* value){
    uint64_t vv = *((uint64_t*) value);
    int num = 42;
    if(*(char *)&num == 42) //test big/little endian
        return (((uint64_t)htonl(vv)) << 32) + htonl(vv >> 32);
    else
        return vv;
}

uint64_t ntohll(uint64_t* value){
    uint64_t vv = *((uint64_t*) value);
    int num = 42;
    if(*(char *)&num == 42) //test big/little endian
        return (((uint64_t)ntohl(vv)) << 32) + ntohl(vv >> 32);
    else
        return vv;
}

uint16_t hton(const uint16_t &num)
{
    return htons(num);
}


uint32_t hton(const uint32_t &num)
{
    return htonl(num);
}

uint64_t hton(uint64_t &num)
{
    return htonll(&num);
}

uint16_t ntoh(const uint16_t &num)
{
    return ntohs(num);
}

uint32_t ntoh(const uint32_t &num)
{
    return ntohl(num);
}

uint64_t ntoh(uint64_t &num)
{
    return ntohll(&num);
}

#endif // NETUTILS_H_INCLUDED
