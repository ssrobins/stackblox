set -e
  
build_dir=build_mac

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

config=Release

cmake -G Xcode ..

cmake --build . --config $config

ctest -C $config --output-on-failure

cpack -C $config
