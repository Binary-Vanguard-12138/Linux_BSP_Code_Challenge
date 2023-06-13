#ifndef _ATSHARED_H_
#define _ATSHARED_H_

#include <stdint.h>

#define TIMELINE	"TIME\n"
#define htonll(x) ((1==htonl(1)) ? (x) : ((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define ntohll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))


uint64_t get_time_since_epoch();

#endif //_ATSHARED_H_
