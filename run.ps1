& del *.exe *.o
& make
$env:LD_LIBRARY_PATH = ".\sfml\lib"
Start-Process -FilePath ".\graphit"
