call ndk-build clean
call ndk-build TARGET_LINK=0 NDK_DEBUG=0 CONFIGURATION=StaticRelease
call ndk-build TARGET_LINK=0 NDK_DEBUG=1 CONFIGURATION=StaticDebug
rmdir /s /q libs
rmdir /s /q obj
call ndk-build clean
call ndk-build TARGET_LINK=1 NDK_DEBUG=0 CONFIGURATION=DynamicRelease
call ndk-build TARGET_LINK=1 NDK_DEBUG=1 CONFIGURATION=DynamicDebug
rmdir /s /q libs
rmdir /s /q obj
xcopy /y ..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\arm64-v8a\StaticRelease\
xcopy /y ..\..\..\BuildFiles\Android\armeabi\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\armeabi\StaticRelease\
xcopy /y ..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\armeabi-v7a\StaticRelease\
xcopy /y ..\..\..\BuildFiles\Android\mips\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\mips\StaticRelease\
xcopy /y ..\..\..\BuildFiles\Android\mips64\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\mips64\StaticRelease\
xcopy /y ..\..\..\BuildFiles\Android\x86\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\x86\StaticRelease\
xcopy /y ..\..\..\BuildFiles\Android\x86_64\StaticRelease\lib81589BFED0B84B1194524BEE623E1838.a %ECO_FRAMEWORK%\Eco.String1\BuildFiles\Android\x86_64\StaticRelease\
pause
