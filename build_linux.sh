set -e
  
build_dir=build_linux

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

config=Release

cmake -G Ninja -DCMAKE_BUILD_TYPE=$config ..

cmake --build . --verbose

ctest -C $config --output-on-failure

cpack -C $config
