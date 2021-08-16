from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#d299a2e1a9b1b779eb0e2bd7c11d2cf845e5f403")
        self.build_requires("cmake_utils/0.3.1#77d5f06b9b20302a5410e41ed45e7bbea7de90a5")

    def requirements(self):
        self.requires("gtest/1.11.0#e16a50c3a5d1fcb9955b759f6b6d82dea712d821")
        self.requires("ssrobins_engine/0.3.0#4c16af68030be3ef1ad1b9eb0a139e58c1449886")
