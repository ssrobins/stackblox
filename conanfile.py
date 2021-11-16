from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/1.0.0#33a5929ed7796027107fb57187ae4248e0faf3ce")
        self.build_requires("cmake_utils/2.0.1#bc87acc9a67867fb20e22e3c51eb4c070a9f9758")

    def requirements(self):
        self.requires("gtest/1.11.0#8fd6a2a8d5711b4ddb33e9addc96ab35cdb9f538")
        self.requires("ssrobins_engine/1.0.0#d220df5c247a38aef42cd86471ffaef0aae4d726")
