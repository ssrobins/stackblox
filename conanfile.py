from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def requirements(self):
        self.requires.add("gtest/1.10.0#016389183489f5c0a5db55001303991db14e7ce1")
        self.requires.add("ssrobins_engine/0.1.0#bfdd7e61f2ae28bfee82720e4b9e9b39ff8da27d")
