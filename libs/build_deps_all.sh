#!/bin/bash
set -e

cd libs

# 参数
if [ -z $cmake ]; then
  cmake="cmake"
fi
if [ -z $deps ]; then
  deps="deps"
fi

# libs/deps/...
mkdir -p $deps
cd $deps
if [ -z $NKR_PACKAGE ]; then
  INSTALL_PREFIX=$PWD/built
else
  INSTALL_PREFIX=$PWD/package
fi
rm -rf $INSTALL_PREFIX
mkdir -p $INSTALL_PREFIX

#### clean ####
clean() {
  rm -rf dl.zip yaml-* zxing-* protobuf
}

#### ZXing ####
curl -L -o dl.zip https://codeload.github.com/zxing-cpp/zxing-cpp/zip/refs/heads/master
unzip dl.zip

cd zxing-*
mkdir -p build
cd build

$cmake .. -GNinja -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF -DBUILD_BLACKBOX_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
ninja && ninja install

cd ../..

#### yaml-cpp ####
curl -L -o dl.zip https://codeload.github.com/jbeder/yaml-cpp/zip/refs/heads/master
unzip dl.zip

cd yaml-*
mkdir -p build
cd build

$cmake .. -GNinja -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
ninja && ninja install

cd ../..

#### protobuf ####
git clone --recurse-submodules -b v28.2 --depth 1 --shallow-submodules https://github.com/protocolbuffers/protobuf

#备注：交叉编译要在 host 也安装 protobuf 并且版本一致,编译安装，同参数，安装到 /usr/local

mkdir -p protobuf/build
cd protobuf/build

$cmake .. -GNinja \
  -DCMAKE_CXX_STANDARD=23 \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -Dprotobuf_MSVC_STATIC_RUNTIME=OFF \
  -Dprotobuf_BUILD_TESTS=OFF \
  -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX
ninja && ninja install

cd ../..

####
clean
