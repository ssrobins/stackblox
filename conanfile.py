from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/0.1.0#5ce8c1a310ba03a40c1b8e3f5059eecfcb287e30")
        self.build_requires("cmake_utils/0.3.1#d093c585be2418d6a664babbec39e71d6b5cd11d")

    def requirements(self):
        self.requires("gtest/1.10.0#1dc34103486deb0c4056a3326c005456f805fc6b")
        self.requires("ssrobins_engine/0.2.0#1a5b63e14ea15c351c3f5b3e187336c3fdfc7f7f")
