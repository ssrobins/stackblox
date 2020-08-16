from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#1d2ac253f9887def0813161c99f252f08e127f1f")
        self.build_requires("cmake_utils/0.3.1#a680a99b588c0c874b8ee9af304acf30aa3b5787")

    def requirements(self):
        self.requires("gtest/1.10.0#e94a23d95f707f467fac115a8b586b41f07f24ff")
        self.requires("ssrobins_engine/0.2.0#3a781ba48b31bee03f7ce622d27d2b9861203591")
