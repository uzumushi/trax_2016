all:	array_test.exe array_kai_test.exe tree_node_test.exe

CXXFLAGS = -Wall -O3

ARRAY_SRCS = trax_array.cpp move.cpp
ARRAY_KAI_SRCS = trax_array_kai.cpp $(ARRAY_SRCS)
TREE_NODE_SRCS = trax_tree_node.cpp $(ARRAY_KAI_SRCS)

ARRAY_TEST_SRCS = $(ARRAY_SRCS) array_test.cpp
ARRAY_TEST_OBJS = $(ARRAY_TEST_SRCS:%.cpp=%.o)

ARRAY_KAI_TEST_SRCS = array_kai_test.cpp $(ARRAY_KAI_SRCS)
ARRAY_KAI_TEST_OBJS = $(ARRAY_KAI_TEST_SRCS:%.cpp=%.o)

TREE_NODE_TEST_SRCS = tree_node_test.cpp $(TREE_NODE_SRCS)
TREE_NODE_TEST_OBJS = $(TREE_NODE_TEST_SRCS:%.cpp=%.o)

.SUFFIXES: .cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

array_test.exe: $(ARRAY_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(ARRAY_TEST_OBJS) $(LDFLAGS)

array_kai_test.exe: $(ARRAY_KAI_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(ARRAY_KAI_TEST_OBJS) $(LDFLAGS)

tree_node_test.exe: $(TREE_NODE_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TREE_NODE_TEST_OBJS) $(LDFLAGS)

clean:
	-rm -rf *.o *~ core main
