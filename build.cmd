mkdir -p build\ && cd build\ && rmdir build\
cd build\ && g++ -I..\ -o messagebus ..\main.cpp ..\http_tcpserver.cpp -lstdc++ -lws2_32