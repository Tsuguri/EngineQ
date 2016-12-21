IF NOT EXIST Projects\MSVC_clang MD Projects\MSVC_clang
cd Projects\MSVC_clang
cmake.exe -G "Visual Studio 14 Win64" -T v140_clang_c2 ../../Source
START EngineQ.sln