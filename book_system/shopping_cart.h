#ifndef SHOPPING_CART
#define SHOPPING_CART

#include"cart.h"

cart _shopping_cart;

namespace shopping_cart {
   
    void display_menu() {
        _shopping_cart.read();
        _shopping_cart.display_menu();
        _shopping_cart.write();
    }

    status add_to_cart(const int& book_id, const date& add_to_cart_date, const int& purchase_amount) {
        return _shopping_cart.add_to_cart(book_id, add_to_cart_date, purchase_amount);
    }

}

#endif