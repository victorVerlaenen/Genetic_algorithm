



if not exist %LIBRARY_PREFIX%\include\xtl\xbasic_fixed_string.hpp (exit 1)
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %LIBRARY_PREFIX%\share\cmake\xtl\xtlConfig.cmake (exit 1)
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %LIBRARY_PREFIX%\share\cmake\xtl\xtlConfigVersion.cmake (exit 1)
IF %ERRORLEVEL% NEQ 0 exit /B 1
exit /B 0
