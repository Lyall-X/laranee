#include "net_sys.h"

#include <signal.h>

#include "base/logging.h"

void NetSystem::Init()
{
    server_entity_ = CreateEntity<ServerEntity>();
    signal(SIGPIPE, SIG_IGN);  // Ignore SIGPIPE to prevent crashes on broken pipes
    signal(SIGINT, [](int) {
        GINFO("Received SIGINT, stopping NetSystem...");
        NetSystem::Instance().Stop();
    });
}

void NetSystem::Run(std::function<bool()>&& main_loop)
{
    MainThreadComponent* cmp = server_entity_->GetComponent<MainThreadComponent>();
    cmp->main_thread.Run([main_loop]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return main_loop();
    });

    for (auto* reactor : server_entity_->GetComponent<ReactorComponent>()->reactors_)
    {
        reactor->GetComponent<IOThreadComponent>()->io_thread.Run([reactor]() {
            GDEBUG("IO thread for reactor {} is running", reactor->Id());
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return true;
        });
    }
    while (running_.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void NetSystem::Stop()
{
    running_.store(false);
    MainThreadComponent* cmp = server_entity_->GetComponent<MainThreadComponent>();
    cmp->main_thread.Stop();
    for (auto* reactor : server_entity_->GetComponent<ReactorComponent>()->reactors_)
    {
        reactor->GetComponent<IOThreadComponent>()->io_thread.Stop();
    }
}