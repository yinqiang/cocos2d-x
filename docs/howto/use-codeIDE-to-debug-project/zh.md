如何使用codeIDE调试quick工程
===

##创建工程
- 你可以使用player创建一个新工程，也可以使用命令行创建
- Quick V3 beta之后的版本创建的工程自动支持codeIDE，你无需另外做处理；如果你创建工程时使用的quick版本不够高，你可以用最新版本重新创建一个工程后，将原来的代码移到新的工程中使用
- 在创建工程时，指定好适当的屏幕模式(横屏或者竖屏)，可以避免以后再作修改
- codeIDE的新版本将会支持quick工程的创建

##在codeIDE中导入已创建的quick工程
- 和导入普通cocos工程没有区别
- 在codeIDE中从菜单开始依次选择 File -> Import -> Cocos -> Import Cocos Project -> Next
- 点“Browse...”，选择要导入的工程所在目录，点“Open”按钮返回
- 窗口中已经列出你工程目录下的文件，点“Next”继续
- 新窗口中点击“Finish”，等待导入完成

##为工程设置调试配置参数
- 在codeIDE界面里，左边栏里点鼠标右键，在弹出菜单中选择 Debug As -> Debug Configurations ，或者直接点击上方的“Debug Configurations”按钮，打开设置界面
- 在设置界面中，左边栏“Cocos Luabinding”目录下，选中要修改的配置项。如果是为新导入的工程进行配置，最好新建一个配置项
- Name: 这里可以修改你的配置项的名称
- Project：这里选择配置项关联的工程，请点击“Browse...”正确选择你想要调试的工程
- Taget Platform：选择调试平台。quick工程请选择“Remote Debug”，并在其下的Platform选项中选择Mac或者Windows，两个IP选项均选择“127.0.0.1”
- 配置后如下图。
![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/use-codeIDE-to-debug-project/res/Debug_config.png)

- 点“Apply”以保存设置，点“Close”关闭设置窗口

##命令行启动runtime(仅调试lua代码)
- 启动runtime前，请确认quick V3已经正确安装，且quick V3平台目录下的player能正常运行；并确认已经按前面步骤设置好调试配置参数
- 启动命令行窗口，在命令行中进入要调试的工程目录
- 运行runtime-mac.sh，启动runtime
- 在codeIDE中，设置好Lua代码的断点，直接点击“Debug Remote”按钮即可开始调试

##通过player工程启动runtime(同时调试lua和c++代码)
- Mac下用xcode打开quick/player/proj.mac目录下的player工程；Windows下用vs2013打开quick/player/proj.win32目录下的player工程
- 配置player工程的启动参数为： （配置方法请参考后面的说明）
```
-debugger-codeide -workdir <工程目录路径>
```
- 如果需要竖屏启动，则配置参数为：
```
-debugger-codeide -workdir <工程目录路径> -portrait
```
- 设置完成，运行工程即可启动runtime
- 在codeIDE中，设置好Lua代码的断点，直接点击“Debug Remote”按钮即可开始调试

##在xcode中配置工程的启动参数的方法
- 用 Xcode 打开 mac 工程后，选择菜单 Product -> Scheme -> 你的项目名字
- 选择菜单 Product -> Scheme -> Edit Scheme，打开 Scheme 对话框
- 从对话框左侧选中 "Run"
- 从右侧选中 "Arguments"
- 在 Arguments Passed On Launch 里点 "+" 添加命令参数
- 示例如图
![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/use-codeIDE-to-debug-project/res/xcode_set_arguments.png)

##在VS中配置工程的启动参数的方法
- 用 Visual Studio 打开 win32 工程
- 确保从 Solution Explorer （解决方案管理器）中选中了你的项目
- 选择菜单 Project -> Properties，打开 Project Property 对话框
- 从对话框左侧选中 "Configuration Properties / Debugging"
- 从右侧选中 "Command Arguments"，添加命令参数内容
- 示例如图