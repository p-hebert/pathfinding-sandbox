# Pathfinding Sandbox Demo

## Quick Start

```bash
cmake --preset debug
cmake --build --preset debug
./build/debug/pathfinding_sandbox
```

## Build environment setup

### MacOS

```bash
xcode-select --install
brew install cmake ninja

# Symlink clang-format, clang-tidy directly
# Avoids exporting LLVM in PATH, which would override the Apple-provided LLVM.
ln -s /opt/homebrew/opt/llvm/bin/clang-format /opt/homebrew/bin/clang-format
ln -s /opt/homebrew/opt/llvm/bin/clang-tidy /opt/homebrew/bin/clang-tidy
```
