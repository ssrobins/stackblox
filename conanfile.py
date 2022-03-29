from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.6.1#cec773c2bd9f752184188e5d43058439b4311cb4")
        self.build_requires("cmake_utils/6.1.0#9ced9bcfd95178b35d2ec5955b725a5652dbda26")

    def requirements(self):
        self.requires("gtest/1.11.0#8ef69248cd41cd3a29dcfd3340f0589a291c2631")
        self.requires("ssrobins_engine/1.2.0#9d170ee47bc0546ccf0cea5252e8e3eeab987548")
        self.requires("stackblox_assets/2.0.0#d287a5317b98108ba2594c5ed63217990ebc138e")
