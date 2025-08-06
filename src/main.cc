#include "net/net_sys.h"

bool OnTick()
{
    GDEBUG("Main loop tick");
    return true;  // Return false to stop the loop
}

int main()
{
    Logging::Instance().Init("laranee");
    NetSystem::Instance().Init();
    NetSystem::Instance().Run(OnTick);
    return 0;
}
