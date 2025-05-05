 g++ .\tests\game_test.cpp  `
-I"./tests/googletest-main/googletest/include" -I"./include/" `
-L"./tests/googletest-main/lib" `
-DWIN32_LEAN_AND_MEAN -DNOMINMAX `
-lgtest -lgtest_main -pthread `
-o game_test.exe