from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#85f60caeb1c67dda9309809530c85f60a781b916")
        self.build_requires("cmake_utils/0.3.1#bddead915084dbfac2b4114574fae5ae8545e540")

    def requirements(self):
        self.requires("gtest/1.10.0#1c931c5867b5491b08d404971e9171cefb8188a5")
        self.requires("ssrobins_engine/0.2.0#981c6feef81508d8359b065867fb3e2959dbb43a")
