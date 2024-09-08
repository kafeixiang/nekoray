#!/bin/bash
set -e

source libs/env_deploy.sh
[ "$GOOS" == "windows7" ] && [ "$GOARCH" == "amd64" ] && DEST=$DEPLOYMENT/windows7 || true
[ "$GOOS" == "windows" ] && [ "$GOARCH" == "amd64" ] && DEST=$DEPLOYMENT/windows-amd64 || true
[ "$GOOS" == "windows" ] && [ "$GOARCH" == "arm64" ] && DEST=$DEPLOYMENT/windows-arm64 || true
[ "$GOOS" == "linux" ] && [ "$GOARCH" == "amd64" ] && DEST=$DEPLOYMENT/linux-amd64 || true
[ "$GOOS" == "linux" ] && [ "$GOARCH" == "arm64" ] && DEST=$DEPLOYMENT/linux-arm64 || true
[ "$GOOS" == "darwin" ] && [ "$GOARCH" == "amd64" ] && DEST=$DEPLOYMENT/macos-amd64 || true
[ "$GOOS" == "darwin" ] && [ "$GOARCH" == "arm64" ] && DEST=$DEPLOYMENT/macos-arm64 || true
if [ $GOOS = "windows7" ]; then
  GOOS=windows
  OLD=y
fi

if [ -z $DEST ]; then
  echo "Please set GOOS GOARCH"
  exit 1
fi
rm -rf $DEST
mkdir -p $DEST

export CGO_ENABLED=0

#### Go: updater ####
# pushd go/cmd/updater
# [ "$GOOS" == "darwin" ] || go build -o $DEST -trimpath -ldflags "-w -s"
# [ "$GOOS" == "linux" ] && mv $DEST/updater $DEST/launcher || true
# popd

#### Go: nekobox_core ####
pushd CORE/cmd/sing-box
COMMIT_HASH=$(git rev-parse --short HEAD)
if [ -z $OLD ]; then
  go build -v -trimpath -ldflags "-w -s -X 'github.com/sagernet/sing-box/constant.Version=$COMMIT_HASH'" -tags "with_clash_api,with_gvisor,with_quic,with_wireguard,with_utls,with_ech,with_dhcp,with_shadowsocksr"
else
  go build -v -trimpath -ldflags "-w -s -X 'github.com/sagernet/sing-box/constant.Version=$COMMIT_HASH'" -tags "with_clash_api,with_gvisor,with_quic,with_wireguard,with_utls,with_dhcp,with_shadowsocksr"
fi

if [ -f "sing-box.exe" ]; then
  mv sing-box.exe $DEST/nekobox_core.exe
elif [ -f "sing-box" ]; then
  mv sing-box $DEST/nekobox_core
fi
popd