IF NOT EXIST Build MD Build
cd Build
IF NOT EXIST MSVC MD MSVC
cd MSVC
cmake.exe -G "Visual Studio 14 Win64" ../../Source
START EngineQ.sln