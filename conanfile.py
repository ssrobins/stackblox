from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#52d8b32fdd00c207564dd9c164cfdc902728f9c0")
        self.build_requires("cmake_utils/0.3.1#b92e3b563e31a4fe0e55849f3bfdb55eb7b06284")

    def requirements(self):
        self.requires("gtest/1.10.0#992f6addc84f632327426c11415a0b0647926c77")
        self.requires("ssrobins_engine/0.2.0#f0bb1dd7f2934821d3f81b770cad1afdd80f34ac")
