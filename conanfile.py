from conan import ConanFile

required_conan_version = ">=2.0.0-beta1"

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def build_requirements(self):
        self.test_requires("gtest/1.12.1@ssrobins")

    def requirements(self):
        if self.settings.os == "Android":
            self.requires("android_sdl/2.7.0@ssrobins")
        self.requires("cmake_utils/11.0.0@ssrobins")
        self.requires("ssrobins_engine/2.0.3@ssrobins")
