
#import "AppController.h"

#include "AppDelegate.h"
#include "glfw3.h"
#include "glfw3native.h"

#include "cocos2d.h"
#include "CCLuaEngine.h"

#include "PlayerMac.h"

USING_NS_CC;

@implementation AppController

std::string getCurAppPath(void)
{
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

- (void) dealloc
{
    if (_buildTask)
    {
        [_buildTask interrupt];
        _buildTask = nil;
    }
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    player::Player::create();

    _isAlwaysOnTop = NO;
    _debugLogFile = 0;

    _buildTask = nil;
    _isBuildingFinished = YES;

    // load QUICK_COCOS2DX_ROOT from ~/.QUICK_COCOS2DX_ROOT
    NSMutableString *path = [NSMutableString stringWithString:NSHomeDirectory()];
    [path appendString:@"/.QUICK_V3_ROOT"];
    NSError *error = nil;
    NSString *env = [NSString stringWithContentsOfFile:path
                                              encoding:NSUTF8StringEncoding
                                                 error:&error];
    if (error || env.length == 0)
    {
        [self showAlertWithoutSheet:@"Please run \"setup_mac.sh\", set quick-cocos2d-x root path."
                          withTitle:@"quick player error"];
        [[NSApplication sharedApplication] terminate:self];
    }

    env = [env stringByTrimmingCharactersInSet:[NSCharacterSet newlineCharacterSet]];
    SimulatorConfig::getInstance()->setQuickCocos2dxRootPath([env cStringUsingEncoding:NSUTF8StringEncoding]);

    [self updateProjectFromCommandLineArgs:&_project];
    [self createWindowAndGLView];
    [self startup];
}

-(void) applicationDidResignActive: (NSNotification*) note
{
    cocos2d::EventCustom event("APP.EVENT");
    std::stringstream buf;

    buf << "{\"name\":\"focusOut\"}";

    event.setDataString(buf.str());
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

- (void) applicationDidBecomeActive:(NSNotification *)notification
{
    cocos2d::EventCustom event("APP.EVENT");
    std::stringstream buf;

    buf << "{\"name\":\"focusIn\"}";

    event.setDataString(buf.str());
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

- (BOOL) windowShouldClose:(id)sender
{
    return YES;
}

- (void) windowWillClose:(NSNotification *)notification
{
    [[NSRunningApplication currentApplication] terminate];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig
{
    return [self makeCommandLineArgsFromProjectConfig:kProjectConfigAll];
}

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig:(unsigned int)mask
{
    _project.setWindowOffset(Vec2(_window.frame.origin.x, _window.frame.origin.y));
    NSString *commandLine = [NSString stringWithCString:_project.makeCommandLine(mask).c_str()
                                               encoding:NSUTF8StringEncoding];
    return [NSMutableArray arrayWithArray:[commandLine componentsSeparatedByString:@" "]];
}

- (void) updateProjectFromCommandLineArgs:(ProjectConfig*)config
{
    NSArray *nsargs = [[NSProcessInfo processInfo] arguments];
    long n = [nsargs count];
    if (n == 2)
    {
        config->setProjectDir([[nsargs objectAtIndex:1] cStringUsingEncoding:NSUTF8StringEncoding]);
        config->setDebuggerType(kCCLuaDebuggerCodeIDE);
    }
    else
    {
        vector<string> args;
        for (int i = 0; i < [nsargs count]; ++i)
        {
            args.push_back([[nsargs objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        config->parseCommandLine(args);
    }

    if (config->getProjectDir().length() == 0)
    {
        config->resetToWelcome();
    }
}

- (void) launch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
}

- (void) relaunch:(NSArray*)args
{
    [self launch:args];
    [[NSApplication sharedApplication] terminate:self];
}

- (void) relaunch
{
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (void) showAlertWithoutSheet:(NSString*)message withTitle:(NSString*)title
{
    NSAlert *alert = [[[NSAlert alloc] init] autorelease];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:message];
	[alert setInformativeText:title];
	[alert setAlertStyle:NSWarningAlertStyle];
    [alert runModal];
}

- (void) loadLuaConfig
{
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

    luaopen_player_luabinding(pEngine->getLuaStack()->getLuaState());

    NSMutableString *path = [NSMutableString stringWithString:NSHomeDirectory()];
    [path appendString:@"/"];

    // set user home dir
    lua_pushstring(pEngine->getLuaStack()->getLuaState(), path.UTF8String);
    lua_setglobal(pEngine->getLuaStack()->getLuaState(), "__USER_HOME__");

    [path appendString:@".quick_player.lua"];


    NSString *luaCorePath = [[NSBundle mainBundle] pathForResource:@"player" ofType:@"lua"];
    pEngine->getLuaStack()->executeScriptFile(luaCorePath.UTF8String);

    const player::PlayerSettings &settings = player::PlayerProtocol::getInstance()->getPlayerSettings();

    _project.setWindowOffset(Vec2(settings.offsetX, settings.offsetY));
}

#pragma mark -
#pragma mark functions

- (void) createWindowAndGLView
{
    int width = _project.getFrameSize().width;
    int height = _project.getFrameSize().height;
    float scale = _project.getFrameScale();

    GLView *eglView = GLView::createWithRect("quick-x-player", cocos2d::Rect(0, 0, width, height), scale, _project.isResizeWindow());
    Director::getInstance()->setOpenGLView(eglView);

    _window = glfwGetCocoaWindow(eglView->getWindow());
    [NSApp setDelegate: self];
    [_window center];

    if (_project.getProjectDir().length())
    {
        [self setZoom:_project.getFrameScale()];
        Vec2 pos = _project.getWindowOffset();
        if (pos.x != 0 && pos.y != 0)
        {
            [_window setFrameOrigin:NSMakePoint(pos.x, pos.y)];
        }
    }

    [_window becomeFirstResponder];
    [_window makeKeyAndOrderFront:self];
    [_window setAcceptsMouseMovedEvents:NO];
}

- (void) startup
{
    std::string path = SimulatorConfig::getInstance()->getQuickCocos2dxRootPath();
    if (path.length() <= 0)
    {
        [self showPreferences:YES];
    }

    const string projectDir = _project.getProjectDir();
    if (projectDir.length())
    {
        FileUtils::getInstance()->setSearchRootPath(projectDir.c_str());
        if (_project.isWriteDebugLogToFile())
        {
            [self writeDebugLogToFile:_project.getDebugLogFilePath()];
        }
    }

    const string writablePath = _project.getWritableRealPath();
    if (writablePath.length())
    {
        FileUtils::getInstance()->setWritablePath(writablePath.c_str());
    }

    if (_project.isShowConsole())
    {
        [self openConsoleWindow];
    }

    _app = new AppDelegate();
    _app->setProjectConfig(_project);
    _app->run();

    // After run, application needs to be terminated immediately.
    [NSApp terminate: self];
}

- (void) openConsoleWindow
{
    if (!_consoleController)
    {
        _consoleController = [[ConsoleWindowController alloc] initWithWindowNibName:@"ConsoleWindow"];
    }
    [_consoleController.window orderFrontRegardless];

    //set console pipe
    _pipe = [NSPipe pipe] ;
    _pipeReadHandle = [_pipe fileHandleForReading] ;

    int outfd = [[_pipe fileHandleForWriting] fileDescriptor];
    if (dup2(outfd, fileno(stderr)) != fileno(stderr) || dup2(outfd, fileno(stdout)) != fileno(stdout))
    {
        perror("Unable to redirect output");
        //        [self showAlert:@"Unable to redirect output to console!" withTitle:@"quick-x-player error"];
    }
    else
    {
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(handleNotification:) name: NSFileHandleReadCompletionNotification object: _pipeReadHandle] ;
        [_pipeReadHandle readInBackgroundAndNotify] ;
    }
}

- (bool) writeDebugLogToFile:(const string)path
{
    if (_debugLogFile) return true;
    //log to file
    if(_fileHandle) return true;
    NSString *fPath = [NSString stringWithCString:path.c_str() encoding:[NSString defaultCStringEncoding]];
    [[NSFileManager defaultManager] createFileAtPath:fPath contents:nil attributes:nil] ;
    _fileHandle = [NSFileHandle fileHandleForWritingAtPath:fPath];
    [_fileHandle retain];
    return true;
}

- (void)handleNotification:(NSNotification *)note
{
    //NSLog(@"Received notification: %@", note);
    [_pipeReadHandle readInBackgroundAndNotify] ;
    NSData *data = [[note userInfo] objectForKey:NSFileHandleNotificationDataItem];
    NSString *str = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];

    //show log to console
    [_consoleController trace:str];
    if(_fileHandle!=nil){
        [_fileHandle writeData:[str dataUsingEncoding:NSUTF8StringEncoding]];
    }

}

- (void) close_debugLogFile
{
    if(_fileHandle){
        [_fileHandle closeFile];
        [_fileHandle release];
        _fileHandle = nil;
    }
    if (_debugLogFile)
    {
        close(_debugLogFile);
        _debugLogFile = 0;
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc removeObserver:self];
    }
}

- (void) setZoom:(float)scale
{
    Director::getInstance()->getOpenGLView()->setFrameZoomFactor(scale);
    _project.setFrameScale(scale);
}

//-(void) setAlwaysOnTop:(BOOL)alwaysOnTop
//{
//    NSMenuItem *windowMenu = [[window menu] itemWithTitle:@"Window"];
//    NSMenuItem *menuItem = [[windowMenu submenu] itemWithTitle:@"Always On Top"];
//    if (alwaysOnTop)
//    {
//        [window setLevel:NSFloatingWindowLevel];
//        [menuItem setState:NSOnState];
//    }
//    else
//    {
//        [window setLevel:NSNormalWindowLevel];
//        [menuItem setState:NSOffState];
//    }
//    _isAlwaysOnTop = alwaysOnTop;
//}

- (void) buildAndroidInBackground:(NSString *) scriptAbsPath
{
    _buildTask = [[NSTask alloc] init];
    [_buildTask setLaunchPath: [NSString stringWithUTF8String:scriptAbsPath.UTF8String]];

    [_buildTask setArguments: [NSArray array]];

    [_buildTask launch];

    [_buildTask waitUntilExit];

    int exitCode = [_buildTask terminationStatus];
    [_buildTask release];
    _buildTask = nil;

    [self performSelectorOnMainThread:@selector(updateAlertUI:) withObject:@(exitCode) waitUntilDone:YES];
}
//
//- (void) updateAlertUI:(NSString*) errCodeString
//{
//    if (!buildAlert) return;
//
//    int errCode = [errCodeString intValue];
//    NSString *message = (errCode == 0) ? @"Build finished, Congraturations!" : @"OPPS, please check your code or build env";
//    BOOL hide = (errCode == 0) ? YES : NO;
//
//    [buildAlert setMessageText:message];
//    [[[buildAlert buttons] objectAtIndex:0] setTitle:@"Finish"];
//    [[[buildAlert buttons] objectAtIndex:1] setHidden:hide];
//}


#pragma mark -
#pragma mark IB Actions

- (IBAction) onFileNewPlayer:(id)sender
{
    NSMutableArray *args = [self makeCommandLineArgsFromProjectConfig];
    [args removeLastObject];
    [args removeLastObject];
    [self launch:args];
}

//- (IBAction) onPlayerWriteDebugLogToFile:(id)sender
//{
//    bool isWrite = _project.isWriteDebugLogToFile();
//    if (!isWrite)
//    {
//        if ([self writeDebugLogToFile:_project.get_debugLogFilePath()])
//        {
//            _project.setWriteDebugLogToFile(true);
//            [(NSMenuItem*)sender setState:NSOnState];
//        }
//    }
//    else
//    {
//        _project.setWriteDebugLogToFile(false);
//        [self close_debugLogFile];
//        [(NSMenuItem*)sender setState:NSOffState];
//    }
//}
//
//- (IBAction) onPlayerOpenDebugLog:(id)sender
//{
//    const string path = _project.get_debugLogFilePath();
//    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding]];
//}
//
//- (IBAction) onPlayerRelaunch:(id)sender
//{
//    [self relaunch];
//}
//
//- (IBAction) onPlayerShowProjectSandbox:(id)sender
//{
//    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:FileUtils::sharedFileUtils()->getWritablePath().c_str() encoding:NSUTF8StringEncoding]];
//}
//
//- (IBAction) onPlayerShowProjectFiles:(id)sender
//{
//    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:_project.getProjectDir().c_str() encoding:NSUTF8StringEncoding]];
//}
//
//- (IBAction) onScreenChangeFrameSize:(id)sender
//{
//    NSInteger i = [sender tag];
//    if (i >= 0 && i < SimulatorConfig::getInstance()->getScreenSizeCount())
//    {
//        SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize((int)i);
//        _project.setFrameSize(_project.isLandscapeFrame() ? cocos2d::Size(size.height, size.width) : cocos2d::Size(size.width, size.height));
//        _project.setFrameScale(1.0f);
//        [self relaunch];
//    }
//}
//
//- (IBAction) onScreenPortait:(id)sender
//{
//    if ([sender state] == NSOnState) return;
//    [sender setState:NSOnState];
//    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Landscape"] setState:NSOffState];
//    _project.changeFrameOrientationToPortait();
//    [self relaunch];
//}
//
//- (IBAction) onScreenLandscape:(id)sender
//{
//    if ([sender state] == NSOnState) return;
//    [sender setState:NSOnState];
//    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Portait"] setState:NSOffState];
//    _project.changeFrameOrientationToLandscape();
//    [self relaunch];
//}
//
//- (IBAction) onScreenZoomOut:(id)sender
//{
//    if ([sender state] == NSOnState) return;
//    float scale = (float)[sender tag] / 100.0f;
//    [self setZoom:scale];
//    [self updateView];
//    [self updateUI];
//    [self updateOpenRect];
//
//}
//
//- (void) updateView
//{
//    auto policy = eglView->getResolutionPolicy();
//    auto designSize = eglView->getDesignResolutionSize();
//
//    cocos2d::Size frameSize = _project.getFrameSize();
//    eglView->setFrameSize(frameSize.width, frameSize.height);
//
//    eglView->setDesignResolutionSize(designSize.width, designSize.height, policy);
//}
//
//-(IBAction) onWindowAlwaysOnTop:(id)sender
//{
//    [self setAlwaysOnTop:!_isAlwaysOnTop];
//}
//
//-(IBAction)fileBuildAndroid:(id)sender
//{
//    if (!_isBuildingFinished) return;
//
//    if (_project.isWelcome())
//    {
//        [self showAlert:@"Welcome app is not for android" withTitle:@""];
//    }
//    else
//    {
//        std::string scriptPath = _project.getProjectDir() + "proj.android/build_native.sh";
//        if (!FileUtils::getInstance()->isFileExist(scriptPath))
//        {
//            [self showAlert:[NSString stringWithFormat:@"%s isn't exist", scriptPath.c_str()] withTitle:@""];
//        }
//        else
//        {
//            _isBuildingFinished = NO;
//            NSString *tmpPath = [NSString stringWithUTF8String:scriptPath.c_str()];
//
//            [self performSelectorInBackground:@selector(buildAndroidInBackground:)
//                                   withObject:tmpPath];
//
//
//
//            NSAlert *alert = [[[NSAlert alloc] init] autorelease];
//            [alert addButtonWithTitle:@"Cancel"];
//            [[alert addButtonWithTitle:@"How to setup android ENV"] setHidden:YES];
//            [alert setMessageText:@"Building android target, view console :-)"];
//            [alert setAlertStyle:NSWarningAlertStyle];
//
//            buildAlert = alert;
//            [alert beginSheetModalForWindow:window
//                          completionHandler:^(NSModalResponse returnCode) {
//
//                              _isBuildingFinished = YES;
//                              if (returnCode == NSAlertFirstButtonReturn)
//                              {
//                                  if (_buildTask && [_buildTask isRunning])
//                                  {
//                                      [NSObject cancelPreviousPerformRequestsWithTarget:self];
//                                      [_buildTask interrupt];
//                                  }
//                              }
//                              else if (returnCode == NSAlertSecondButtonReturn)
//                              {
//                                  Native::openURL("http://quick.cocos.org/?p=415");
//                              }
//                          }];
//        }
//    }
//}
//
//- (BOOL)validateUserInterfaceItem:(id<NSValidatedUserInterfaceItem>)anItem
//{
//    return (_isBuildingFinished);
//}
//
//- (IBAction) fileBuildIOS:(id)sender
//{
//    if (_project.isWelcome())
//    {
//        [self showAlert:@"Welcome app " withTitle:@""];
//    }
//    else
//    {
//        [self showAlert:@"Coming soon :-)" withTitle:@""];
//    }
//}

@end
