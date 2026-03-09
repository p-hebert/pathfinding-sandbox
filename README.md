# Pathfinding Sandbox Demo
## Build

Requirements:
- CMake ≥ 3.25
- Ninja
- C++20 compiler

```bash
git clone https://github.com/p-hebert/pathfinding-sandbox
cd pathfinding-sandbox

cmake --preset debug
cmake --build --preset debug
```

## Run

```bash
./build/debug/pathfinding_sandbox
```

## Run tests

```bash
ctest --test-dir build/debug
```