#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main()
{
    // Initialize variables to store customer information
    int customer_id;
    string customer_name;
    string customer_email;
    string customer_region;
    string customer_phone;

    // Get input from user
    cout << "Enter customer ID: ";
    cin >> customer_id;
    cout << "Enter customer name: ";
    cin >> customer_name;
    cout << "Enter customer email: ";
    cin >> customer_email;
    cout << "Enter customer region: ";
    cin >> customer_region;
    cout << "Enter customer phone number: ";
    cin >> customer_phone;

    try {
        // Create a connection to the MySQL database
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;

        driver = get_driver_instance();
        con = driver->connect("hostname", "username", "password");
        con->setSchema("database_name");

        // Insert customer information into the database
        stmt = con->createStatement();
        stmt->execute("INSERT INTO customers (id, name, email, region, phone) VALUES ('" + to_string(customer_id) + "', '" + customer_name + "', '" + customer_email + "', '" + customer_region + "', '" + customer_phone + "')");

        // Close the connection
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    return 0;
}