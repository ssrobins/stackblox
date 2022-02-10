from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.6.0#508b1df8b9b4b37172e71af0c64acb23a413e3c9")
        self.build_requires("cmake_utils/6.0.1#c04990b3e6de61a45c1b7a2845a7aa6daf2abf9d")

    def requirements(self):
        self.requires("gtest/1.11.0#8ef69248cd41cd3a29dcfd3340f0589a291c2631")
        self.requires("ssrobins_engine/1.2.0#f5f260275e36f6cc278bb32787ab24d01b8b1356")
        self.requires("stackblox_assets/2.0.0#d287a5317b98108ba2594c5ed63217990ebc138e")
