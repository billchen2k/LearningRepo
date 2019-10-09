@ if /I  "%1" == "-r"         goto uninstall
@ if /I  "%1" == "-remove"    goto uninstall
@ if /I  "%1" == "-u"         goto uninstall
@ if /I  "%1" == "-uninstall" goto uninstall
@ if NOT "%1" == ""           goto usage
@ goto install

:install
@
@ rem -- all assembly should be made with "make TARGET=INSTALL" to be installed
@
gacutil.exe /if csgl.dll
copy csgl.native.dll  %SystemRoot%\System32
copy csgl.dll         %SystemRoot%\System32
@goto end

:uninstall
@
@ rem -- take care to remove all previous version
@
gacutil.exe /u csgl-extension
gacutil.exe /u csgl-opengl
gacutil.exe /u csgl-base
gacutil.exe /u csgl
del %SystemRoot%\System32\csgl-extension.dll
del %SystemRoot%\System32\csgl-opengl.dll
del %SystemRoot%\System32\csgl-base.dll
del %SystemRoot%\System32\csgl-native.dll
del %SystemRoot%\System32\csgl.native.dll
del %SystemRoot%\System32\csgl.dll
@goto end

:usage
@ echo " usage :
@ echo " - install     => install   csgl
@ echo " - install -u  => uninstall csgl
@goto end

:end