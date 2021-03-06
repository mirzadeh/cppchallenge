#include <iostream>

#include <cppchallenge/matrix2d.h>
#include <cppchallenge/utilities.h>

using namespace std;
using namespace cppchallenge;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " [testfile]" << endl;
        return EXIT_FAILURE;
    }

    TestData<double> data;
    try {
        ifstream file(argv[1]);
        data.parse(file);

    } catch (const std::exception& e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    auto& A = data.mat["A"];
    auto& B = data.mat["B"];
    auto& X = data.vec["X"];

    // Add a list of tests to be executed -- each test will be run in try-catch block separately
    vector<Test> tests;
    tests.push_back({"Matrix-Vector multiply", [&] { return compare(A*X, data.vec["AX"]); }});
    tests.push_back({"Matrix-Matrix addition", [&] { return compare(A+B, data.mat["A+B"]); }});
    tests.push_back({"Matrix-Matrix subtraction", [&] { return compare(A-B, data.mat["A-B"]); }});
    tests.push_back({"Matrix-Matrix multiply", [&] { return compare(A*B, data.mat["A*B"]); }});
    tests.push_back({"Matrix transposition",
                     [&] { return compare(A.transpose(), data.mat["A^T"]); }});

    // testing various forms of associativity and distributivity
    tests.push_back({"A+B == B+A", [&] { return compare(A+B, B+A); }});
    tests.push_back({"(A+B)+B == A+(B+B)", [&] { return compare((A+B)+B, A+(B+B)); }});
    tests.push_back({"(A+B)*X == AX+BX", [&] { return compare((A+B)*X, A*X+B*X); }});
    tests.push_back({"(A+B)*B == A*B+B*B", [&] { return compare((A+B)*B, A*B+B*B); }});
    tests.push_back({"A^T^T == A",
                     [&] { return compare(A.transpose().transpose(), A); }});
    tests.push_back({"(A*B)^T == B^T*A^T",
                     [&] { return compare((A*B).transpose(), B.transpose()*A.transpose()); }});

    // run all tests
    int num_failed = 0;
    for (auto& t: tests) num_failed += runtest(t);

    cout << endl;
    if (num_failed == 0) {
        cout << "All tests passed!\n";
    } else {
        cout << num_failed << " tests failed\n";
    }

    return num_failed;
}
