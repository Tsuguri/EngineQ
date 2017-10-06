IF NOT EXIST Build MD Build
cd Build
IF NOT EXIST MSVC_clang MD MSVC_clang
cd MSVC_clang
cmake.exe -G "Visual Studio 14 Win64" -T v140_clang_c2 ../../Source
START EngineQ.sln