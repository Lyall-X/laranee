#include "server.h"

#include "base/logging.h"
#include "net_sys.h"

ServerEntity::ServerEntity()
{
    ReactorComponent* cmp = GetComponent<ReactorComponent>();
    for (int i = 0; i < IO_THREAD_NUM; ++i)
    {
        cmp->reactors_.emplace_back(NetSystem::Instance().CreateEntity<ReactorEntity>());
    }
}