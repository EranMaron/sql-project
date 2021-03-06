#include "db.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	Database &db = Database::getInstance();
	
	int n = 0;
	while (n != 99) {
		cout << "\nBook store manu:\n";
		cout << "1.show all book in stock\n";
		cout << "2.show all open orders\n";
		cout << "3.show all store clients\n";
		cout << "4.show all store suppliers\n";
		cout << "5.show all deals beetween 2 dates\n";
		cout << "6.show all book in disocunt(global)\n";
		cout << "7.check if book in stock\n";
		cout << "8.show the supplier of book\n";
		cout << "9.show how many copies sell from book since date\n";
		cout << "10.show how many book costumer buy from date\n";
		cout << "11.show the costumer that buy the most book from date\n";
		cout << "12.show the supplier that order from him the most since date\n";
		cout << "13.show all book orders beetween two dates\n";
		cout << "14.show all book orders beetween two dates thet became sales\n";
		cout << "15.the discount that get costumer since date\n";
		cout << "16.show the store income during Quarter\n";
		cout << "17.show how many new costumer since date\n";
		cout << "18.show how much the store order from supplier beetween dates\n";
		cout << "19.show how much seller sales beetween dates\n";
		cout << "20.show the 10 most sallers beetween dates\n";
		cout << "please enter your choice: \n";
		cin >> n;

		switch (n) {

			case 99: {
				continue;
			}

			case 1: {
				db.allBookOnStore();
				cin.clear();
				break;
			}

			case 2: {	
				db.allopenorders();
				cin.clear();
				break;
			}

			case 3: {
				db.allClients();
				cin.clear();
				break;
			}

			case 4: {
				db.allSuppliers();
				cin.clear();
				break;
			}

			case 5: {
				db.dealsBeetweenDates();
				cin.clear();
				break;
			}

			case 6: {
				db.booksInDiscount();
				cin.clear();
				break;
			}

			case 7: {
				db.BookInStock();
				cin.clear();
				break;
			}

			case 8: {
				db.bookSupplier();
				cin.clear();
				break;
			}

			case 9: {
				db.bookSoldSince();
				cin.clear();
				break;
			}

			case 10: {
				db.BookToCostumer();
				cin.clear();
				break;
			}

			case 11: {
				db.TopClient();
				cin.clear();
				break;
			}
			case 12: {
				db.SupplierMostOrder();
				cin.clear();
				break;
			}

			case 13: {
				db.ordersSince();
				cin.clear();
				break;
			}

			case 14: {
				db.ordeToSales();
				cin.clear();
				break;
			}

			case 15: {
				db.CostumerTotalDiscount();
				cin.clear();
				break;
			}

			case 16: {
				db.QuarterIncome();
				cin.clear();
				break;
			}

			case 17: {
				db.NewCostumer();
				cin.clear();
				break;
			}
			case 18: {
				db.supplierPurchases();
				cin.clear();
				break;
			}

			case 19: {
				db.workersSales();
				cin.clear();
				break;
			}

			case 20: {
				db.top10Books();
				cin.clear();
				break;
			}

			default: {
				cout << "wrong choice...." << endl;
				cout << "please choose number beetween 1-20 only-99 for exit";
				n = 0;
				cin.clear();
				break;
			}




		}

		cout << "\nPress any number to return the Main Menu\n" << endl;
		cin >> n;
		cin.clear();
		n = 0;
		


	}
	return 0;
}

