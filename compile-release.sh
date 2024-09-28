conan install . --settings=build_type=Release --build=missing
cmake --preset=conan-release
cmake --build build/Release/