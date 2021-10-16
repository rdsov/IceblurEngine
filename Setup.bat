mkdir Engine\Binaries\Win64\Debug\Editor
mkdir Engine\Binaries\Win64\Release\Editor

echo %cd%\Engine> %cd%\Engine\Binaries\Win64\Debug\Editor\InstallLocation.txt
echo %cd%\Engine> %cd%\Engine\Binaries\Win64\Release\Editor\InstallLocation.txt

CALL .\GenerateProjectFiles.bat