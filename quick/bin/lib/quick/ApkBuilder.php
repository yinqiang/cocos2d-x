<?php

require_once(__DIR__ . '/init.php');

$android_api_ver_map = array(
    '8' => '2.2', 
    '18' => '4.3', 
    '19' => '4.4.2', 
    );

class ApkBuilder
{
    const BUILD_NATIVE_SH = './build_native.sh';
    const BUILD_NATIVE_BAT = 'build_native.bat';

    private $config;

    private $quick_root;

    private $sdk_root;
    private $build_tools_path;
    private $tools_aapt;
    private $tools_dx;
    private $platform_path;
    private $boot_class_path;
    private $class_path;

    private $ndk_root;

    function __construct($config)
    {
        $this->config = $config;
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
        $this->platform_path = $this->sdk_root . '/platforms/android-' . $this->config['api_ver'];
        $this->boot_class_path = $this->platform_path . '/android.jar';
        if (!file_exists($this->boot_class_path))
        {
            print("\nError: $this->boot_class_path not found!\n\n");
            return(false);
        }
        $this->class_path = $this->quick_root . '/cocos/platform/android/java/bin/libcocos2dx.jar';
        if (!file_exists($this->class_path))
        {
            print("\nError: $this->class_path not found!\n\n");
            return(false);
        }
        if ($this->config['classpath']) {
            $this->class_path = $this->class_path . ':' . $this->config['classpath'];
        }

        $this->build_tools_path = $this->sdk_root . '/build-tools';
        if (!is_dir($this->build_tools_path))
        {
            print("\nError: Path $this->build_tools_path not found!\n\n");
            return(false);
        }
        global $android_api_ver_map;
        $android_ver_str = 'android-' . $android_api_ver_map[$this->config['api_ver']];
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

        $cmd_str = $this->tools_aapt 
            . ' package -f -m -J ./gen -S res -M AndroidManifest.xml ' . '-I ' . $this->boot_class_path;

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

        $cmd_str = 'javac -encoding utf8 -target 1.5 -bootclasspath ' 
            . $this->boot_class_path 
            . ' -classpath ' . $this->class_path . ' -d bin/classes ';
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

    function make_dex()
    {
        $cmd_str = $this->build_tools_path . '/dx'
            . ' --dex --output=./bin/classes.dex ./bin/classes';

        $retval = $this->exec_sys_cmd($cmd_str);

        return $retval;
    }

    function make_resources()
    {
        $cmd_str = $this->tools_aapt 
            . ' package -f -S res -A assets -M AndroidManifest.xml' . ' -I ' . $this->boot_class_path
            . ' -F bin/resources.ap_';

        $retval = $this->exec_sys_cmd($cmd_str);

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

        $retval = $this->make_dex();
        if ($retval!=0)
        {
            print("Error: make bin/classes.dex error!!\n");
            return($retval);
        }

        $retval = $this->make_resources();
        if ($retval!=0)
        {
            print("Error: make bin/resources.ap_ error!!\n");
            return($retval);
        }

        return($retval);
    }

}
