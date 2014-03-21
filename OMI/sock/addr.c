/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include "addr.h"
#include <ctype.h>
#include <string.h>

/* Include network headers */
#if defined(CONFIG_OS_WINDOWS)
# include <winsock2.h>
#elif defined(CONFIG_POSIX)
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>
#endif

#if defined(CONFIG_OS_WINDOWS)
typedef unsigned long InAddr;
#else
typedef in_addr_t InAddr;
#endif

/* disabling IPv6 OACR warnings - D3M bug 52 */

MI_Result Addr_Init(
    Addr* self_,
    const char* host,
    unsigned short port)
{
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 24002)
#endif
    struct sockaddr_in* self = (struct sockaddr_in*)self_;
    struct sockaddr_in* addr;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif

    /* Clear address */
    memset((char*)self, 0, sizeof(*self));
    addr = (struct sockaddr_in*)self;

    if (isalpha((unsigned char)host[0]))
    {
        /* Handle host name */
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 24001)
#pragma prefast (disable: 38026)
#endif
        struct hostent* p = gethostbyname((char*)host);
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
        if (!p)
            return MI_RESULT_FAILED;

        addr->sin_family = p->h_addrtype;
        memcpy(&addr->sin_addr, p->h_addr, p->h_length);
    }
    else
    {
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 24001)
#endif
        /* Handle dotted notation */
        InAddr ip = inet_addr((char*)host);
#ifdef _PREFAST_
#pragma prefast (pop)
#endif

        if (ip == (InAddr)-1)
            return MI_RESULT_FAILED;

        addr->sin_addr.s_addr = ip;
        addr->sin_family = AF_INET;
    }

    /* Set the port */
    self->sin_port = htons(port);
    return MI_RESULT_OK;
}

void Addr_InitAny(
    Addr* self_,
    unsigned short port)
{
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 24002)
#endif
    struct sockaddr_in* self = (struct sockaddr_in*)self_;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif

    memset((char*)self, 0, sizeof(*self));
    self->sin_family = AF_INET;
    self->sin_addr.s_addr = htonl(INADDR_ANY);
    self->sin_port = htons(port);
}
