#include <iostream>
#include <gtest/gtest.h>

#include "ERTWrapper/test_eclgridreader.cpp"

#include "Model/reservoir/grid/test_grid.cpp"
#include "Model/reservoir/grid/test_ijkcoordinate.cpp"
#include "Model/reservoir/grid/test_xyzcoordinate.cpp"
#include "Model/reservoir/grid/test_cell.cpp"
#include "Model/variables/test_variables.cpp"
#include "Model/variables/test_variablecontainer.cpp"

using namespace std;

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from gtest_main.cc\n");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
