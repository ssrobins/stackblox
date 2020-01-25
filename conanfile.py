from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires.add("android_sdl2/0.1.0#6bcfa9bb0ef5adf28594b838a718ed2e8ce90208")
        self.build_requires.add("cmake_utils/0.3.1#7b308615a235fdf046db096dd35325c0375c2f88")

    def requirements(self):
        self.requires.add("gtest/1.10.0#fbedb03a0bb64f1df48a54f4394eab3978d6ffb3")
        self.requires.add("ssrobins_engine/0.2.0#bf865cfccef9adeb95fd387b723c796adb0cfcdc")
