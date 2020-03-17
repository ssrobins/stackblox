set -e
  
build_dir=build_linux

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

cmake -G "Ninja Multi-Config" ..

config=Release

cmake --build . --config $config --verbose

ctest -C $config --output-on-failure

cpack -C $config
