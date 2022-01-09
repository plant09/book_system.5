#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include"assistance.h"
#include"hash_table.h"

class book_manager
{
public:
	book_manager();
	~book_manager();

	bool add_a_book(book_data &book);
	int add_books();
	bool delete_books(int left, int right);
	int delete_one_day_books(date &date);
	bool show_books_on_ID(int left, int right);
	bool show_books_on_date(date &lD, date &rD);
	void show_books_on_author(char name[AUTHOR_NAME_LENGTH]);

	void display_menu(book_manager &manager);
	status get_book_by_id(book_data &book, const int id);
	status buy_book(const int &id, const int &amount);
private:
	void cin_book(book_data &book);
	void show_book(const book_data &book);

	hash_table books;
	int bookCount;
};

#endif
