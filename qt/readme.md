
mkdir qt; cd qt
git clone git://gitorious.org/qt/qtbase.git

export QTVER=qt5
export QTDIR=/home/saic/opt/static/$QTVER 
export PATH=$QTDIR/bin/:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib/:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=$QTDIR/lib/pkgconfig/:$PKG_CONFIG_PATH
export QT_PLUGIN_PATH=$QTDIR/lib/plugins/


./configure -confirm-license -opensource -debug -nomake examples -nomake tests  -make libs -prefix ${QTDIR} -no-xcb -static
make
sudo make install


ti omap:
https://gitorious.org/tigraphics/qtsupport


./configure -prefix /home/static/qt5 -debug -opengl es2 -xplatform linux-omap5-g++ -make libs  -opensource -confirm-license  -nomake examples -nomake tests -sysroot /home/saic/build/dra7xx-evm -no-pch --no-linuxfb -static


make -j4


export QTDIR=/home/saic/source/qt/5.5/Src/qtbase
export PKG_CONFIG_LIBDIR=/home/saic/source/qt/5.5/Src/qtbase/lib/pkgconfig:home/saic/build/dra7xx-evm/home/static/qt5/lib/pkgconfig

build qtwayland



export RPI_SYSROOT=/home/saic/build/dra7xx-evm/
export TOOLCHAIN=/home/saic/zxq/prebuilts/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux/arm-linux-gnueabihf
export QTDIR=/home/saic/source/qt/5.5/Src/qtbase
export PATH=$QTDIR/bin:$TOOLCHAIN/bin:$PATH
export PREFIX=/home/static/qt5
export PKG_CONFIG_PATH="$RPI_SYSROOT/usr/lib/pkgconfig:$RPI_SYSROOT/$PREFIX/lib/pkgconfig:$RPI_SYSROOT/$PREFIX/share/pkgconfig"
export PKG_CONFIG_SYSROOT_DIR="$RPI_SYSROOT"
export PKG_CONFIG_ALLOW_SYSTEM_LIBS=1
export PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1
export CPP=$TOOLCHAIN/bin/arm-linux-gnueabihf-cpp
export CC=$TOOLCHAIN/bin/arm-linux-gnueabihf-gcc
export CXX=$TOOLCHAIN/bin/arm-linux-gnueabihf-g++
export CFLAGS="--sysroot=$RPI_SYSROOT"
export CXXFLAGS="--sysroot=$RPI_SYSROOT"
export CPPFLAGS="--sysroot=$RPI_SYSROOT"
export LD=$TOOLCHAIN/bin/arm-linux-gnueabihf-ld
export LDFLAGS="--sysroot=$RPI_SYSROOT"
export AS=$TOOLCHAIN/bin/arm-linux-gnueabihf-as
export STRIP=$TOOLCHAIN/bin/arm-linux-gnueabihf-strip
export AR=$TOOLCHAIN/bin/arm-linux-gnueabihf-ar 



export QT_QPA_PLATFORM_PLUGIN_PATH=/home/qt5/plugins/platforms  
export QT_QPA_PLATFORM=wayland



