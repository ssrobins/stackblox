from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires.add("android_sdl2/0.1.0#debda07d9c722b256dc83beccc487d30fffbd274")
        self.build_requires.add("cmake_utils/0.3.1#95dea75496ef60374382c194489e6524e9503eb4")

    def requirements(self):
        self.requires.add("gtest/1.10.0#39adcd397319f61148b40f694b47ab5b3e6fa320")
        self.requires.add("ssrobins_engine/0.2.0#10d9dedb6d496652315dcd3331130945de88aefd")
