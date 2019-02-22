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
//#include "algorithm"
using namespace std;

Solution solution = *new Solution;

bool Dpll(Formula origin, int baseValue) {
    if (baseValue != 0) {
        origin = Simplify(origin, baseValue);
        cout << "";
//        solution.push_back(baseValue);
    }

    int simpleValue = 0;

    if (origin.Size() == 0) {
//        solution.push_back(baseValue);
        return true;  //empty formula--Solved
    }
    for (auto p = origin.Start();; p = p->next) {
        auto temp = p->data.Start();
        if (temp == NULL) {
//            solution.erase(solution.End());
            return false;  //empty clause--No Slution

        }
        if (temp == p->data.End()) {
            //single clause--use it to further simplify
            simpleValue = temp->data;
            if (Dpll(origin, simpleValue)) {
                solution.push_back(simpleValue);
                return true;
            } else
                return false;
//            break;
        }
        if (p == origin.End()) {
            simpleValue = temp->data;
            break;
        }
    }
    auto backup = *(new Formula);
    for (auto p = origin.Start();; p = p->next) {
        auto tempClause = *(new Clause);

        for (auto pList = p->data.Start(), pListEnd = p->data.End(); pList != NULL; pList = pList->next) {
            tempClause.push_back(pList->data);
            if (pList == pListEnd) {
                break;
            }
        }
        backup.push_back(tempClause);
        if (p == origin.End()) {
            break;
        }
    }

    if (Dpll(origin, simpleValue)) {
        solution.push_back(simpleValue);
        return true;
    }
//    solution.erase(solution.End());
    origin.Clear();

    if (Dpll(backup, -simpleValue)) {
        solution.push_back(-simpleValue);
        return true;
    }
    return false;
    //remain backup!?
}

auto DpllBack(Formula origin) {
    int simpleValue = findSingle(origin);
    for (; simpleValue != 0;) {
//        Simplify(origin,simpleValue);
        for (auto p = origin.Start();; p = p->next) {
            auto temp = p->data.Start();
            if (temp == NULL) {
                return 0;  //empty clause--No Slution
            }
            if (temp == p->data.End()) {
                //single clause--use it to further simplify
                simpleValue = temp->data;
                break;
            }
            if (p == origin.End()) {
                simpleValue = temp->data;
                break;
            }
        }
    }
}


int main(void) {

    string localFileName;
    localFileName = "True_M2";
    regex pattern(".cnf");
    string localFileNameSelected = regex_replace(localFileName, pattern, "");
    auto f1 = readCNF("../set/" + localFileName);

    auto t1 = chrono::steady_clock::now();
    auto x = Dpll(f1, 0);
    auto t2 = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double >>(t2 - t1);
    cout << x << endl << "Time(s): " << time_span.count() << "" << endl;
    ShowVector(solution);
    if (x == 0) {
        outputSolution(0, "../set/" + localFileNameSelected + ".res", time_span.count() * 1000);
    } else {
        SortSolution(solution);
        outputSolution(solution, "../set/" + localFileNameSelected + ".res", time_span.count() * 1000);
    }


}