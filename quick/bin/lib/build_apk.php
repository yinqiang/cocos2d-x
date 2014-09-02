<?php

ini_set('memory_limit','256M');
require_once(__DIR__ . '/quick/ApkBuilder.php');

// ----

$builder = new ApkBuilder();

$retval = $builder->run();

echo "build return value: $retval\n";
return($retval);