from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake", "cmake_find_package_multi"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.6.2#da38ed876673a6da88d73f6dcb0138de5561125b")
        self.build_requires("cmake_utils/8.0.0#b0932588b4ccd8ac8db4fed90295f7480ac0b37f")

    def requirements(self):
        self.requires("gtest/1.11.0#b6d68d3070e0f968f2a456728c7f7af1621d51f2")
        self.requires("ssrobins_engine/1.2.0#9e4bcecf20b6b5dd4e4317a179d9b5c48b504097")
        self.requires("stackblox_assets/2.0.0#d287a5317b98108ba2594c5ed63217990ebc138e")
