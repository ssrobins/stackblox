from conan import ConanFile

required_conan_version = ">=2.0.4"

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def build_requirements(self):
        self.test_requires("gtest/1.13.0")

    def requirements(self):
        self.requires("sdl/2.26.5")
        self.requires("sdl_image/2.0.5")
        self.requires("sdl_mixer/2.0.4")
        self.requires("sdl_ttf/2.20.1")
