#include "db.h"
#include <iostream>

void clearCin() {
	string temp;
	getline(cin, temp);
}


Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
	connection_properties["hostName"] = DB_HOST;
	connection_properties["port"] = DB_PORT;
	connection_properties["userName"] = DB_USER;
	connection_properties["password"] = DB_PASS;
	connection_properties["OPT_RECONNECT"] = true;
	

}

Database & Database::getInstance() {
	if (Database::instance == 0) {
		instance = new Database();
	}
	return *instance;
}

Connection * Database::getConnection() {
	try {
		Connection *con = driver->connect(connection_properties);
		con->setSchema(DB_NAME);
		return con;
	} catch (SQLException &e) {
		cout << e.what();
	}
	return 0;
}



void Database::allBookOnStore(){
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement *stmt = con->createStatement();
	ResultSet *rset =  stmt->executeQuery("SELECT * FROM book WHERE Num_Of_Books_In_Stock != 0");
	rset->beforeFirst();
	cout << "Books Currently In Stock:" << endl;

	while (rset->next()) {
		cout << "- " << rset->getString("Book_Name") << ". writing by: " << rset->getString("Book_Author") << "." << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}
void Database::ordersSince() {

	string temp1, temp2;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT count(Oreder_Date) as numoforder FROM orders where Oreder_Date >= ?  and Oreder_Date <=  ? ;");

	cout << "Please Enter Start Date:> ";
	clearCin();
	getline(cin, temp1);
	cout << "Please Enter End Date:> ";
	pstmt->setString(1, temp1);
	getline(cin, temp2);
	pstmt->setString(2, temp2);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << "Number Of Orders Between " << temp1 << " And " << temp2 << " Is: " << rset->getString("numoforder") << endl;



	delete con;
	delete pstmt;
	delete rset;
}
void Database::allopenorders() {

	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT * FROM orders  WHERE Status != 'Delivered';");

	rset->beforeFirst();
	cout << "Open Orders:" << endl;

	while (rset->next()) {
		cout << "Order Number: " << rset->getUInt("Order_ID") << ". Order_Date: " << rset->getString("Oreder_Date") << ". Status: " << rset->getString("Status") << "." << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void Database::allClients() {
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT * FROM customer;");

	rset->beforeFirst();
	cout << "Clients:" << endl;

	while (rset->next()) {
		cout << "Costumer ID: " << rset->getUInt("Customer_ID") << " Client Name: " << rset->getString("First_Name") << " " << rset->getString("Last_Name") << "  Phone Number: ";
		cout << rset->getString("Phone") << "." << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void Database::allSuppliers() {
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement *stmt = con->createStatement();
	ResultSet *rset = stmt->executeQuery("SELECT * FROM supplier;");

	rset->beforeFirst();
	while (rset->next()) {
		cout << "Supplier Number: " << rset->getUInt("Supplier_ID") << ".\tSupplier Name: ";
		cout << rset->getString("First_Name") << " " << rset->getString("Last_Name")  <<"."<< endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void Database::dealsBeetweenDates() {
	string temp;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;	
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transactions WHERE Transaction_Date>=? and Transaction_Date<?;");

	cout << "Please Enter Start Date:> ";
	cin >> temp;
	pstmt->setString(1, temp);

	cout << "Please Enter End Date:> ";
	cin >> temp;
	pstmt->setString(2, temp);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	while (rset->next()) {
		cout << "Deal Number: " << rset->getUInt("Transaction_Num") << ". \tDeal Date: "
			<< rset->getString("Transaction_Date") << "." << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}


void Database::booksInDiscount(){
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	Statement *stmt = con->createStatement();
	rset = stmt->executeQuery("SELECT * FROM book WHERE Global_Discount > 0;");
	rset->beforeFirst();
	while (rset->next()) {

		cout << "- " << rset->getString("Book_Name") << ", By ";
		cout<< rset->getString("Book_Author") << " Is On A " << rset->getDouble("Global_Discount")  << "% Discount" << endl;
	}

	delete con;
	delete stmt;
	delete rset;
}

void Database::BookInStock() {

	string bookName;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM book WHERE Book_Name = ?;");
		
	cout << "Please Enter Book Name:> ";
	clearCin();
	getline(cin, bookName);
	pstmt->setString(1, bookName);
	rset = pstmt->executeQuery();

	rset->beforeFirst();
	
	if (rset->next()) {
		int stock = rset->getInt("Num_Of_Books_In_Stock");
		cout << "The Book '" << rset->getString("Book_Name") << "' Is  ";

		if (stock) {
			cout << "In Stock With " << stock << " Units Remaining!" << endl;
		}
		else cout << " NOT In Stock!" << endl;
	}

	else cout << "Book Named '" << bookName << "is missing In The Store..." << endl;

	delete con;
	delete pstmt;
	delete rset;
}

void Database::bookSupplier(){

	string bookName,bookid;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT Book_ID FROM book WHERE Book_Name = ? ;");

	cout << "Please Enter Book Name:> ";
	clearCin();
	getline(cin, bookName);
	pstmt->setString(1, bookName);
	rset=pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	bookid= rset->getString("Book_ID");

	pstmt = con->prepareStatement("SELECT supplier.First_Name,supplier.Last_Name,supplier.Phone from supplier join book_supply on supplier.Supplier_ID=book_supply.Supplier_ID where book_supply.Book_ID=?");
	pstmt->setString(1, bookid);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << "Supplier first name: " << rset->getString("First_Name") << " last name: "<< rset->getString("Last_Name")<<"  telephone: "<< rset->getString("Phone") <<endl;

	delete con;
	delete pstmt;
	delete rset;
}

void Database::bookSoldSince() {
	string bookName, bookid,orderdate;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT Book_ID FROM book WHERE Book_Name = ? ;");

	cout << "Please Enter Book Name:> ";
	clearCin();
	getline(cin, bookName);
	pstmt->setString(1, bookName);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	bookid = rset->getString("Book_ID");

	pstmt = con->prepareStatement("SELECT COUNT(Book_ID) as book_count FROM transactions WHERE Book_ID=? and Transaction_Date>=?");
	pstmt->setString(1, bookid);
	cout << "Please Enter Date:> ";
	getline(cin, orderdate);
	pstmt->setString(2, orderdate);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout <<"The book "<< bookName <<" order from "<<orderdate<<" "<<rset->getString("book_count")<<" time"<< endl;

	delete con;
	delete pstmt;
	delete rset;
}

void Database::ordeToSales() {

	string temp1, temp2;
	int counter = 1;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(Status) as paidorder FROM orders WHERE Oreder_Date >= ? and Oreder_Date <=  ? and Status = 'Delivered';");

	cout << "Please Enter Start Date:> ";
	clearCin();
	getline(cin, temp1);
	pstmt->setString(1, temp1);

	cout << "Please Enter End Date:> ";
	getline(cin, temp2);
	pstmt->setString(2, temp2);

	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();

	cout << "Orders That Turned Into A Deal Between: " << temp1 << " And " << temp2 << " is: " << rset->getString("paidorder") << endl;
	return;

	delete con;
	delete pstmt;
	delete rset;
}

void Database::QuarterIncome() {

	string temp1, temp2;
	int quarter, sum = 0;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT sum(cost) from transactions where Transaction_Date>=? and Transaction_Date<?;");

	cout << "Please Enter Year: ";
	clearCin();
	getline(cin, temp1);

	cout << "Please Enter Quarter Number (1-4): ";
	cin >> quarter;

	switch (quarter) {

	case 1: {

		temp2 = temp1 + "-01-01";
		pstmt->setString(1, temp2);
		temp2 = temp1 + "-03-30";
		pstmt->setString(2, temp2);
		break;
	}

	case 2: {
		temp2 = temp1 + "-04-01";
		pstmt->setString(1, temp2);
		temp2 = temp1 + "-06-30";
		pstmt->setString(2, temp2);
		break;
	}

	case 3: {
		temp2 = temp1 + "-07-01";
		pstmt->setString(1, temp2);
		temp2 = temp1 + "-09-30";
		pstmt->setString(2, temp2);
		break;
	}

	case 4: {
		temp2 = temp1 + "-10-01";
		pstmt->setString(1, temp2);
		temp2 = temp1 + "-12-30";
		pstmt->setString(2, temp2);
		break;
	}
	}

	rset = pstmt->executeQuery();

	rset->beforeFirst();
	rset->next();

	cout << "Total Profits In Quarter " << quarter << " Of " << temp1 << ": " << rset->getUInt("sum(cost)") << "$." << endl;

	delete con;
	delete pstmt;
	delete rset;
}
void Database::BookToCostumer() {
	
	string customer_id, orderdate;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(Customer_ID) as cus_count FROM transactions WHERE Customer_ID=? and Transaction_Date>=?");

	cout << "Please Enter customer id: ";
	clearCin();
	getline(cin, customer_id);
	pstmt->setString(1, customer_id);
	cout << "Please Enter Date: ";
	getline(cin, orderdate);
	pstmt->setString(2, orderdate);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << "The customer with id " << customer_id << " order from " << orderdate << " " << rset->getString("cus_count") << " time" << endl;

	delete con;
	delete pstmt;
	delete rset;
}
void Database::TopClient() {

	string bookName, customer_id, temp;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(Customer_ID), Customer_ID FROM transactions where Transaction_Date >= ?  GROUP BY Customer_ID order by COUNT(Customer_ID) desc  ;");
	cout << "Please Enter Date: ";
	clearCin();
	getline(cin, temp);
	pstmt->setString(1, temp);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	customer_id = rset->getString("Customer_ID");

	pstmt = con->prepareStatement("SELECT `First_Name`,`Last_Name`,`Phone` FROM `customer` WHERE Customer_ID=?");
	pstmt->setString(1, customer_id);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << "The customer who bought the most books in the store is:\nname: " << rset->getString("first_name") << " " << rset->getString("last_name") << "\nphone number: " << rset->getString("Phone") << endl;

	delete con;
	delete pstmt;
	delete rset;
}







void Database::workersSales() {

	string temp1, temp2;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("select First_Name,Last_Name,sum(cost) from seller INNER join transactions on seller.Seller_ID=transactions.Seller_ID where seller.Seller_ID=? and transactions.Transaction_Date>=? and transactions.Transaction_Date<?");

	
	cout << "Please Enter Seller ID: ";
	clearCin();
	getline(cin, temp1);
	pstmt->setString(1, temp1);
	

	cout << "Please Enter Start Date: ";
	getline(cin, temp1);
	pstmt->setString(2, temp1);

	cout << "Please Enter End Date: ";
	getline(cin, temp2);
	pstmt->setString(3, temp2);

	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << "The Total Sum Of Sales By " << rset->getString("First_Name") << " " << rset->getString("Last_Name") << " Between " << temp1 << " And " << temp2 << " Is: " << rset->getUInt("sum(cost)") << "$." << endl;


	delete con;
	delete pstmt;
	delete rset;

}

void Database::SupplierMostOrder() {
	string bookName, customer_id, temp;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(Supplier_ID), Supplier_ID FROM orders where Oreder_Date >= ?  GROUP BY Supplier_ID order by COUNT(Supplier_ID) desc  ;");
	cout << "Please Enter Date: ";
	clearCin();
	getline(cin, temp);
	pstmt->setString(1, temp);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	customer_id = rset->getString("Supplier_ID");

	pstmt = con->prepareStatement("SELECT `First_Name`,`Last_Name`,`Phone` FROM `supplier` WHERE Supplier_ID=?");
	pstmt->setString(1, customer_id);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << "The supplier who order from the most books in the store is:\nname: " << rset->getString("first_name") << " " << rset->getString("last_name") << "\nphone number: " << rset->getString("Phone") << endl;

	delete con;
	delete pstmt;
	delete rset;
}

void Database::CostumerTotalDiscount() {

	string temp,temp2;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT sum(Book_Price)-sum(cost) as disc from transactions join book where book.Book_ID=transactions.Book_ID and transactions.Customer_ID=? and transactions.Transaction_Date >= ?  ;");
	cout << "Please Enter Costumer id: ";
	clearCin();
	getline(cin, temp2);
	pstmt->setString(1, temp2);
	cout << "Please Enter A Date: ";
	getline(cin, temp);
	pstmt->setString(2, temp);


	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << temp2 << " Has Received A Total Discount Of " << rset->getUInt("disc") << "$ Since " << temp << "." << endl;
	

	delete con;
	delete pstmt;
	delete rset;

}

void Database::top10Books() {
	
	string temp1, temp2;
	int counter = 1;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("select count(Book_ID),Book_ID from transactions where Transaction_Date>=? and Transaction_Date < ? group by (Book_ID) order by (count(Book_ID)) desc limit 10 ;");

	cout << "Please Enter Start Date: ";
	clearCin();
	getline(cin, temp1);
	pstmt->setString(1, temp1);

	cout << "Please Enter End Date: ";
	getline(cin, temp2);
	pstmt->setString(2, temp2);

	rset = pstmt->executeQuery();

	if (rset->rowsCount() == 0) {
		 cout << "Invaid Dates Or No Deals Where Found Between Given Dates." << endl;
		 return;
	}

	rset->beforeFirst();
	cout << "Top Books Sold Between " << temp1 << " And " << temp2 << " Are:" << endl;

	while (rset->next()) {
		cout << counter << ") " << rset->getString("Book_ID") << ", Selling " << rset->getString("count(Book_ID)") << " Books." << endl;
		++counter;
	}
	

	delete con;
	delete pstmt;
	delete rset;
}
void Database::NewCostumer() {

	string temp;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT count(Customer_ID) as newjoined FROM customer WHERE Join_Date >= ?;");

	cout << "Please Enter Date: ";
	clearCin();
	getline(cin, temp);
	pstmt->setString(1, temp);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset->next();
	cout << rset->getString("newjoined") << " new customers as added from " << temp << endl;

	delete con;
	delete pstmt;
	delete rset;
}
void Database::supplierPurchases() {

	string temp1, temp2, supplier;
	int counter = 1, sum = 0;
	Connection *con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet *rset;
	PreparedStatement *pstmt = con->prepareStatement("SELECT sum(Book_Price) FROM orders join book WHERE orders.Book_ID= book.Book_ID and Oreder_Date<=? and Oreder_Date > ? and Supplier_ID=?;");
	clearCin();
	cout << "Please Enter Start Date: ";
	getline(cin, temp1);
	pstmt->setString(2, temp1);
	cout << "Please Enter End Date: ";
	getline(cin, temp2);
	pstmt->setString(1, temp2);
	cout << "Please Enter Supplier Number: ";
	
	getline(cin, supplier);
	pstmt->setString(3, supplier);

	rset = pstmt->executeQuery();
	rset->beforeFirst();
	rset ->next();

	cout << "\nTotal Purchases From supplier number " << supplier << " Between " << temp1 << " And " << temp2 << " is: " <<rset->getUInt("sum(Book_Price)")<<"$."<< endl;


	delete con;
	delete pstmt;
	delete rset;
}

