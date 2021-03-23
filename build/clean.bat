@echo off
call clean_int.bat
del ..\bin\*_debug.* /q
del ..\bin\*_release.* /q
del ..\bin\*_retail.* /q
rd ..\lib /s /q
