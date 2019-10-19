set -e
  
build_dir=build_linux

cd $(dirname "$0")
mkdir -p $build_dir
cd $build_dir

conan remote add bintray-stever https://api.bintray.com/conan/stever/conan --insert --force

conan install --update .. -s compiler.libcxx=libstdc++11

config=Release

cmake -G Ninja -DCMAKE_BUILD_TYPE=$config ..

cmake --build .

ctest -C $config --output-on-failure

cpack -C $config
