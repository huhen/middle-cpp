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

```
make
sudo make install
```
