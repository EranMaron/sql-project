#ifndef _DB_H
#define _DB_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace sql;
using namespace std;
#define DB_NAME "book_store"
#define DB_HOST "tcp://127.0.0.1/"
#define DB_PORT 3306
#define DB_USER "zahor"
#define DB_PASS "1234"

class Database {
private:
	// singleton instance
	static Database *instance;

	Driver *driver;
	ConnectOptionsMap connection_properties;
	Database();
public:
	static Database& getInstance();

	Connection *getConnection();

	virtual ~Database() {}
	void QuarterIncome();
	void allBookOnStore();
	void allopenorders();
	void allClients();
	void allSuppliers();
	void dealsBeetweenDates();
	void booksInDiscount();
	void BookInStock();
	void bookSupplier();
	void BookToCostumer();
	void NewCostumer();
	void ordersSince();
	void workersSales();
	void SupplierMostOrder();
	void TopClient();
	void CostumerTotalDiscount();
	void top10Books();
	void supplierPurchases();
	void bookSoldSince();
	void ordeToSales();
	
};



#endif