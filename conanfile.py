from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.3.0#9517496737c184f98924eec823064964c8123474")
        self.build_requires("cmake_utils/5.1.0#2c0d8f9dda3cac137976849bb3851fd6c4999de0")

    def requirements(self):
        self.requires("gtest/1.11.0#8ef69248cd41cd3a29dcfd3340f0589a291c2631")
        self.requires("sdl2_mixer/2.0.4#d0ec5667eb6132eb971c09a3507ced0c50fd72e5")
        self.requires("ssrobins_engine/1.1.0#f5b55c46ffa5fc752c81d7a4454d743a2660adde")
        self.requires("stackblox_assets/1.1.0#7d2ab7c56b39064b4ff03ab69e5ff9cf0995bfeb1")
