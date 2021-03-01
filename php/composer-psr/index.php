<?php
header('Content-type: text/plain');
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

require 'vendor/autoload.php';

echo "
├───inni
│   └───Auto
│   │   └───Bmw.php
│   └───Riku.php
├───srcc
│   └───Spacebar
│   │   └───Bar.php
│   └───Spacebar.php <<----------
├───vendor
│   └───autoload.php
├───composer.json
└───index.php
";

$test = new \Srcc\Spacebar;
echo "\nResult: " . $test->kissa();
echo "\n------------------------------------------------------\n";

echo "
├───inni
│   └───Auto
│   │   └───Bmw.php
│   └───Riku.php
├───srcc
│   └───Spacebar
│   │   └───Bar.php <<----------
│   └───Spacebar.php
├───vendor
│   └───autoload.php
├───composer.json
└───index.php
";

$bar = new \Srcc\Spacebar\Bar;
echo "\nResult: " . $bar->koira();
echo "\n------------------------------------------------------\n";

echo "
├───inni
│   └───Auto
│   │   └───Bmw.php
│   └───Riku.php <<----------
├───srcc
│   └───Spacebar
│   │   └───Bar.php
│   └───Spacebar.php
├───vendor
│   └───autoload.php
├───composer.json
└───index.php
";

$riku = new \Inni\Riku;
echo "\nResult: " . $riku->mina();
echo "\n------------------------------------------------------\n";

echo "
├───inni
│   └───Auto
│   │   └───Bmw.php <<----------
│   └───Riku.php
├───srcc
│   └───Spacebar
│   │   └───Bar.php
│   └───Spacebar.php
├───vendor
│   └───autoload.php
├───composer.json
└───index.php
";

$bmw = new \Inni\Auto\Bmw;
echo "\nResult: " . $bmw->kolina();
echo "\n------------------------------------------------------\n";

echo "\nEND";
