#!/bin/sh
set -e

# Save working directory
original_dir=$(pwd)

cd external/libcurl-conan/all
conan export --user svnscha --channel dev --version 8.6.0 .

cd "$original_dir/external/scale-codec-cpp"
conan export --user svnscha --channel dev .

cd "$original_dir/external/sr25519"
conan export --user svnscha --channel dev .

# Move back to working directory
cd "$original_dir"

# Build
conan create . --profile:host ./conan-profiles/linux.profile --profile:build ./conan-profiles/linux.profile --build=missing --format json > release.json
