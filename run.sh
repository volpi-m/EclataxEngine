#!/usr/bin/bash

# Skip if conan is installed and install it otherwise

if ! [ -x "$(command -v conan)" ]; then
    # Install conan
    sudo pip install conan --upgrade

    # Set a default profile for conan and set the compiler at c++11
    conan profile new default --detect
    conan profile update settings.compiler.libcxx=libstdc++11 default

    # Add and / or update needed remotes for this project
    conan remote add conan_center https://api.bintray.com/conan/conan/conan-center
    conan remote add epitech https://api.bintray.com/conan/epitech/public-conan
    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
fi

# Build if needed, make otherwise

mkdir -p logs

if [ ! -d "./build" ] || [ "$1" == "-b" ] || [ "$1" == "--build" ]
then
    conan remote update conan_center https://api.bintray.com/conan/conan/conan-center
    conan remote update epitech https://api.bintray.com/conan/epitech/public-conan
    conan remote update bincrafters https://api.bintray.com/conan/bincrafters/public-conan

    # Remove old build folder and procces to a new build

    rm -rf build
    mkdir -p build && cd build && conan install ../conanfile.txt --build=missing && cmake .. && cd ..
else
    #  Make
    cd build && cmake --build . -- -j 4 && cd ..
fi