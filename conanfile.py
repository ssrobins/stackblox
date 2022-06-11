from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def requirements(self):
        if self.settings.os == "Android":
            self.requires("android_sdl2/2.6.2#3c96b14f735a4e9fee75ee9a586b4d1076e016b7")
        self.requires("cmake_utils/9.0.1#3c96b14f735a4e9fee75ee9a586b4d1076e016b7")
        self.requires("gtest/1.11.0#3c96b14f735a4e9fee75ee9a586b4d1076e016b7")
        self.requires("ssrobins_engine/1.2.0#3c96b14f735a4e9fee75ee9a586b4d1076e016b7")
