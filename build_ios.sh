set -e

build_dir=build_ios

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

cmake -G Xcode -DCMAKE_SYSTEM_NAME=iOS ..

config=Release

cmake --build . --config $config

cpack -C $config-iphoneos
