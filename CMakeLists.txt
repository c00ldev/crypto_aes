cmake_minimum_required(VERSION 3.10)
project(crypto_aes)

set(CMAKE_CXX_STANDARD 17)

add_executable(aes main.cpp AES.h SBox.cpp SBox.h RowShifter.cpp RowShifter.h Block.h ColumnMixer.cpp ColumnMixer.h KeySchedule.h InvalidKeySize.cpp InvalidKeySize.h)
