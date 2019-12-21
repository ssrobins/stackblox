set -e

build_dir=build_android-v7a

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

config=Release

cmake -G Ninja -DANDROID_ABI=armeabi-v7a -DCMAKE_BUILD_TYPE=$config -DCMAKE_TOOLCHAIN_FILE=$ANDROID_HOME/android-ndk-${android_ndk_version}/build/cmake/android.toolchain.cmake ..

cmake --build . --verbose

cpack -C $config
