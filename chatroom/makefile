# 声明编译器
CXX = g++
# 声明编译选项
CFLAGS = -Wall -g
# 声明可执行文件名
TARGET = server

# 声明编译规则
$(TARGET): server.cpp mySocket.cpp mySocket.h
	$(CXX) $(LDFLAGS) $^ -o $@

client: server.cpp mySocket.cpp mySocket.h
	$(CXX) $(LDFLAGS) $^ -o $@
# 声明清理规则
clean:
	rm -f $(TARGET)

