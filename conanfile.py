from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.6.2#b2f5aa9e053147937e745afcdfb0c3e82afec4b9")
        self.build_requires("cmake_utils/9.0.1#b2f5aa9e053147937e745afcdfb0c3e82afec4b9")

    def requirements(self):
        self.requires("gtest/1.11.0#b2f5aa9e053147937e745afcdfb0c3e82afec4b9")
        self.requires("ssrobins_engine/1.2.0#b2f5aa9e053147937e745afcdfb0c3e82afec4b9")
