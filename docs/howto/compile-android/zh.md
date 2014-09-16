Title: 编译 Android 工程

编译 Android 工程
================

要编译 Android 功能，必须使用最新版本的 Android SDK 和`指定的 r9d 版本` Android NDK。

~

## 安装 Android SDK 和 NDK

不管是 Mac 还是 Windows 环境，都需要从 [http://developer.android.com/sdk/](http://developer.android.com/sdk/) 下载最新版本的 ADT Bundle。

下载解压缩以后，运行 `sdk/tools` 目录中的 `android` 工具，对 SDK 进行更新。

> 由于网络问题，大家需要代理才能完成更新操作。

由于 cocos2d-x 还不支持最新的 NDK r10，所以我们需要从网络上搜索 NDK r9d 用于编译。

> SDK 和 NDK 不能放在包含中文和空格的目录中。
> Windows 下，SDK/NDK 必须和 quick 的文件放在同一个分区中。

在完成 SDK 和 NDK 的下载安装后，我们需要做一些环境配置工作：

-   Mac 下修改 .profile 文件：

    启动 终端 应用程序, 运行命令:

    ~~~
    $ if [ -f ~/.profile ]; then open -e ~/.profile; fi
    ~~~

    如果没看到文本编辑窗口出现，则运行以下命令：

    ~~~
    $ if [ -f ~/.bash_profile ]; then open -e ~/.bash_profile; fi
    ~~~

    添加以下代码：

    ~~~
    export ANDROID_NDK_ROOT=NDK绝对路径
    export ANDROID_SDK_ROOT=SDK绝对路径
    export ANDROID_HOME=${ANDROID_SDK_ROOT}
    ~~~

    例如：

    ~~~
    export ANDROID_NDK_ROOT=/Users/dualface/android-ndk-r9d
    export ANDROID_SDK_ROOT=/Users/dualface/android-sdk
    export ANDROID_HOME=${ANDROID_SDK_ROOT}
    ~~~

-   Windows 下在系统设置里添加以下环境变量：

    ~~~
    ANDROID_NDK_ROOT=NDK绝对路径
    ANDROID_SDK_ROOT=SDK绝对路径
    ANDROID_HOME=%ANDROID_SDK_ROOT%
    ~~~

    例如：

    ~~~
    ANDROID_NDK_ROOT=C:\Work\android-ndk-r9d
    ANDROID_SDK_ROOT=C:\Work\android-sdk
    ANDROID_HOME=%ANDROID_SDK_ROOT%
    ~~~

~

## 编译 samples/anysdk

quick 中带有一个 AnySDK 的示例，我们可以编译这个示例来检查准备工作是否就绪：

> AnySDK 是一个极为方便的工具，可以大大减低接入 SDK 的工作量。
> 
> 详情请访问：[http://www.anysdk.com/](http://www.anysdk.com/)
> 
> AnySDK 为 CP 商提供一套第三方SDK接入解决方案，整个接入过程，不改变任何 SDK 的功能、特性、参数等，对于最终玩家而言是完全透明无感知的。目的是让 CP 商能有更多时间更专注于游戏本身的品质，所有 SDK 的接入工作统统交给我们吧。第三方 SDK 包括了渠道 SDK、用户系统、支付系统、广告系统、统计系统、分享系统等等。我们不开 SDK，我们只帮您轻松接入第三方 SDK！

1.  打开终端窗口，进入 `quick/samples/anysdk/proj.android` 目录
2.  如果是 Mac 系统，运行 `./build_native.sh`，Windows 系统则运行 `build_native.bat`
3.  如果一切顺利，我们将看到输出信息的最后几行：

    ~~~
    SharedLibrary  : libgame.so
    Install        : libgame.so => libs/armeabi/libgame.so
    ~~~

~

如果编译失败，请仔细检查 SDK/NDK 版本、安装路径。

> 修改了环境设置后，必须重新打开终端窗口才能生效。

~

运行 `build_native` 只是编译了 C++ 部分，而 Android 应用还存在 Java 部分，这时就需要 Eclipse ADT 来进行了。

### 将项目导入 Eclipse ADT

在先前下载的 `ADT Bundle` 中，已经包含了 Eclipse ADT 工具。只需要从 `eclipse` 目录中启动即可。下面的截图是 Mac 系统，但 Windows 系统中的操作完全一致。

启动后，需要先导入 cocos2d-x 的 Java 库：

1.  选择菜单 File -> Import, 再选择 Android -> Existing Android Code Into Workspace
2.  点击 Browse 按钮, 选择 quick 目录中的 `cocos/platform/android/java`
3.  点击 "Finish" 完成操作。

接下来导入 AnySDK 示例的 Android 工程：

1.  重复上述步骤，导入 `quick/samples/anysdk/proj.android`
2.  在 `AnySDK` 工程上点击右键选择菜单 "Properties" 打开工程设置对话框
3.  从左侧选择 `Android`，然后点击右侧 "Add" 按钮，添加 `v3quick` 库。如果添加之前 `v3quick` 库已经在 `Library` 列表中，则删除后重新添加
4.  检查 `Project Build Target` 是否是最新版本的 SDK

    ![](res/check-project-properties.png)

~

如果完成上述操作后，Eclipse ADT 窗口 `Package Explorer` 列出的 `v3quick` 和 `AnySDK` 项目文件夹上有红色错误图标。请仔细检查 `v3quick` 和 `AnySDK` 项目的操作步骤，以及 `Project Build Target` 是否是最新版本的 SDK。

~

### 设置 Android 设备允许真机调试 ###

Android 官方文档：http://developer.android.com/tools/device.html

1.  Enable USB debugging on your device.

	-   On most devices running Android 3.2 or older, you can find the option under Settings > Applications > Development.
	-   On Android 4.0 and newer, it’s in Settings > Developer options.

    	Note: On Android 4.2 and newer, Developer options is hidden by default. To make it available, go to Settings > About phone and tap Build number seven times. Return to the previous screen to find Developer options.
	
    -   在系统设置中找到“开发者选项”，打开“USB调试”。Android 4.2 开始，`开发者选项`默认是隐藏的，需要打开`设置->关于`界面，然后在`Build Number`上点击七次才能打开`开发者选项`。

2.  Set up your system to detect your device.

	-   If you’re developing on Windows, you need to install a USB driver for adb. For an installation guide and links to OEM drivers, see the OEM USB Drivers document.

    -   根据不同的机型，也许需要安装该机型特定的 USB 驱动程序。例如 Moto 就必须安装 Moto 的 USB 驱动。

3.  Connect your device.
    
    完成设置后，将设备连接到开发机，并解锁设备。

~

### 在设备上测试 AnySDK 示例 ###

1.  在 Eclipse ADT 里选择菜单 Window -> Show View -> Other…, 再选择 Android -> Devices

2.  如果设备设置完成，那么在 Devices 标签页中就可以看到你的设备

3.  在 `AnySDK` 项目上点击鼠标右键, 选择菜单 Debug As -> Android Application. 如果一切正常，等一会儿就可以在设备上看到运行画面了：

    ![](res/run-on-device.png)

