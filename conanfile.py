from conans import ConanFile

class Conan(ConanFile):

    settings = "os"
    generators = "cmake"

    def requirements(self):
        self.requires.add("gtest/1.8.1#0ab3cafdcd7fe85deaefe41b3011d36fbd86e38e")
        self.requires.add("ssrobins_engine/0.1.0#fd9f76ce040cba32fc6e47149b55ddb655da90dd")
