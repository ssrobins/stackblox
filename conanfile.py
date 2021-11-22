from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/1.0.0#33a5929ed7796027107fb57187ae4248e0faf3ce")
        self.build_requires("cmake_utils/3.0.0#4e7b4d9bfca394477325cdfc8eacce8b1c82583e")

    def requirements(self):
        self.requires("gtest/1.11.0#7a8dc4022cf1753b71057bfe89043cf4a5b4dc8f")
        self.requires("ssrobins_engine/1.0.0#6de66ab2a4a7269def4a08fa8be75f6b5cd89deb")
