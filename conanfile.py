from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#b05721a9fb7f10bd7ae3392924dcf58aa497abb9")
        self.build_requires("cmake_utils/0.3.1#77d5f06b9b20302a5410e41ed45e7bbea7de90a5")

    def requirements(self):
        self.requires("gtest/1.11.0#5c7586ef6610e8053ee79086fbc7743d9fbde653")
        self.requires("ssrobins_engine/0.3.0#3b2b885d3bfc96b00e7c3c69fdd2282f02f3bde3")
