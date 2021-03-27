from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#a8e9c63ad2763313865f84a027b0509ab6a4208f")
        self.build_requires("cmake_utils/0.3.1#da30d52b2c5db13fc90a22140f704d67c7635319")

    def requirements(self):
        self.requires("gtest/1.10.0#a2327ae0fc8d73335445e3951ae998a6f0887be4")
        self.requires("ssrobins_engine/0.3.0#7744a6a9ab567a8caa242397b15714d2b16a2441")
