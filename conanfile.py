from conans import ConanFile

class Conan(ConanFile):
    name = "StackBlox"
    version = ""
    settings = "os"
    generators = "cmake"

    def requirements(self):
        self.requires.add("gtest/1.8.1#0ab3cafdcd7fe85deaefe41b3011d36fbd86e38e")
        self.requires.add("ssrobins_engine/0.1.0#fd90aa57c604024d1e49597f75616ad42c7683a1")
