#include "book_manager.h"
#include <iostream>
#include "assistance.h"
#include <iomanip>

bool _is_day(const date &date)
{
	if (date.year < 1800 || date.year > 2030 || date.month < 1 || date.month > 12 || date.day < 1 || date.day > 31)
	{
		cout << "亲, 请输入正确的日期哦！！！" << endl;
		return false;
	}
	return true;
}
void _show_book(const book_data &book)
{
	cout << setfill(' ');
	std::cout.flags(std::ios::left);
	cout << "ID:" << setw(5) << book.book_id;
	cout << "书名:" << setw(20) << book.book_name;
	cout << "作者:" << setw(10) << book.author_name;
	cout << "出版社:" << setw(20) << book.publisher_name;
	std::cout.flags(std::ios::right);
	cout << "出版日期:" << book.publish_date.year << '-' << setfill('0') << setw(2) << book.publish_date.month << '-' << setfill('0') << setw(2) << book.publish_date.day << "  ";
	std::cout.flags(std::ios::left);
	cout << setfill(' ');
	cout << "价格:" << fixed << setprecision(2) << book.price*(float)0.01 << "  ";
	cout << "库存:" << setw(5) << book.amount;
	std::cout.flags(std::ios::right);
	cout << "入库日期:" << book.storage_date.year << '-' << setfill('0') << setw(2) << book.storage_date.month << '-' << setfill('0') << setw(2) << book.storage_date.day << endl;
}

book_manager::book_manager(): bookCount(0)
{
	book_data _book;
	ifstream inf("library.dat", ios::in | ios::binary);
	if (!inf)
	{
		cout << "no file!!!" << endl;
		return;
	}

	inf.read(reinterpret_cast<char*>(&_book), sizeof(_book));

	while(!inf.eof())
	{
		books.insert(_book); bookCount++;
		inf.read(reinterpret_cast<char*>(&_book), sizeof(_book));
	}
}

book_manager::~book_manager()
{
	books.in_storage();
}

bool book_manager::add_a_book(book_data &book)
{
	if (books.insert(book))
	{
		bookCount++;
		return true;
	}
	else
	{
		cout << "id为" << book.book_id << "的书已经存在" << endl;
	}
	return false;
}

int book_manager::add_books()
{
	int count = 0;
	char name[20];
	cout << "请输入录入的二进制文件名：";
	cin >> name;
	ifstream inf(name, ios::in | ios::binary);
	if (!inf)
	{
		cout << "no file!!!" << endl;
		return 0;
	}
	book_data _book;
	inf.read(reinterpret_cast<char*>(&_book), sizeof(_book));

	while(!inf.eof())
	{
		if (books.insert(_book))
		{
			bookCount++;
			count++;
		}
		else
		{
			cout << "id为" << _book.book_id << "的书已经存在" << endl;
		}
		inf.read(reinterpret_cast<char*>(&_book), sizeof(_book));
	}
	cout << "录入成功！" << endl;
	cout << "已成功录入" << count << "本图书";
	return count;
}

bool book_manager::delete_books(int left, int right)
{
	if (left > right || left < 1 || right < 1)
	{
		cout << "亲，请不要捉弄可爱的小灰羊哦~" << endl;
		return false;
	}

	book_data book;
	for (int id = left; id <= right; id++)
	{
		if (books.delete_books_by_ID(id, book))
		{
			bookCount--;
			cout << "已删除ID为" << id << "的书籍" << endl;
		}
	}
	return true;
}

int book_manager::delete_one_day_books(date &date)
{
	if (!_is_day(date)) return 0;	//判断日期是否合法

	int count = 0;
	if (count = books.delete_books_by_date(date))	//直接利用函数
	{
		bookCount -= count;
		return count;
	}
	return 0;
}

bool book_manager::show_books_on_ID(int left, int right)
{
	if (left > right || left < 1 || right < 1)
	{
		cout << "亲，请不要捉弄可爱的小灰羊哦~" << endl;
		return false;
	}

	book_data book;
	bool flag = true;
	for (int id = left; id <= right; id++)
	{
		if (books.get_books_by_ID(id, book))
		{
			if (flag)
			{
				cout << "成功找到该书籍:" << endl;
				flag = false;
			}
			show_book(book);
		}
	}
	if (flag)
	{
		cout << "未在该范围内找到任何书籍！！！" << endl;
		return false;
	}
	return true;
}

bool book_manager::show_books_on_date(date &lD, date &rD)
{
	if (!_is_day(lD) || !_is_day(rD)) return false;	//判断日期是否合法

	if (lD > rD)	//范围是否存在
		return false;

	book_data book[100];
	for (date day = lD; day <= rD; ++day)
	{
		int count = 0;
		count = books.get_books_by_date(day, book);
		if (count > 0)
		{
			cout << day.year << '-' << day.month << '-' << day.day << "有" << count << "本图书:" << endl;
			for (int i = 0; i < count; i++)
			{
				show_book(book[i]);
			}
		}
	}
	return true;
}

void book_manager::show_books_on_author(char name[AUTHOR_NAME_LENGTH])
{
	book_data book[200];
	int count = 0;
	if (count = books.get_books_by_author(name, book))
	{
		cout << "书库中共存有" << name << "的" << count << "本书:" << endl;
		for (int i = 0; i < count; i++)
		{
			show_book(book[i]);
		}
		return;
	}
	cout << "抱歉亲，书库中没有找到作者" << name << "的书籍哦！" << endl;
}


status book_manager::get_book_by_id(book_data &book, const int id)
{
	if (id < 1) return FAIL;

	if (books.get_books_by_ID(id, book))
		return SUCCESS;
	return NOT_PRESENT;
}

status book_manager::buy_book(const int &id, const int &amount)
{
	if (id < 1) return FAIL; //id非法
	if (amount <= 0) return FAIL; //amount非法

	book_data book;
	book_data book_temp;
	if (books.get_books_by_ID(id, book))
	{
		if (book.amount < amount)
			return RANGE_ERROR;	//书不够
		else
		{
			book.amount -= amount;
			books.delete_books_by_ID(id, book_temp);
			books.insert_old_book(book);
			return SUCCESS;	//成功买走
		}
	}

	return NOT_PRESENT;
}

void book_manager::display_menu(book_manager &manager)
{
	int in = 0;
	while(in >= 0 && in <= 10)
	{
	system("cls");
	cin.clear();
	std::cout << "----------------------------" << std::endl;
	std::cout << "-欢迎来到弹灰羊书库管理界面-" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "书库中共存有" << bookCount << "本图书" << endl;
	std::cout << "1.入库图书" << std::endl;
	std::cout << "2.删除图书" << std::endl;
	std::cout << "3.显示图书" << std::endl;
	std::cout << "4.返回主菜单" << std::endl;
	std::cout << "请输入：";
	int in = 0;
	std::cin >> in;
	cin.clear();
	cin.ignore(1024, '\n');
	switch (in)
	{
		case 1: {
				while (true)
				{
					std::cout << "1.逐个录入" << std::endl << "2.批量录入" << std::endl << "3.返回上一级" << std::endl;
					std::cout << "请输入：";
					in = 0;
					std::cin >> in;
					cin.clear();
					cin.ignore(1024, '\n');
					system("clear");
					if (in == 1)
					{
						book_data book;
						cin_book(book);
						show_book(book);
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "你确定录入该书吗？('y' or 'n')" << endl << "请输入:";
						char ch;
						cin >> ch;
						if (ch == 'y')
						{
							if (manager.add_a_book(book))
								cout << "操作完成!" << endl; 
							else
							{
								cout << "操作失败!" << endl;
								cout << "可能是该书已经存在，建议亲先删除该书后在录入哦。" << endl;
							}
						}
						else
						{
							cout << "已成功为您取消录入^_^|~" << endl;
						}
					}
					else if (in == 2)
					{
						if (manager.add_books())
							cout << "操作完成!" << endl; 
						else
						{
							cout << "操作失败!" << endl;
						}
					}
					else if (in == 3)
					{
						break;
					}
				}
				break;
			}
		case 2:	{
				while (true)
				{
					std::cout << "1.按书号删除" << std::endl << "2.按日期删除" << std::endl << "3.返回上一级" << std::endl;
					std::cout << "请输入：";
					in = 0;
					std::cin >> in;
					system("clear");
					cin.clear();
					cin.ignore(1024, '\n');
					if (in == 1)
					{
						std::cout << "请输入书号范围(下界 上界)：";
						int left = -1, right = -1;
						std::cin >> left >> right;
						cin.clear();
						cin.ignore(1024, '\n');
						if (left <= right)
						{
						       	manager.show_books_on_ID(left, right);
							cout << "亲，您确定要删除这些书籍吗?('y' or 'n')" << endl << "请输入：";
							char ch;
							cin >> ch;
							cin.clear();	//清空缓存区
							cin.ignore(1024, '\n');
							if (ch == 'y')
							{
								if (manager.delete_books(left, right))
									cout << "操作完成!" << endl; 
								else
									cout << "操作失败!" << endl;
							}
							else
							{
								cout << "已成功为您取消删除^_^|~" << endl;
							}
						}
						else
							std::cout << "非法范围！" << std::endl;
					}
					else if (in == 2)
					{
						date _date;
						_date.year = 0;	//防止胡乱输入
						_date.month = 1;
						_date.day = 1;
						std::cout << "请输入删除日期(年 月 日)：";
						std::cin >> _date.year;
						std::cin >> _date.month;
						std::cin >> _date.day;
						cin.clear();
						cin.ignore(1024, '\n');
						int count = 0;
						manager.show_books_on_date(_date, _date);
						cout << "亲，您确定要删除这些书籍吗?('y' or 'n')" << endl << "请输入：";
						char ch;
						cin >> ch;
						cin.clear();
						cin.ignore(1024, '\n');
						if (ch == 'y')
						{
							if (count = manager.delete_one_day_books(_date))
							{
								cout << "亲，已为您删除了" << count << "本书籍。" << endl;
							}
							else
							{
								cout << "操作失败!" << endl;
								cout << "可能是该日期没有任何书籍哦。" << endl;
							}
						}
						else
						{
							cout << "已成功为您取消删除^_^|~" << endl;
						}
					}
					else if (in == 3)
					{
						break;
					}
				}
				break;
			}
		case 3:	{
				bool flag = true;
				while (flag)
				{
					std::cout << "1.全部展示" << std::endl;
					std::cout << "2.按书号展示" << std::endl;
					std::cout << "3.按日期展示" << std::endl;
					std::cout << "4.按作者展示" << std::endl;
					std::cout << "5.返回上一级" << std::endl;
					std::cout << "请输入：";
					in = 0;
					std::cin >> in;
					cin.clear();
					cin.ignore(1024, '\n');
					switch (in)
					{
					case 1:{
						       cout << "已展示全部的" << bookCount << "本书籍：" << endl;
						       books.traverse(_show_book);
						       break;
					       }
					case 2:{
							std::cout << "请输入书号范围(下界 上界)：";
							int left = 0, right = 0;
							std::cin >> left >> right;
							cin.clear();
							cin.ignore(1024, '\n');
							if (left <= right)
							{
						       		manager.show_books_on_ID(left, right);
							}
							else
							std::cout << "非法范围！" << std::endl;
						       	break;
					       }
					case 3:{
							date date_1, date_2;

							date_1.year = 0;	//防止胡乱输入
							date_1.month = 1;
							date_1.day = 1;
							date_2.year = 0;	//防止胡乱输入
							date_2.month = 1;
							date_2.day = 1;

							std::cout << "请输入展示起始日期(年 月 日)：";
							std::cin >> date_1.year;
							std::cin >> date_1.month;
							std::cin >> date_1.day;
							cin.clear();
							cin.ignore(1024, '\n');
							std::cout << "请输入展示截至日期(年 月 日)：";
							std::cin >> date_2.year;
							std::cin >> date_2.month;
							std::cin >> date_2.day;
							cin.clear();
							cin.ignore(1024, '\n');
							manager.show_books_on_date(date_1, date_2);
							break;
					       }
					case 4:{
							char name[AUTHOR_NAME_LENGTH];
						       	std::cout << "请输入作者姓名：";
							std::cin >> name;
							cin.clear();
							cin.ignore(1024, '\n');
						       	show_books_on_author(name);
							break;
					       }
					case 5: flag = false;
					}
				}
				break;
			}
		case 4: return;
	}
	}
}

void book_manager::cin_book(book_data &book)
{
	float price = 0;
	std::cout << "请输入图书号：";
	std::cin >> book.book_id;
	cin.clear();
	cin.ignore(1024, '\n');
	std::cout << "请输入书名：";
	std::cin >> book.book_name;
	cin.clear();
	cin.ignore(1024, '\n');
	std::cout << "请输入作者：";
	std::cin >> book.author_name;
	cin.clear();
	cin.ignore(1024, '\n');
	std::cout << "请输入出版社：";
	std::cin >> book.publisher_name;
	cin.clear();
	cin.ignore(1024, '\n');
	std::cout << "请输入出版日期(年 月 日)：";
	std::cin >> book.publish_date.year;
	std::cin >> book.publish_date.month;
	std::cin >> book.publish_date.day;
	cin.clear();
	cin.ignore(1024, '\n');
	std::cout << "请输入价格：";
	std::cin >> price;
	cin.clear();
	cin.ignore(1024, '\n');
	book.price = (int)(price * 100);
	std::cout << "请输入入库的数量：";
	std::cin >> book.amount;
	cin.clear();
	cin.ignore(1024, '\n');
	std::cout << "请输入入库日期(年 月 日)：";
	std::cin >> book.storage_date.year;
	std::cin >> book.storage_date.month;
	std::cin >> book.storage_date.day;
	cin.clear();
	cin.ignore(1024, '\n');
}

void book_manager::show_book(const book_data &book)
{
	cout << setfill(' ');
	std::cout.flags(std::ios::left);
	cout << "ID:" << setw(5) << book.book_id;
	cout << "书名:" << setw(20) << book.book_name;
	cout << "作者:" << setw(10) << book.author_name;
	cout << "出版社:" << setw(20) << book.publisher_name;
	std::cout.flags(std::ios::right);
	cout << "出版日期:" << book.publish_date.year << '-' << setfill('0') << setw(2) << book.publish_date.month << '-' << setfill('0') << setw(2) << book.publish_date.day << "  ";
	std::cout.flags(std::ios::left);
	cout << setfill(' ');
	cout << "价格:" << fixed << setprecision(2) << book.price*(float)0.01 << "  ";
	cout << "库存:" << setw(5) << book.amount;
	std::cout.flags(std::ios::right);
	cout << "入库日期:" << book.storage_date.year << '-' << setfill('0') << setw(2) << book.storage_date.month << '-' << setfill('0') << setw(2) << book.storage_date.day << endl;
}
