# foresteamnd
## Prepare build
```bash
mkdir build
cd build
cmake ..
```
## Build (Linux)
```bash
cmake --build . --config Release -j{NUMBER_OF_THREADS}
```
## Build (Windows)
```bash
cmake --build . --target ALL_BUILD --config Release
```
## Install
```bash
chmod +x install
sudo ./install
```
