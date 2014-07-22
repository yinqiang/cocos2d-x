
#include "cocos2d.h"

using namespace cocos2d;

class AppControllerBridge : public Ref
{
public:
    AppControllerBridge(void *controller)
    : m_controller(controller)
    {
    }
    
    void onWelcomeNewProject(Ref *object);
    void onWelcomeOpen(Ref *object);
    void onWelcomeSamples(Ref *object);
    void onWelcomeGetStarted(Ref *object);
    void onWelcomeGetCommunity(Ref *object);
    void onWelcomeOpenRecent(Ref *object);

private:
    void *m_controller;
};
