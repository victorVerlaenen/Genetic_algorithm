



if not exist %LIBRARY_PREFIX%\include\xtensor\xarray.hpp (exit 1)
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %LIBRARY_PREFIX%\lib\cmake\xtensor\xtensorConfig.cmake (exit 1)
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %LIBRARY_PREFIX%\lib\cmake\xtensor\xtensorConfigVersion.cmake (exit 1)
IF %ERRORLEVEL% NEQ 0 exit /B 1
exit /B 0
