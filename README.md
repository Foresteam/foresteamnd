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
## Install (system-wide, use bash shell)
```bash
chmod +x install
sudo ./install
```
## Install-extract (use bash shell). Organizes files for future import
```bash
chmod +x install_extract
./install_extract
```
