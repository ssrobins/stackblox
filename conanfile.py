from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#b185e9d8c14eef5fcbce6e9fb0468c944149a4c5")
        self.build_requires("cmake_utils/0.3.1#cc144db607f04d12c0b18303a7c7d37386ce0783")

    def requirements(self):
        self.requires("gtest/1.10.0#30c3a8ee7b1c80b95c376542109b72102c191bcd")
        self.requires("ssrobins_engine/0.2.0#fc3b0de476823df5833e6c727aacf8823e23dfb3")
