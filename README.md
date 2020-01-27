# Jumanpp-php

Jumanpp-php is a PHP bindings for Juman++.

[Juman++](https://github.com/ku-nlp/jumanpp) a Morphological Analyzer Toolkit.

## Requirements

PHP 7.3  
libjumanpp

```
$ curl -fSL "https://github.com/YujiroTakahashi/libjumanpp/archive/master.tar.gz" -o "./libjumanpp.tgz"
$ tar xf libjumanpp.tgz
$ cd libjumanpp-master
$ mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j $(nproc)
$ sudo make install
```

## Building jumanpp for PHP

```
$ cd jumanpp-php
$ phpize
$ ./configure
$ make -j $(nproc)
$ sudo make install
```

edit your php.ini and add:

```
extension=jumanpp.so
```

## Class synopsis

```php
Jumanpp {
    public __construct ( void )
    public array analyze ( string text )
    public string wakati ( string text )
}
```

## Table of Contents

[Jumanpp::__construct](#__construct)  
[Jumanpp::analyze](#analyze)  
[Jumanpp::wakati](#wakati)  

-----

### <a name="__construct">Jumanpp::__construct()

load a model.

```php
$ftext = new Jumanpp('/usr/local/libexec/jumanpp/jumandic.jppmdl');
```

-----

### <a name="analyze">array Jumanpp::analyze(string text)

get the analyzed.

```php
$analyzed = $jpp->analyze('魅力がたっぷりと詰まっている');
print_r($analyzed);
```
```
Array
(
    [0] => Array
        (
            [surface] => 魅力
            [reading] => みりょく
            [baseform] => 魅力
            [pos] => 名詞
            [subpos] => 普通名詞
            [conjType] => *
            [conjForm] => *
            [feat] => 代表表記: カテゴリ:抽象物
            [redirect] => 
            [posId] => 6
            [subposId] => 1
            [conjTypeId] => 0
            [conjFormId] => 0
            [featflag] => 0
        )

    [1] => Array
        (
            [surface] => が
            [reading] => が
            [baseform] => が
            [pos] => 助詞
            [subpos] => 格助詞
            [conjType] => *
            [conjForm] => *
            [feat] => *
            [redirect] => 
            [posId] => 9
            [subposId] => 1
            [conjTypeId] => 0
            [conjFormId] => 0
            [featflag] => 0
        )

    [2] => Array
        (
            [surface] => たっぷり
            [reading] => たっぷり
            [baseform] => たっぷりだ
            [pos] => 形容詞
            [subpos] => *
            [conjType] => ナノ形容詞
            [conjForm] => 語幹
            [feat] => 代表表記:
            [redirect] => 
            [posId] => 3
            [subposId] => 0
            [conjTypeId] => 22
            [conjFormId] => 1
            [featflag] => 0
        )

    [3] => Array
        (
            [surface] => と
            [reading] => と
            [baseform] => と
            [pos] => 助詞
            [subpos] => 格助詞
            [conjType] => *
            [conjForm] => *
            [feat] => *
            [redirect] => 
            [posId] => 9
            [subposId] => 1
            [conjTypeId] => 0
            [conjFormId] => 0
            [featflag] => 0
        )

    [4] => Array
        (
            [surface] => 詰まって
            [reading] => つまって
            [baseform] => 詰まる
            [pos] => 動詞
            [subpos] => *
            [conjType] => 子音動詞ラ行
            [conjForm] => タ系連用テ形
            [feat] => 代表表記: ドメイン:料理・食事 自他動詞:他:詰める/つめる
            [redirect] => 
            [posId] => 2
            [subposId] => 0
            [conjTypeId] => 10
            [conjFormId] => 14
            [featflag] => 0
        )

    [5] => Array
        (
            [surface] => いる
            [reading] => いる
            [baseform] => いる
            [pos] => 接尾辞
            [subpos] => 動詞性接尾辞
            [conjType] => 母音動詞
            [conjForm] => 基本形
            [feat] => 代表表記:
            [redirect] => 
            [posId] => 14
            [subposId] => 7
            [conjTypeId] => 1
            [conjFormId] => 2
            [featflag] => 0
        )

)
```
-----

### <a name="wakati">string Jumanpp::wakati()

get the wakati.

```php
echo $jpp->wakati('魅力がたっぷりと詰まっている');
```
```
魅力 が たっぷり と 詰まって いる
```
