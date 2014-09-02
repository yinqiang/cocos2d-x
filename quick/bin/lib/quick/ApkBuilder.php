<?php

require_once(__DIR__ . '/init.php');

class ApkBuilder
{
    const BUILD_NATIVE_SH = './build_native.sh';
    const BUILD_NATIVE_BAT = 'build_native.bat';

    private $quick_root;
    private $sdk_root;
    private $build_tools_path;
    private $tools_aapt;
    private $tools_dx;
    private $ndk_root;

    function __construct()
    {
        // $this->config = $config;
        // $this->options = $options;
    }

    function exec_sys_cmd($cmd_str)
    {
        echo "exec: $cmd_str\n";
        system($cmd_str, $retval);
        echo "*******************\n";

        return $retval;
    }

    function checkToolsRootPath()
    {
        $this->quick_root = $_ENV["QUICK_V3_ROOT"];
        if (!$this->quick_root)
        {
            print("\nError: Path QUICK_V3_ROOT not found!\n\n");
            return(false);
        }

        $this->sdk_root = $_ENV["ANDROID_SDK_ROOT"];
        if (!$this->sdk_root)
        {
            print("\nError: Path ANDROID_SDK_ROOT not found!\n\n");
            return(false);
        }
        $this->build_tools_path = $this->sdk_root . '/build-tools';
        if (!is_dir($this->build_tools_path))
        {
            print("\nError: Path $this->build_tools_path not found!\n\n");
            return(false);
        }
        $android_ver_str = 'android-4.4.2';
        $this->build_tools_path = $this->build_tools_path . '/' . $android_ver_str;
        if (!is_dir($this->build_tools_path))
        {
            print("\nError: Path $this->build_tools_path not found!\n\n");
            return(false);
        }
        $this->tools_aapt = $this->build_tools_path . '/aapt';

        $this->ndk_root = $_ENV["ANDROID_NDK_ROOT"];
        if (!$this->ndk_root)
        {
            print("\nError: Path ANDROID_NDK_ROOT not found!\n\n");
            return(false);
        }

        return true;
    }

    function buildNative()
    {
        if (DS == '/')
        {
            $build_bin =  self::BUILD_NATIVE_SH;
        }
        else
        {
            $build_bin =  self::BUILD_NATIVE_BAT;
        }

        $retval = $this->exec_sys_cmd($build_bin);

        return $retval;
    }

    function appt_res()
    {
        if (!is_dir('gen'))
        {
            mkdir('gen');
        }

        $cmd_str = $this->tools_aapt . ' package -f -m -J ./gen -S res -M AndroidManifest.xml ' . '-I ' . $this->sdk_root . '/platforms/android-19/android.jar';

        $retval = $this->exec_sys_cmd($cmd_str);

        return $retval;
    }

    function compile_java()
    {
        if (!is_dir('bin'))
        {
            mkdir('bin');
        }

        if (!is_dir('bin/classes'))
        {
            mkdir('bin/classes');
        }

        $files = array();
        findFiles('src', $files);

        $cmd_str = 'javac -encoding utf8 -target 1.5 -bootclasspath ~/android/android-sdk-macosx/platforms/android-19/android.jar -classpath ~/quick-x-3/cocos/platform/android/java/bin/libcocos2dx.jar:./protocols/android/libPluginProtocol.jar -d bin/classes ';
        foreach ($files as $file)
        {
            $retval = $this->exec_sys_cmd($cmd_str . $file);
            if ($retval!=0)
            {
                print("error in $file\n");
                return $retval;
            }
        }

        return $retval;
    }

    function run()
    {
        $retval = 0;

        if (!$this->checkToolsRootPath())
        {
            return(-1);
        }

        $retval = $this->buildNative();
        if ($retval!=0)
        {
            print("\nError: Build native lib failed!\n\n");
            return($retval);
        }

        $retval = $this->appt_res();
        if ($retval!=0)
        {
            print("\nError: Build resources failed!\n\n");
            return($retval);
        }

        $retval = $this->compile_java();
        if ($retval!=0)
        {
            print("Error: javac error!!\n");
            return($retval);
        }

        return($retval);
    }

}
