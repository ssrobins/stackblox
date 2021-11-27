from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.1.0#990c9e26dd59ee78d2fe5d1c3e2f1c544afe1dfd")
        self.build_requires("cmake_utils/4.0.0#6f1fbd5e82af9782f3cb28a040dfe34c6e5c990a")

    def requirements(self):
        self.requires("gtest/1.11.0#7a8dc4022cf1753b71057bfe89043cf4a5b4dc8f")
        self.requires("ssrobins_engine/1.0.0#6de66ab2a4a7269def4a08fa8be75f6b5cd89deb")
