@echo off
@echo Setting up mini_sxp project dependency
@echo.
@echo Please enter mini_sxp directory (where README.md resides) to use with this
@echo project. The path can be relative, e.g. "..\..\mini_sxp\trunk". This will
@echo create directory symlink "mini_sxp" in this directory that is used to find
@echo mini_sxp files when compiling the project. As the result of successful
@echo symlink creation you should see "mini_sxp" which links to the mini_sxp dir.
@echo.
@echo Note: deleting the created "mini_sxp" symlink won't delete the content of
@echo the linked directory but only the symlink.
@echo.
set /p MINI_SXP_DIR="mini_sxp dir: "
mklink /D mini_sxp %MINI_SXP_DIR%
pause
