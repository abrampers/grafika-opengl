# OpenGL!

## Dependencies
```sh-session
brew install cmake
brew install glfw3
brew install glew
brew install assimp
```

## Build
```sh-session
mkdir build
cd build
cmake ..

# build all tasks
make

# Task 1: Green Pentagon
make green_pentagon

# Task 2a: Pentagon with different vertex colors
make pentagon

# Task 2b: Unicorn
make unicorn

# Task 3: Car
make jeep

# Task UAS: Car + Lighting + Rain + Smoke
make uas
```

## Run
```sh-session
cd build

# Task 1: Green Pentagon
./green_pentagon

# Task 2a: Pentagon with different vertex colors
./pentagon

# Task 2b: Unicorn
./unicorn

# Task 3: Car
./jeep

# Task UAS: Car + Lighting + Rain + Smoke
./uas
```

### Created by:
1. [Abram Situmorang](https://github.com/abrampers)
1. [Nicholas Rianto Putra](https://github.com/Nicholaz99)
1. [Faza Fahleraz](https://github.com/ffahleraz)