all:	array_test.exe array_kai_test.exe

CXXFLAGS = -Wall

COMMON_SRCS = trax_array.cpp move.cpp

ARRAY_TEST_SRCS = $(COMMON_SRCS) array_test.cpp
ARRAY_TEST_OBJS = $(ARRAY_TEST_SRCS:%.cpp=%.o)

ARRAY_KAI_TEST_SRCS = trax_array_kai.cpp array_kai_test.cpp $(COMMON_SRCS)
ARRAY_KAI_TEST_OBJS = $(ARRAY_KAI_TEST_SRCS:%.cpp=%.o)

.SUFFIXES: .cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

array_test.exe: $(ARRAY_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(ARRAY_TEST_OBJS) $(LDFLAGS)

array_kai_test.exe: $(ARRAY_KAI_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(ARRAY_KAI_TEST_OBJS) $(LDFLAGS)


clean:
	-rm -rf *.o *~ core main
