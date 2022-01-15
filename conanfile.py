from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.4.0#41295dd86e5d152269019ea03930766db0c0bddc")
        self.build_requires("cmake_utils/6.0.0#ac1a71244046f44f5484a554918f6a42a1f86d99")

    def requirements(self):
        self.requires("gtest/1.11.0#8ef69248cd41cd3a29dcfd3340f0589a291c2631")
        self.requires("ssrobins_engine/1.2.0#f5f260275e36f6cc278bb32787ab24d01b8b1356")
        self.requires("stackblox_assets/2.0.0#d287a5317b98108ba2594c5ed63217990ebc138e")
