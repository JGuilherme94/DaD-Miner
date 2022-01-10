rem do not show output
@echo off
rem clear last commands
cls
rem check if args are valid
if %1 == . goto :NoArg1
if %2 == . goto :NoArg2
if %3 == . goto :NoArg3
if %4 == . goto :NoArg4
if %5 == . goto :NoArg5
if %6 == . goto :NoArg6
if %7 == . goto :NoArg7
rem copy all necessary dlls to the build path
xcopy /y /f %6 %7
rem if everything allright execute the compile command line
g++ -std=c++11 -g %2 -o %7/%3 -I%4 -I%4/gtk-3.0 -I%4/glib-2.0 -I%4/pango-1.0 -I%4/harfbuzz -I%4/cairo -I%4/gdk-pixbuf-2.0 -I%4/atk-1.0 -L%5 -lstdc++ -lgtk-3.dll -lgdk-3.dll -lpangocairo-1.0.dll -lpango-1.0.dll -lharfbuzz.dll -latk-1.0.dll -lcairo-gobject.dll -lcairo.dll -lgdk_pixbuf-2.0.dll -lgio-2.0.dll -lgobject-2.0.dll -lglib-2.0.dll -lopencv_imgcodecs453.dll -lopencv_core453.dll -lopencv_objdetect453.dll -lopencv_highgui453.dll -lopencv_imgproc453.dll
rem -lgio-2.0.dll  -lgmodule-2.0.dll  -lharfbuzz.dll -lpango-1.0.dll -lopencv_core453.dll
rem after compilation goto the end of file
goto :EndOfFile

:NoArg1
echo "fatal error: no valid compiler args"
goto :EndOfFile

:NoArg2
echo "fatal error: no valid input file"
goto :EndOfFile

:NoArg3
echo "fatal error: no valid output file name"
goto :EndOfFile

:NoArg4
echo "fatal error: no valid include path"
goto :EndOfFile

:NoArg5
echo "fatal error: no valid lib path"
goto :EndOfFile

:NoArg6
echo "fatal error: no valid dll path"
goto :EndOfFile

:NoArg7
echo "fatal error: no valid build path"
goto :EndOfFile

:Execute
cd %7
tasklist | find /I %3
if errorlevel 1 (
        start %3 -help
) Else (
        taskkill /f /t /im %3
)
goto :Exit

:EndOfFile
rem check if program as been compiled for run the compiled program
if not exist %7/%3 echo %7/%3 not generated
if exist %7/%3 goto :Execute
goto :Exit

:Exit
exit