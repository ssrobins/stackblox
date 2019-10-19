set -e

build_dir=build_android-v8a

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

export android_min_sdk_version=21

conan remote add bintray-stever https://api.bintray.com/conan/stever/conan --insert --force

conan install --update .. -s os=Android -s os.api_level=$android_min_sdk_version -s arch=armv8 -s compiler=clang -s compiler.version=8 -s compiler.libcxx=libc++

config=Release

cmake -G Ninja -DANDROID_PLATFORM=android-$android_min_sdk_version -DANDROID_ABI=arm64-v8a -DANDROID_TOOLCHAIN=clang -DANDROID_STL=c++_static -DCMAKE_TOOLCHAIN_FILE=$ANDROID_HOME/android-ndk-${android_ndk_version}/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=$config ..

cmake --build .

cpack -C $config
