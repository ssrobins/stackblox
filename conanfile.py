from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#080a2227eb3904d6c6df6bd90ff689d1cf12736e")
        self.build_requires("cmake_utils/0.3.1#cc144db607f04d12c0b18303a7c7d37386ce0783")

    def requirements(self):
        self.requires("gtest/1.10.0#7c3aed2f3f8f76d9bf994bcf17364ef0fa583452")
        self.requires("ssrobins_engine/0.2.0#fd695351c1088d7961446f5f13bf7008e3436664")
