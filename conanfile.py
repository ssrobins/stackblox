from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def requirements(self):
        if self.settings.os == "Android":
            self.requires("android_sdl/2.6.2#94f9b35ee28227c1985125702817819f15e76186")
        self.requires("cmake_utils/10.0.1#94f9b35ee28227c1985125702817819f15e76186")
        self.requires("gtest/1.11.0#94f9b35ee28227c1985125702817819f15e76186")
        self.requires("ssrobins_engine/1.2.0#94f9b35ee28227c1985125702817819f15e76186")
