from conan import ConanFile

required_conan_version = ">=2.0.0-beta1"

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def requirements(self):
        if self.settings.os == "Android":
            self.requires("android_sdl/2.6.2@ssrobins")
        self.requires("cmake_utils/10.0.1@ssrobins")
        self.requires("gtest/1.12.0@ssrobins")
        self.requires("ssrobins_engine/1.2.0@ssrobins")
