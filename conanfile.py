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
        self.requires("gtest/1.10.0#ae1e2f340425ed810e712141a73d8dc7652b64d9")
        self.requires("ssrobins_engine/0.2.0#c017a745b5d97d736cedabf6531f04c2743fbca0")
