#include "iostream"
//#include "referVector.h"
#include "myVector.h"
#include "myList.h"
#include "vector"
#include "memory"
#include "fstream"
#include "Dpll.h"
#include "chrono"
#include "CnfParser.h"
#include "regex"
#include "SudokuSolver.h"
#include "Interface.h"
//#include "algorithm"
using namespace std;


int main(void) {
//    auto satSolver = *new SatSolver;
//    auto cnfParser = *new CnfParser;
//    auto sudokuSolver = *new SudokuSolver;
//    Formula formula = cnfParser.readCnf("Sudoku.cnf");
////    cout << formula.Size()<< endl;
//    Solution solution = satSolver.Solve(formula, cnfParser.symbolNum);
//    cnfParser.outputSolution(satSolver.status, solution, satSolver.time);
    App app = *new App;
    app.Start();

    return 0;
}