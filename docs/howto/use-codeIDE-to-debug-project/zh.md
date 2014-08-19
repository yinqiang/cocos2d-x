如何使用codeIDE调试quick工程
===

##创建工程
- 你可以使用player创建一个新工程，也可以使用命令行创建
- Quick V3 beta之后的版本创建的工程自动支持codeIDE，你无需另外做处理；如果你创建工程时使用的quick版本不够高，你可以用最新版本重新创建一个工程后，将原来的代码移到新的工程中使用
- 在创建工程时，指定好适当的屏幕模式(横屏或者竖屏)，可以避免以后再作修改
- codeIDE的新版本将会支持quick工程的创建

##在codeIDE中导入已创建的quick工程
- 和导入普通cocos工程没有区别
- 在codeIDE中从菜单开始依次选择“File”-“Import”-“Cocos”-“Import Cocos Project”-“Next”
- 点“Browse...”，选择要导入的工程所在目录，点“Open”按钮返回
- 窗口中已经列出你工程目录下的文件，点“Next”继续
- 新窗口中点击“Finish”，等待导入完成

##为工程设置调试配置参数
- 在codeIDE界面里，左边栏里点鼠标右键，在弹出菜单中选择“Debug As”-“Debug Configurations”，或者直接点击上方的“Debug Configurations”按钮，打开设置界面
- 在设置界面中，左边栏“Cocos Luabinding”目录下，选中要修改的配置项。如果是为新导入的工程进行配置，最好新建一个配置项
- Name: 这里可以修改你的配置项的名称
- Project：这里选择配置项关联的工程，请点击“Browse...”正确选择你想要调试的工程
- Taget Platform：选择调试平台。quick工程请选择“Remote Debug”，并在其下的Platform选项中选择Mac或者Windows，两个IP选项均选择“127.0.0.1”
- 配置后如下图。
[](res/Debug_config.png)
- 点“Apply”以保存设置，点“Close”关闭设置窗口