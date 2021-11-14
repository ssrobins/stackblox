from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/1.0.0#33a5929ed7796027107fb57187ae4248e0faf3ce")
        self.build_requires("cmake_utils/1.0.0#926ac6b58f4f500187b0a004491f5d0f7ebe0ed4")

    def requirements(self):
        self.requires("gtest/1.11.0#d87db002fb4324adf3f0a00fcf1e46b306d6271a")
        self.requires("ssrobins_engine/0.3.0#4a6aaeeaae1931812370a21c950d2eb6a004ae12")
