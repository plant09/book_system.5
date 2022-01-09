#include "book_management.h"
#include "book_manager.h"

// 显示图书管理界面
void book_management::display_menu()
{
	book_manager manager;
	manager.display_menu(manager);
}

// 以图书号获取图书信息
status book_management::get_book_by_id(book_data &book, const int &book_id)
{
	book_manager manager;
	return manager.get_book_by_id(book, book_id);
}

// 购买图书
status book_management::buy_book(const int &book_id, const int &amount)
{
	book_manager manager;
	return manager.buy_book(book_id, amount);
}
