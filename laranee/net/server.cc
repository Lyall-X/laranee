#include "server.h"

#include "base/logging.h"
#include "net_sys.h"

ServerEntity::ServerEntity()
{
    ReactorComponent* cmp = GetComponent<ReactorComponent>();
    cmp->accept_reactor_  = NetSystem::Instance().CreateEntity<ReactorEntity>();
    cmp->accept_reactor_->Listen("0.0.0.0", 8888);

    for (int i = 0; i < IO_THREAD_NUM; ++i)
    {
        cmp->io_reactors_.emplace_back(NetSystem::Instance().CreateEntity<ReactorEntity>());
    }
}