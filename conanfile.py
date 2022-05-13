from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def build_requirements(self):
        if self.settings.os == "Android":
            self.build_requires("android_sdl2/2.6.2#da38ed876673a6da88d73f6dcb0138de5561125b")
        self.build_requires("cmake_utils/6.1.0#9ced9bcfd95178b35d2ec5955b725a5652dbda26")

    def requirements(self):
        self.requires("gtest/1.11.0#e4ccbfb41abf17466702bd741d880a1dd2a45fba")
        self.requires("ssrobins_engine/1.2.0#197264673b517775154e16290712d883fe80574b")
        self.requires("stackblox_assets/2.0.0#d287a5317b98108ba2594c5ed63217990ebc138e")
