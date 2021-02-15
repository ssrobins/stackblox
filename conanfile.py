from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#ed934365b888c490f9dca54779d85a6e3cc3cc52")
        self.build_requires("cmake_utils/0.3.1#e474aafdec36cf92d97e781b844f390f3170f29f")

    def requirements(self):
        self.requires("gtest/1.10.0#f11a61df1ef0e30586c1ac7ca39110dba29b2bd7")
        self.requires("ssrobins_engine/0.3.0#a91a3d260dbb7c77f8fc11a68159e2ed85b36dff")
