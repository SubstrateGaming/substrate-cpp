# libSubstrate

## Development

### Setting up Git Hooks

This project uses Git hooks to enforce certain rules and perform checks before committing code.

To enable these hooks, run the following command:

```bash
git config core.hooksPath .githooks
```

### Setup a development node

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

## Building

```sh
# Initialize the project (for development)
conan install conanfile.py -s build_type=Debug --output-folder build --build=missing

# Initialize the project
conan install conanfile.py -s build_type=Release --output-folder build --build=missing

# Build (assuming Windows and MSVC)
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build . --config Release
```

## References

- Substrate.NET.API
  - https://github.com/SubstrateGaming/Substrate.NET.API

- Start a Node
  - https://docs.substrate.io/quick-start/start-a-node/

- Scale Cocdec
  - https://github.com/qdrvm/scale-codec-cpp/tree/master
  - https://docs.substrate.io/reference/scale-codec/
