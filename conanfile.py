from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def requirements(self):
        if self.settings.os == "Android":
            self.requires("android_sdl/2.6.2#f374feb3c060e091bdaf0a0005dd64c28ed04c67")
        self.requires("cmake_utils/10.0.1#f374feb3c060e091bdaf0a0005dd64c28ed04c67")
        self.requires("gtest/1.11.0#f374feb3c060e091bdaf0a0005dd64c28ed04c67")
        self.requires("ssrobins_engine/1.2.0#f374feb3c060e091bdaf0a0005dd64c28ed04c67")
