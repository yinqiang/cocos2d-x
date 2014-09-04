<?php

ini_set('memory_limit','256M');
require_once(__DIR__ . '/quick/ApkBuilder.php');

$options = array(
    array('h',           'help',           0,      false,      'show help'),
    array('k',           'keystore',       1,      null,       'the keystore file'),
    array('kp',          'storepass',      1,      null,       'the keystore password'),
    array('ksa',         'storealias',     1,      null,       'the keystore alias'),
    array('api',         'api_ver',        1,      null,       'android api version'),
    array('classpath',   'classpath',      1,      null,       'extra android class path'),
);

function help()
{
    global $options;

    echo <<<EOT

usage: build_apk -classpath clspath ...

options:

EOT;

    for ($i = 0; $i < count($options); $i++)
    {
        $o = $options[$i];
        printf("    -%s %s\n", $o[0], $o[4]);
    }

    echo <<<EOT


examples:


EOT;

}

// ----

if ($argc > 0)
{
	$config = fetchCommandLineArguments($argv, $options);
}
else
{
	$config = array();
}

if ($config['help'])
{
    help();
    return(0);
}

if (!$config['api_ver'])
{
	$config['api_ver'] = '19';
}

$builder = new ApkBuilder($config);

$retval = $builder->run();

echo "build return value: $retval\n";
return($retval);