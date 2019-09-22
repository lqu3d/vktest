for %%i in (*.frag) do (glslangValidator.exe -G %%i -o %%i.spv)

pause