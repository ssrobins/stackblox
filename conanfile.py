from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#33d7832e580dafa05810540f2808f3b070286189")
        self.build_requires("cmake_utils/0.3.1#30236679ffe9804515e8c092a744560a72ffb55a")

    def requirements(self):
        self.requires("gtest/1.10.0#af5a75e307b6039ab662434cb838441f1342fb51")
        self.requires("ssrobins_engine/0.2.0#0f3b444c5bc516d26feaea22fd73b5eded716c48")
