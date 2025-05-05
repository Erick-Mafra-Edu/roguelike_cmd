windres icon.rc -o recursos.o
g++ .\main.cpp .\recursos.o -o mygame.exe
g++ ./include/readSave.cpp -o ReadSave.exe -DWIN32_LEAN_AND_MEAN -DNOMINMAX
#g++ .\tests\game_test.cpp -I"./tests/googletest-main/googletest/include" -I"./include/" -L"./tests/googletest-main/lib"