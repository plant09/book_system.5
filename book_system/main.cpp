#include"assistance.h"
#include"shopping_cart.h"
#include"book_management.h"

int main()
{
    while (true) {
        system("cls");
        cout << "1. Favorites" << endl;
        cout << "2. Shopping Cart" << endl;
        cout << "3. Book Management" << endl;
        cout << "4. Exit" << endl;
        cout << "Please input your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            //favorites::display_menu();
            break;
        case 2:
            shopping_cart::display_menu();
            break;
        case 3:
            book_management::display_menu();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
            break;
        }
    }
}