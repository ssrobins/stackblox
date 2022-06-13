from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps"

    def requirements(self):
        if self.settings.os == "Android":
            self.requires("android_sdl/2.6.2#fe249e56a871dd3e09cf9ecbdac13e775463d983")
        self.requires("cmake_utils/10.0.1#fe249e56a871dd3e09cf9ecbdac13e775463d983")
        self.requires("gtest/1.11.0#fe249e56a871dd3e09cf9ecbdac13e775463d983")
        self.requires("ssrobins_engine/1.2.0#fe249e56a871dd3e09cf9ecbdac13e775463d983")
