//
// Created by lhh on 2022/1/2.
//

#ifndef BOOK_MANAGEMENT_H
#define BOOK_MANAGEMENT_H

#include "assistance.h"

namespace book_management {
    // 显示图书管理界面
    void display_menu();

    // 以图书号获取图书信息
    status get_book_by_id(book_data &book, const int &book_id);

    // 购买图书
    status buy_book(const int &book_id, const int &amount);
}
#endif // BOOK_MANAGEMENT_H
