#!/bin/bash
set -e

source libs/env_deploy.sh
DEST=$DEPLOYMENT/windows-amd64
rm -rf $DEST
mkdir -p $DEST

#### copy exe ####
cp $BUILD/nekoray.exe $DEST

cd download-artifact
cd *windows-amd64
tar xvzf artifacts.tgz -C ../../
cd ..
cd *public_res
tar xvzf artifacts.tgz -C ../../
cd ../..

mv $DEPLOYMENT/public_res/* $DEST
rmdir $DEPLOYMENT/public_res

#### deploy qt & DLL runtime ####
pushd $DEST
windeployqt nekoray.exe --no-translations --no-system-d3d-compiler --no-compiler-runtime --no-opengl-sw --verbose 2
popd

rm -rf $DEST/dxcompiler.dll $DEST/dxil.dll