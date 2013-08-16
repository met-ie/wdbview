#!/bin/sh

set -e

APP=wdbview
# TODO: dynamically find version
VERSION=1.0.1
PACKAGE_VERSION=`echo $VERSION | sed s/\\..$//`
DEB_VERSION=$VERSION-1

ARCHITECTURE=`dpkg-architecture -qDEB_BUILD_ARCH`


BUILD_DIR=${APP}$VERSION
ORIG_FILE=${APP}_$VERSION.orig.tar.gz

rm -rf $BUILD_DIR

qmake
make all dist

DISTFILE=$BUILD_DIR.tar.gz

mv $DISTFILE $ORIG_FILE
tar xzf $ORIG_FILE
cp -r debian/ $BUILD_DIR

cd $BUILD_DIR

dpkg-buildpackage -us -uc

lintian ../${APP}-${PACKAGE_VERSION}_${DEB_VERSION}_$ARCHITECTURE.deb ../${APP}_$DEB_VERSION.dsc


cd ..
rm -r $BUILD_DIR
