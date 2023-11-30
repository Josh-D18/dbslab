#include <iostream>
#include <occi.h>

using namespace oracle::occi;
using namespace std;

int main() {
    // OCCI Variables
    Environment* env = nullptr;
    Connection* conn = nullptr;
    Statement* stmt = nullptr;
    ResultSet* rs = nullptr;

    /* Used Variables */
    string user = "dbs211_233ncc04";
    string pass = "69502578";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

    try {
        // Create OCCI Environment
        env = Environment::createEnvironment(Environment::DEFAULT);

        // Create Database Connection
        conn = env->createConnection(user, pass, constr);

     
        stmt = conn->createStatement("SELECT EMPLOYEENUMBER, FIRSTNAME, LASTNAME, PHONE, EXTENSION FROM EMPLOYEES E JOIN OFFICES O ON E.OFFICECODE = O.OFFICECODE WHERE O.CITY = 'San Francisco' ORDER BY EMPLOYEENUMBER");
        rs = stmt->executeQuery();
        cout << "Report 1 (Employee Report):" << endl;
        if (!rs->next()) {
            cout << "ResultSet is empty." << endl;
        }
        else {
            do {
                cout << "Employee Number: " << rs->getInt(1) << " First Name: " << rs->getString(2)
                    << " Last Name: " << rs->getString(3) << " Phone Number: " << rs->getString(4)
                    << " Extension: " << rs->getString(5) << endl;
            } while (rs->next());
        }

        stmt = nullptr;


        stmt = conn->createStatement("SELECT employeeNumber, firstName, lastName, phone, extension FROM employees e, offices o WHERE employeeNumber IN(SELECT e1.reportsTo FROM employees e1 LEFT OUTER JOIN employees e2 ON e1.reportsTo = e2.employeeNumber) and e.officeCode = o.officeCode ORDER BY employeeNumber");
        rs = stmt->executeQuery();
        cout << endl << endl;
        cout << "Report 2 (Manager Report):" << endl;
        if (!rs->next()) {
            cout << "ResultSet is empty." << endl;
        }
        else {
            do {
                cout << "Employee Number: " << rs->getInt(1) << " First Name: " << rs->getString(2) << " Last Name: " << rs->getString(3)
                    << " Phone Number: " << rs->getString(4) << " Extension: " << rs->getString(5) << endl;
            } while (rs->next());
        }



        stmt = nullptr; 

        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
    }

    return 0;
}
