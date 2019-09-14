from conans import ConanFile

class Conan(ConanFile):

    settings = "os"
    generators = "cmake"

    def requirements(self):
        self.requires.add("ssrobins_engine/0.1.0#f678e48bb74e5231a29056bb9e3d1fe8d1235425")
