@echo off

powershell write-host -fore Yellow Copying files to destination... Configuration: Debug

set engine_source="Debug\Runtime\IceblurEngine.dll"
set dest_folder="Debug\Editor\"
copy %engine_source% %dest_folder%

powershell write-host -fore Green Finished.

pause
