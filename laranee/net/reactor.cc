#include "reactor.h"

#include <sys/epoll.h>

#include "base/logging.h"
#include "base/time.h"

ReactorEntity::ReactorEntity()
{
    EpollComponent* epoll_cmp = GetComponent<EpollComponent>();
    epoll_cmp->epoll_fd       = epoll_create1(0);
    if (epoll_cmp->epoll_fd < 0)
    {
        GERROR("Failed to create epoll instance");
        return;
    }
}

void ReactorEntity::Listen(const std::string& ip, int port)
{
    UDPAcceptComponent* accept_cmp = GetComponent<UDPAcceptComponent>();
    accept_cmp->ip                 = ip;
    accept_cmp->port               = port;

    accept_cmp->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (accept_cmp->sockfd < 0)
    {
        GERROR("Failed to create socket");
        return;
    }
    bzero(&accept_cmp->addr, sizeof(accept_cmp->addr));
    accept_cmp->addr.sin_family      = AF_INET;
    accept_cmp->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    accept_cmp->addr.sin_port        = htons(port);

    GDEBUG("Reactor Listening on {}:{}", ip, port);

    if (bind(accept_cmp->sockfd, (struct sockaddr*)&(accept_cmp->addr), sizeof(struct sockaddr_in)) < 0)
    {
        GERROR("Failed to bind socket to {}:{}", ip, port);
        close(accept_cmp->sockfd);
        accept_cmp->sockfd = -1;
        return;
    }

    // kcp init
    auto* reactor_action_cmp = GetComponent<ReactorActionComponent>();
    ikcpcb* kcp              = ikcp_create(0x1, reactor_action_cmp);
    ikcp_setmtu(kcp, 1400);
    kcp->output = [](const char* buf, int len, struct IKCPCB* kcp, void* reactor_action_cmp) -> int {
        ReactorActionComponent* reactor = static_cast<ReactorActionComponent*>(reactor_action_cmp);
        return reactor->output_action(buf, len);
    };                               // Set the output function for KCP
    ikcp_nodelay(kcp, 0, 10, 0, 0);  // Set KCP parameters
    ikcp_wndsize(kcp, 128, 128);     // Set KCP window size
    accept_cmp->pkcp = kcp;

    // add listen socket to epoll
    EpollComponent* epoll_cmp = GetComponent<EpollComponent>();
    struct epoll_event ev;
    ev.events  = EPOLLIN;
    ev.data.fd = accept_cmp->sockfd;
    GDEBUG("Registering fd: {}, ev.data.fd: {}", accept_cmp->sockfd, ev.data.fd);
    int ret = epoll_ctl(epoll_cmp->epoll_fd, EPOLL_CTL_ADD, accept_cmp->sockfd, &ev);
    if (ret < 0)
    {
        GERROR("Failed to add socket to epoll");
        return;
    }
}

bool ReactorEntity::OnLoop()
{
    EpollComponent* epoll_cmp = GetComponent<EpollComponent>();
    if (epoll_cmp->epoll_fd < 0)
    {
        GERROR("Invalid epoll file descriptor");
        return false;
    }
    // UDP
    UDPAcceptComponent* udp_accept_cmp = GetComponent<UDPAcceptComponent>();
    if (udp_accept_cmp->pkcp)
        ikcp_update(udp_accept_cmp->pkcp, Time::Now());

    // Wait for events on the epoll file descriptor
    struct epoll_event events[10];
    int nfds = epoll_wait(epoll_cmp->epoll_fd, events, 1024, 1000);
    if (nfds < 0)
    {
        GERROR("Failed to wait on epoll file descriptor");
        return false;
    }

    for (int i = 0; i < nfds; ++i)
    {
        if (events[i].events & EPOLLIN)
        {
            // Handle read event
            UDPAcceptComponent* udp_accept_cmp = GetComponent<UDPAcceptComponent>();
            GDEBUG("eventfd: {}, Triggered fd: {}, udp_accept_cmp->sockfd: {}", epoll_cmp->epoll_fd, events[i].data.fd, udp_accept_cmp->sockfd);
            if (events[i].data.fd == udp_accept_cmp->sockfd)
            {
                socklen_t addr_len = sizeof(udp_accept_cmp->addr);
                uint32_t n         = recvfrom(udp_accept_cmp->sockfd, udp_accept_cmp->buffer, sizeof(udp_accept_cmp->buffer), MSG_DONTWAIT,
                                              (struct sockaddr*)&udp_accept_cmp->addr, &addr_len);
                if (n > 0)
                {
                    ikcp_input(udp_accept_cmp->pkcp, udp_accept_cmp->buffer, n);
                    int recv_len = ikcp_recv(udp_accept_cmp->pkcp, udp_accept_cmp->buffer, n);
                    if (recv_len < 0)
                        continue;
                }
            }
        }
        else if (events[i].events & (EPOLLERR | EPOLLHUP))
        {
            GERROR("Error on socket: {}", events[i].data.fd);
            close(events[i].data.fd);
            continue;
        }
    }
    GDEBUG("Reactor Loop: {}, fd size: {}", Id(), nfds);
    return true;
}