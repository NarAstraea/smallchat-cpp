PROTOC		= protoc
PROTO_FILES = NormalMessagePacket.proto
PROTO_SRC	= NormalMessagePacket.pb.cc
PROTO_HDR	= NormalMessagePacket.pb.h

CXX 		= g++
CXXFLAGS 	= -g -O0 -Wall -Wextra -std=c++17
SRCDIR 		= .
BUILDDIR 	= build
TARGET_S 	= $(BUILDDIR)/smallchat-server
TARGET_C 	= $(BUILDDIR)/smallchat-client
LDFLAGS 	= -lboost_system -lboost_thread -lboost_chrono
SRCS 		= $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.cc)
SRCS_S 		= $(filter-out $(SRCDIR)/smallchat-client.cpp, $(SRCS))
SRCS_C 		= $(filter-out $(SRCDIR)/smallchat-server.cpp, $(SRCS))
OBJS_S 		= $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(filter %.cpp,$(SRCS_S))) \
			  $(patsubst $(SRCDIR)/%.cc, $(BUILDDIR)/%.o, $(filter %.cc,$(SRCS_S)))
OBJS_C 		= $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(filter %.cpp,$(SRCS_C))) \
			  $(patsubst $(SRCDIR)/%.cc, $(BUILDDIR)/%.o, $(filter %.cc,$(SRCS_C)))

#generate Message Packet code
$(PROTO_SRC) $(PROTO_HDR): $(PROTO_FILES)
	$(PROTOC) --cpp_out=. $(PROTO_FILES)

#compile c++ code
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:clean smallchat-server
smallchat-server:$(TARGET_S)

$(TARGET_S): $(OBJS_S)
	$(CXX) $(OBJS_S) -o $@ $(LDFLAGS)

.PHONY:clean smallchat-client
smallchat-client:$(TARGET_C)

$(TARGET_C): $(OBJS_C)
	$(CXX) $(OBJS_C) -o $@ $(LDFLAGS)

.PHONY:clean all
all: smallchat-server smallchat-client

.PHONY:clean
clean:
	rm -f $(OBJS_S) $(OBJS_C) $(TARGET_S) $(TARGET_C)

.PHONY:run_s
run_s:$(TARGET_S)
	./$(TARGET_S)

.PHONY:run_c
run_c:$(TARGET_C)
	./$(TARGET_C)
