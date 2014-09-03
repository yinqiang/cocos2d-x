<?php

ini_set('memory_limit','256M');
require_once(__DIR__ . '/quick/ApkBuilder.php');

// ----

$config = array();

$config['api_ver'] = '19';

$builder = new ApkBuilder($config);

$retval = $builder->run();

echo "build return value: $retval\n";
return($retval);