apt-get update
apt-get install curl zip unzip tar
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
 ./bootstrap-vcpkg.sh
cd ..
vcpkg install libenvpp

vcpkg integrate install


mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake ..

make
./QtServerApp


$env:VCPKG_ROOT = "C:\path\to\vcpkg"
$env:PATH = "$env:VCPKG_ROOT;$env:PATH"



vcpkg install


cmake --preset=default
cmake --build build
./build/QtServerApp


# экпортировать переменные среды из .env


rm -rf ./build/

# https://learn.microsoft.com/ru-ru/vcpkg/get_started/get-started?pivots=shell-powershell