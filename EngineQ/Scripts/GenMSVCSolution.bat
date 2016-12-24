cd ..
IF NOT EXIST Build MD Build
cd Build
IF NOT EXIST MSVC MD MSVC
cd MSVC
cmake -G "Visual Studio 14 Win64" ../../Source
cd ../../Scripts