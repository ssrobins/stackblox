from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires.add("android_sdl2/0.1.0#db746d43b1b7e728db3b2d280aae273da3922e68")
        self.build_requires.add("cmake_utils/0.1.0#89a9bc6923fea4dabf19de6aa6b7ddcf8667b2ee")

    def requirements(self):
        self.requires.add("gtest/1.10.0#ca07d9d05d12f3bbb091f095e30f7c54cd2920ee")
        self.requires.add("ssrobins_engine/0.2.0#fe91404a263a00b29446e96f31fb1484a8de7306")
