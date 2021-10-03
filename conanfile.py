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
        self.requires("gtest/1.11.0#42289b3e08c69030c7f755a4d49d0b0b4d78103e")
        self.requires("ssrobins_engine/0.3.0#d7d920cc764dfe4a64a9e978e627a588d0c16cfa")
