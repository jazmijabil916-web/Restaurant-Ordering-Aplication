#include <iostream>
#include <iomanip>
using namespace std;

#define TAX_RATE 0.05

//List food and drinks
string menuName[14] = {"Chicken Chop", "Grill Chicken Chop", "Lamb Chop", "Fish n Chip","Mushroom Pasta", "French Fries" ,"Meatball", "Chocolate Shake" , "Green Tea","Ice Latte","Ice Mocha","Apple Juice","Orange Juice","Lemon Ice"};
double price[14] = {15.90, 18.90, 23.90, 20.90, 19.90 , 8.90 , 8.90 , 8.90 , 6.90 , 6.90 , 6.90 , 5.90 , 5.90 , 4.90};

// Semua function yang digunakan
void menuDisplay();
void reserveTable();
void placeOrder();
void modifyOrder();
double calculateBill(int orderbil[], int quantity[], int count);
void printReceipt();
void clearOrder();
void releaseTable();

// amount of order you can add
int orderbil[100];
int quantity[100];
int orderCount = 0;

// Menu list
void menuDisplay() {
    cout << "\n=========================== MENU ============================================\n\n";
    cout << left << setw(25) << "FOOD" << " \t| DRINK\n";
    cout << "------------------------------------------------------------------------------\n";

    cout << left << setw(25) << "1. Chicken Chop -RM15.90" << "\t| 8. Chocolate Shake -RM8.90\n";
    cout << left << setw(25) << "2. Grill Chicken Chop -RM18.90" << "\t| 9. Green Tea -RM6.90\n";
    cout << left << setw(25) << "3. Lamb Chop -RM23.90" << "\t| 10. Ice Latte -RM6.90\n";
    cout << left << setw(25) << "4. Fish n Chip -RM20.90" << "\t| 11. Ice Mocha -RM6.90\n";
    cout << left << setw(25) << "5. Mushroom Pasta -RM19.90" << "\t| 12. Apple Juice -RM5.90\n";
    cout << left << setw(25) << "6. French Fries -RM8.90" << "\t| 13. Orange Juice -RM5.90\n";
    cout << left << setw(25) << "7. Meatball -RM8.90" << "\t| 14. Lemon Ice -RM5.90\n";

    cout << "------------------------------------------------------------------------------\n";
}
//Table reserved
bool table[12] = {false};
int currentTable = -1;

void reserveTable() {
    cout << "\n===== TABLE STATUS =====\n";
    for(int i = 0; i < 12; i++) {
        cout << "Table " << i+1 << ": ";
        if (table[i]==false)
        cout <<"Available\n";
        else
        cout <<"Booked\n";
    }

    int choice;
    cout << "Pilih meja (1-12): ";
    cin >> choice;

    if(choice < 1 || choice > 12) {
        cout << "Input invalid,Please try number 1 to 12 only.\n";
        return;
    } 
    if(table[choice-1]) {
        cout << "The table already been reserved!Please choose another table.\n";
    } else {
        table[choice-1] = true;
        currentTable = choice-1;
        cout << "Reservation Completed (Table " << choice << ")\n";
  }
}

// Place order based on menu price after reserve table
void placeOrder() {
    if(currentTable == -1) {
        cout << "Please reserve your table first before continue order.\n";
        return;
    }

    int choice, qnty;
    char addOrder;

    do {
        menuDisplay();

        cout << "Pilih menu (1-14): ";
        cin >> choice;

        if(choice < 1 || choice > 14) {
            cout << "The menu does not exist\n";
            continue;
        }

        cout << "Quantity: ";
        cin >> qnty;

        if(qnty <= 0) {
            cout << "Input invalid,the quantity must be more than 0.\n";
            continue;
        }

        orderbil[orderCount] = choice - 1;
        quantity[orderCount] = qnty;
        orderCount++;

        cout << "Order has been added.\n";

        cout << "Added more menu? (Y/N): ";
        cin >> addOrder;

    } while(addOrder == 'y' || addOrder == 'Y');
}

// MODIFY ORDER AND QUANTITY OF MENU
void modifyOrder() {
    if(orderCount == 0) {
        cout << "There is no order to be modify.\n";
        return;
    }

    cout << "\n===== MODIFY ORDER =====\n";
    for(int i = 0; i < orderCount; i++) {
        cout << i+1 << ". " << menuName[orderbil[i]]
             << " x" << quantity[i] << endl;
    }

    int choice;
    cout << "Choose the menu: ";
    cin >> choice;

    if(choice < 1 || choice > orderCount) {
        cout << "Invalid choice,please try again\n";
        return;
    }

    cout << "Enter new quantity or 0 to delete the menu: ";
    cin >> quantity[choice-1];

    if(quantity[choice-1] == 0) {
        for(int i = choice-1; i < orderCount-1; i++) {
            orderbil[i] = orderbil[i+1];
            quantity[i] = quantity[i+1];
        }
        orderCount--;
        cout << "The menu has been removed.\n";
    } else {
        cout << "Done, order has been updated\n";
    }
}

// CALCULATE BILL 
double calculateBill(int orderbil[], int quantity[], int count) {
    double total = 0;
    for(int i = 0; i < count; i++) {
        total += price[orderbil[i]] * quantity[i];
    }
    return total;
}

// RECEIPT
void printReceipt() {
    if(orderCount == 0) {
        cout << "There is no order.\n";
        return;
    }

    double total = calculateBill(orderbil, quantity, orderCount);
    double tax = total * TAX_RATE;
    double grandTotal = total + tax;

    cout << "\n===== RECEIPT =====\n";
    cout << "Table: " << currentTable+1 << endl;

    for(int i = 0; i < orderCount; i++) {
        cout << menuName[orderbil[i]]
             << " x" << quantity[i]
             << " = RM" << price[orderbil[i]] * quantity[i] << endl;
    }

    cout << "----------------------\n";
    cout << "Subtotal: RM" << total << endl;
    cout << "Service Tax (5%): RM" << tax << endl;
    cout << "Total: RM" << grandTotal << endl;

    clearOrder();
    releaseTable();
}

// RESET
void clearOrder() {
    orderCount = 0;
}

void releaseTable() {
    if(currentTable != -1) {
        table[currentTable] = false;
        currentTable = -1;
        cout << "The table has been cleared.\n";
    }
}

// Main (User interface)
int main() {
    int option;
    cout<<"~~WELCOME TO D'CRUISE KITCHEN~~"<<endl;

    do {
        cout << "\n***** RESTAURANT SYSTEM *****\n";
        cout << "1. Menu Display\n";
        cout << "2. Reserve Table\n";
        cout << "3. Place Order\n";
        cout << "4. Modify Order\n";
        cout << "5. Print Receipt\n";
        cout << "6. Exit\n";
        cout << "Choose: ";
        cin >> option;

        switch(option) {
            case 1: menuDisplay(); break;
            case 2: reserveTable(); break;
            case 3: placeOrder(); break;
            case 4: modifyOrder(); break;
            case 5: printReceipt(); break;
            case 6: cout << "Thank you,Please come again.\n"; break;
            default: cout << "INPUT INVALID!!,PLEASE TRY AGAIN.\n";
        }

    } while(option != 6);

    return 0;
}
