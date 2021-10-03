# Boost + Debian Bullseye 開発用 テンプレート

VSCode Dev Container 拡張を使用して
Debian GNU/Linux Bullseye (x86-64) をターゲットにした
Boost Library を使用するの開発環境を構築するための
テンプレート プロジェクト

## 環境

VSCode Dev Container 拡張
Docker for Windows (WSL2)

## 注意点

Boost のビルド作業が入るので, イメージ構築にやたらとCPUパワー喰います.

## 

ベースイメージ: debian:bullseye-slim

- /usr/local/lib 以下に ビルドされた boost ライブラリ群 + CMake用モジュール
- /usr/local/include 以下に boost ヘッダ群

を格納

詳細は .devcontainer/Dockerfile を参照

## CMakeLists.txt 雛型

FIND_PACKAGE(Boost ... の使い方はググってたもれ


```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT(boostexample 
  VERSION 2021.10.3
  LANGUAGES C CXX)

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(Threads REQUIRED)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.77.0 REQUIRED)

message("## Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message("## Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

ADD_SUBDIRECTORY(sample)
```
