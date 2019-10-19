set -e
  
build_dir=build_mac

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

conan remote add bintray-stever https://api.bintray.com/conan/stever/conan --insert --force

conan install --update .. -s compiler.version=11.0

config=Release

cmake -G Xcode ..

cmake --build . --config $config

ctest -C $config --output-on-failure

cpack -C $config
