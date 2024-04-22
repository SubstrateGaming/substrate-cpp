# 📦 libSubstrate

This project has developed a comprehensive library that is compatible with the substrate ecosystem, akin to [Substrate.NET.API](https://github.com/SubstrateGaming/Substrate.NET.API). It offers all the necessary interfaces for interacting with a substrate node. For practical applications of this library, please consult the provided usage examples.

## Setup Git Hooks

This project uses Git hooks to enforce certain rules and perform checks before committing code.

To enable these hooks, run the following command:

```bash
git config core.hooksPath .githooks
```

## Setup a development node

```yaml
version: '2'

services:
  substrate:
    container_name: substrate
    image: parity/substrate:latest
    ports:
      - 30333:30333   # p2p port
      - 9933:9933     # rpc port
      - 9944:9944     # ws port
      - 9615:9615     # Prometheus port
    command: [
      "--dev",
      "--rpc-external",
      "--prometheus-external",
      "--rpc-cors", "all"
    ]

  polkadotui:
    container_name: polkadotui
    image: jacogr/polkadot-js-apps
    environment:
      - WS_URL=ws://[YOUR-MACHINE-IP]:9944
    ports:
      - 80:80
```

## Requirements

- [Conan](https://conan.io/)
- CMake
- A C++ compiler
- Libraries, prebuild in your local Conan registry:
  - [sr25519](https://github.com/svnscha/sr25519)
  - [libcurl (with web sockets)](https://github.com/svnscha/libcurl-conan)
  - [libscale](https://github.com/svnscha/scale-codec-cpp)

## 🚀 Usage

Add this package to your project's `conanfile.txt`:

```ini
[requires]
libSubstrate/1.0.1@svnscha/dev

[generators]
cmake
```

To install dependencies, run:

```sh
conan install .
```

To build your project with Conan, run:

```sh
mkdir build && cd build
conan build ..
```

## 🧪 Export Dependencies

```sh
cd external/libcurl-conan/all
conan export --user svnscha --channel dev --version 8.6.0 .

cd external/scale-codec-cpp
conan export --user svnscha --channel dev .

cd external/sr25519
conan export --user svnscha --channel dev .
```

## 🧪 Export this Package

To export the Conan package, navigate to the directory containing conanfile.py and run:

```sh
conan export --user svnscha --channel dev .
```

This exports the package to your local cache, usable by other projects.

## 🧪 Building the Package

For local development you could simply use

```sh
conan create --build=missing .
```

## 🧪 Development

```sh
conan install conanfile.py -s build_type=Debug --build=missing
```

and then select your CMake presets in your favorite IDE and work on this library.

## References

- Substrate.NET.API
  - https://github.com/SubstrateGaming/Substrate.NET.API

- Start a Node
  - https://docs.substrate.io/quick-start/start-a-node/

- Scale Cocdec
  - https://github.com/qdrvm/scale-codec-cpp/tree/master
  - https://docs.substrate.io/reference/scale-codec/
