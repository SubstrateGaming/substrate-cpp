from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class libSubstratePackage(ConanFile):

    # Metadata
    name = "libsubstrate"
    version = "1.0.0"
    license = "Apache-2.0 license"
    author = "svnscha"
    description = "C++ client interface to Polkadot (Substrate)"
    topics = ("crypto", "polkadot", "substrate", "sr25519")

    # Binary configuration
    settings = "os", "compiler", "arch", "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    options = {"shared": [True, False]}

    default_options = {
        "shared": True,
        "boost*:header_only": True,
        "libsodium*:shared": False,
    }

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "libSubstrate/*", "deps/*"

    def requirements(self):
        self.requires("boost/1.84.0")
        self.requires("nlohmann_json/3.11.3")
        self.requires("libsodium/1.0.19")
        self.requires("gtest/1.14.0")
        self.requires("sr25519/1.0.0@svnscha/dev")
        self.requires("libcurl/8.7.0@svnscha/dev")

    def layout(self):
        self.folders.build_folder_vars = ["settings.os", "settings.compiler", "settings.compiler.version", "settings.arch", "settings.build_type"]
        cmake_layout(self)

    def config_options(self):
        pass

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["libSubstrate"]
