# PMC Game Engine
A 3D game engine written in C++ utilizing Irrlicht and BulletPhysics.
View the [Wiki](https://github.com/morgenm/PMC-Game/wiki) to see the Engine and to view the Architecture document.

# Building the Engine
## Building on 64-bit machines
```
mkdir build
cd build
cmake .. -A x64
cmake --build . --config Release
```

## Building Debug on 64-bit machines
```
mkdir build
cd build
cmake .. -A x64 -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```
### To then run the tests
```
python tests/run_all_tests.py build_directory
```
