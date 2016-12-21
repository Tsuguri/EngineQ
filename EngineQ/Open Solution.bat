IF NOT EXIST Projects\MSVC MD Projects\MSVC
cd Projects\MSVC
cmake.exe -G "Visual Studio 14 Win64" ../../Source
START EngineQ.sln