set build_dir=%cd%
echo Setting up environment for Qt usage...
@rem IMPORTANTE, si instala otras versiones de QT, o si se instala este en otra
@rem dirección, revisar y corregir estos PATHS, o la generación del instalador 
@rem no funcionará
set PATH=C:\Qt\5.15.2\mingw81_32\bin;C:\Qt\Tools\mingw730_32\bin;C:\Qt\Tools\QtInstallerFramework\4.0\bin;%PATH%
echo Building...
@rem Etapa de compilación
cd %build_dir%\build
qmake.exe ../tprof.pro -spec win32-g++
mingw32-make -j8
@rem A partir de acá, existirá el ejecutable horno-inducción.exe, que es el programa final
@rem pero este no podrá ser ejecutado ya que faltan los .dll de QT
move .\release\horno-induccion.exe ..\deploy\packages\fiuba.solidos.amorfos\data
mkdir ..\deploy\packages\fiuba.solidos.amorfos\data\fuzzy
copy ..\fuzzy\* ..\deploy\packages\fiuba.solidos.amorfos\data\fuzzy
cd ..\deploy\packages\fiuba.solidos.amorfos\data
windeployqt horno-induccion.exe
@rem a partir de acá, el ejecutable se puede ejecutar normalmente. 
@rem Pero se procederá a realizar un instalador hecho y derecho
cd %build_dir%\deploy
binarycreator --offline-only -c config/config.xml -p packages horno-induccion-installer
move horno-induccion-installer.exe %build_dir%
rmdir /s/q packages\fiuba.solidos.amorfos\data
mkdir packages\fiuba.solidos.amorfos\data
cd %build_dir%