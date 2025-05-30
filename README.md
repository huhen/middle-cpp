https://practicum.yandex.ru/profile/middle-cpp/


Установка clang
```
sudo apt install clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python3-clang
```

Установка jemalloc
```
git clone -b 5.3.0 https://github.com/jemalloc/jemalloc.git
cd jemalloc
./autogen.sh --enable-prof
```
или
```
wget https://github.com/jemalloc/jemalloc/releases/download/5.3.0/jemalloc-5.3.0.tar.bz2
tar -xjf jemalloc-5.3.0.tar.bz2
cd jemalloc-5.3.0
./configure --enable-prof
```
далее:
```
make
sudo make install
```

Запуск с профилированием:
```
MALLOC_CONF=prof_leak:true,lg_prof_sample:0,prof_final:true,prof:true ./app
```

windows
в settings "cmake.generator": "Ninja"
```
winget install Ninja-build.Ninja
winget install cmake
```

boost
```
cd ~
wget https://archives.boost.io/release/1.88.0/source/boost_1_88_0.tar.bz2
tar -xjf boost_1_88_0.tar.bz2
cd boost_1_88_0
./bootstrap.sh --prefix=/usr/local/boost-1.88.0
./b2 headers
# ./b2
sudo ./b2 install
```