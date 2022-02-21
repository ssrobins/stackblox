from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.6.0#508b1df8b9b4b37172e71af0c64acb23a413e3c9")
        self.build_requires("cmake_utils/6.1.0#9ced9bcfd95178b35d2ec5955b725a5652dbda26")

    def requirements(self):
        self.requires("gtest/1.11.0#8ef69248cd41cd3a29dcfd3340f0589a291c2631")
        self.requires("ssrobins_engine/1.2.0#781bb1f65dcb2ff4f3719dc0ea24e5857606dbd5")
        self.requires("stackblox_assets/2.0.0#d287a5317b98108ba2594c5ed63217990ebc138e")
