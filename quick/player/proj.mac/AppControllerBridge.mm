
#include "AppControllerBridge.h"
#import "AppController.h"

void AppControllerBridge::onWelcomeNewProject(Ref *object)
{
    [(AppController*)m_controller welcomeNewProject];
}

void AppControllerBridge::onWelcomeOpen(Ref *object)
{
    [(AppController*)m_controller welcomeOpen];
}

void AppControllerBridge::onWelcomeSamples(Ref *object)
{
    [(AppController*)m_controller welcomeSamples];
}

void AppControllerBridge::onWelcomeGetStarted(Ref *object)
{
    [(AppController*)m_controller welcomeGetStarted];
}

void AppControllerBridge::onWelcomeGetCommunity(Ref *object)
{
    [(AppController*)m_controller welcomeCommunity];
}

void AppControllerBridge::onWelcomeOpenRecent(Ref *object)
{
    [(AppController*)m_controller welcomeOpenRecent:object];
}
