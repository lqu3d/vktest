for %%i in (*.vert) do (glslangValidator.exe -G %%i -o %%i.spv)

pause