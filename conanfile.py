from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.1.0#4631baf96c5937b22753e9ac1146265ca3b32aff")
        self.build_requires("cmake_utils/5.0.0#1ecfed8c68a43ea17d321701cc8a91df21d06453")

    def requirements(self):
        self.requires("gtest/1.11.0#8ef69248cd41cd3a29dcfd3340f0589a291c2631")
        self.requires("ssrobins_engine/1.1.0#f5b55c46ffa5fc752c81d7a4454d743a2660adde")
        self.requires("stackblox_assets/1.0.0#7e796301888eccdfe557d90cfa53f6dff5ab97e7")
