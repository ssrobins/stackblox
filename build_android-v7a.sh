set -e

build_dir=build_android-v7a

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

cmake -G "Ninja Multi-Config" -DANDROID_ABI=armeabi-v7a -DCMAKE_TOOLCHAIN_FILE=$ANDROID_HOME/android-ndk-${android_ndk_version}/build/cmake/android.toolchain.cmake ..

config=Release

cmake --build . --config $config --verbose

cpack -C $config
