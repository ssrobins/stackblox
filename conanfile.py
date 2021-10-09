from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#b276f95f39b2d5afe404751198b15c400938844d")
        self.build_requires("cmake_utils/0.3.1#a1d53d179d9736ff032b5f5de3e4c3e2eebcb1f0")

    def requirements(self):
        self.requires("gtest/1.11.0#da27a76e3c6d8034aee23541c0c4e9720f224ecc")
        self.requires("ssrobins_engine/0.3.0#8f04c86eafae2ff0e33063296233d79e48c9a701")
