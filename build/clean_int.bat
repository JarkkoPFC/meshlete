@echo off
rd ..\_intermediate /s /q
del ..\bin\*.idb /s /q
del ..\bin\*.ilk /s /q
del ..\lib\*.idb /s /q
del ..\src\*.tmp /s /q
del *.user /s /q
del *.ncb /s /q
del *.sdf /s /q
del *.idb /s /q
del *.suo /a:h /s /q
rd vs2010\ipch /s /q
rd vs2012\ipch /s /q
rd vs2013\ipch /s /q
rd vs2015\ipch /s /q
rd vs2015\.vs /s /q
rd vs2017\.vs /s /q
rd vs2019\.vs /s /q
