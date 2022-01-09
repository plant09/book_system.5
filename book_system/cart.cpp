#include "cart.h"

date cart::set_date()
{
	int year = 0, month = 0, day = 0;
	string date_str;

	cout << "日期(xxxx.xx.xx):";
	cin >> date_str;

	int flag1 = 0;
	for (int i = 0; i < date_str.size(); i++)
	{

		if (date_str[i] == '.') flag1++;
		else
			switch (flag1)
			{
			case 0:
				year = year * 10 + date_str[i] - '0';
				break;
			case 1:
				month = month * 10 + date_str[i] - '0';
				break;
			case 2:
				day = day * 10 + date_str[i] - '0';
				break;
			}
	}

	int flag2 = 1;
	if (flag1 != 2)flag2 = 0;
	else if (month <= 0 || month > 12) flag2 = 0;
	else if (day <= 0 || day > 31)flag2 = 0;
	else if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && day > 30) flag2 = 0;
	else if ((month == 2 && day > 29) || (year % 4 == 0 && month == 2 && day > 28))flag2 = 0;

	if (flag2 != 1)
	{
		cout << "日期非法！请重新输入" << endl;
		return set_date();
	}

	date d;
	d.year = year;
	d.month = month;
	d.day = day;
	return d;
}

BinTreeNode* cart::find_node(const int& book_id)
{
	BinTreeNode* f;
	return  cart.find(book_id, f);
}

void cart::assis_read(ifstream& file,int low,int high)
{
	if (low <= high)
	{
		int mid = (low + high) / 2;
		
		file.seekg(mid * sizeof(book_data), ios::beg);
		book_data book;
		file.read(reinterpret_cast<char*>(&book), sizeof(book));
		cart.insert(book);

		assis_read(file, low, mid - 1);
		assis_read(file, mid +1, high);
	}
}

status cart::read()
{
	ifstream file("cart.dat", ios::in | ios::binary);
	if (!file)
	{
		cout << "no file! write and read will default" << endl;
		return FAIL;
	}
	
	file.seekg(0, ios::end);           //文件定位到文件尾
	int book_num = file.tellg() / sizeof(book_data);   //图书数量=（文件尾-文件头）/book长度

	assis_read(file, 0, book_num - 1);
	return SUCCESS;
}

void cart::assis_write(ofstream& file,BinTreeNode* p)
{
	if (p != nullptr)
	{
		assis_write(file, p->leftChild);

		book_data book = p->data;
		file.write(reinterpret_cast<char*>(&book), sizeof(book_data));
		
		assis_write(file, p->rightChild);
	}
}

status cart::write()
{
	ofstream file("cart.dat", ios::out | ios::binary);
	if (!file)
	{
		cout << "no file! write and read will default" << endl;
		return FAIL;
	}
	
	assis_write(file, cart.get_root());
	return SUCCESS;
}

status cart::query_cart_book(const int& book_id)
{
	BinTreeNode* p;
	p = find_node(book_id);
	if (p != nullptr)
	{
		cout << "图书号：  " << p->data.book_id << endl;
		cout << "书名：    " << p->data.book_name << endl;
		cout << "作者：    " << p->data.author_name << endl;
		cout << "定价：    " << p->data.price*float(0.01) << "元" << endl;
		cout << "出版社：  " << p->data.publisher_name << endl;
		cout << "出版日期：" << p->data.publish_date.year << "." << p->data.publish_date.month << "." << p->data.publish_date.day << endl;
		cout << "购买数量：" << p->data.purchase_amount << endl;
		cout << "加入购物车时间：" << p->data.add_to_cart_date.year << "." << p->data.add_to_cart_date.month << "." << p->data.add_to_cart_date.day << endl;
		return SUCCESS;
	}
	cout << "图书不存在！";
	return NOT_PRESENT;
}

status cart::modify_purchase_num(const int& book_id, const int& book_num)
{
	BinTreeNode* p;
	p = find_node(book_id);
	if (p != nullptr)
	{
		if (book_num <= 0)
		{
			cout << "修改数量非法，如需删除请返回上一层选择删除功能" << endl;
			return RANGE_ERROR;
		}
		else if (book_num > p->data.amount)
		{
			cout << "库存不足，当前库存" << p->data.amount << "本" << endl;
			return RANGE_ERROR;
		}
		else
		{
			this->price_of_all = this->price_of_all + p->data.price * (book_num - p->data.purchase_amount);
			this->amount_of_all_books_of_cart = this->amount_of_all_books_of_cart + book_num - p->data.purchase_amount;
			p->data.purchase_amount = book_num;
			p->data.purchase_money = p->data.price * p->data.purchase_amount;
			book_management::buy_book(book_id, book_num);
			cout << "修改成功！" << endl;
			cout << "ID:" << p->data.book_id << "  " << p->data.book_name << "  购买数量：" << p->data.purchase_amount << endl;
			return SUCCESS;
		}
	}
	else
	{
		cout << "您要修改的图书不存在，请确认您的输入无误！";
		return NOT_PRESENT;
	}
}

status cart::move_to_favorites(const int& book_id, const date& add_to_favorites_date)
{
	status s;
	s = delete_cart_book(book_id);
	if (s == SUCCESS)
		//s = favorites::add_to_favorites(book_id, add_to_favorites_date);
	return s;
}

status cart::delete_cart_book(const int& book_id)
{
	BinTreeNode* p;
	p = find_node(book_id);
	if (p != NULL)
	{
		amount_of_all_books_of_cart-=  p->data.purchase_amount;
		cart.delete_node(p);
		return SUCCESS;
	}
	else
	{
		cout << "图书不存在，请确认您的输入无误！"<< endl;
		return NOT_PRESENT;
	}
}

status cart::show_all_book()
{
	if (cart.get_root() != nullptr)
	{
		cart.show_all_data(cart.get_root());
		return SUCCESS;
	}
	else
	{
		cout << "购物车里空空如也，快去挑选喜欢的图书吧！";
		return NOT_PRESENT;
	}
}

void cart::display_menu()
{
	system("cls");
	int choice, id;

	cout << fixed << setprecision(2);

	cout << "-----------购物车菜单--------------" << endl<<endl;
	cout << "----------1.加入购物车-------------" << endl;
	cout << "----------2.查询指定图书-----------" << endl;
	cout << "----------3.修改购买数量-----------" << endl;
	cout << "----------4.移至收藏夹-------------" << endl;
	cout << "----------5.删除指定图书-----------" << endl;
	cout << "----------6.显示所有图书-----------" << endl;
	cout << "----------7.返回主界面-------------" << endl << endl;
	cout << "请输入您选择的功能：";
	cin >> choice;
	system("cls");

	switch (choice)
	{
	case 1:
		cout << "----------加入购物车----------" << endl << endl;

		while (1)
		{
			cout << "请输入待加入图书的id：";
			cin >> id;
			book_data book;
			if (book_management::get_book_by_id(book, id) != SUCCESS)
			{
				cout << "本图书管理系统未收录该图书，请确认输入无误！按ESC返回重新输入";
				while (1)
				{
					if (_kbhit() && _getch() == 27)
					{
						system("cls");
						break;
					}
				}
			}
			else
				break;
		}
		cout << "请输入加入数量：";
		int purchase_amount;
		cin >> purchase_amount;
		cout << "请输入加入时间：" << endl;
		add_to_cart(id, set_date(),purchase_amount);
		cout << endl << endl << "返回上一层请按 ESC";
		while (1)
		{
			if (_kbhit() && _getch() == 27)
				break;			
		}
		display_menu();
		break;

	case 2:
		cout << "----------查询图书----------" << endl << endl;
		cout << "请输入待查询图书的id：";
		cin >> id;
		query_cart_book(id);
		cout << endl << endl << "返回上一层请按 ESC";
		while (1)
		{
			if (_kbhit() && _getch() == 27)
				break;
		}
		display_menu();
		break;

	case 3:
		cout << "----------修改数量----------" << endl << endl;
		int num;
		cout << "请输入待修改数量的图书的id：";
		cin >> id;
		cout << "请输入图书数量：";
		cin >> num;
		modify_purchase_num(id, num);
		cout << endl << endl << "返回上一层请按 ESC";
		while (1)
		{
			if (_kbhit() && _getch() == 27)
				break;
		}
		display_menu();
		break;

	case 4:
		cout << "----------移至收藏夹----------" << endl << endl;
		cout << "请输入待移入收藏夹的图书的id：";
		cin >> id;
		cout << "请输入移入收藏夹的时间：" << endl;
		if (move_to_favorites(id, set_date()) == SUCCESS)
		{
			book_data book;
			book_management::get_book_by_id(book, id);
			cout << "ID:" << id << "   书名：" << book.book_name << "  移入收藏夹成功" << endl;
		}
		while (1)
		{
			if (_kbhit() && _getch() == 27)
				break;
		}
		display_menu();
		break;

	case 5:
		cout << "----------删除图书----------" << endl << endl;
		cout << "请输入待删除的图书的id：";
		cin >> id;
		if (delete_cart_book(id) == SUCCESS)
		{
			book_data book;
			book_management::get_book_by_id(book, id);
			cout << "ID:" << id << "   书名：" << book.book_name << "  删除成功" << endl;
		}
		cout << endl << "返回上一层请按 ESC";
		while (1)
		{
			if (_kbhit() && _getch() == 27)
				break;
		}
		display_menu();
		break;

	case 6:
		cout << "----------显示全部----------" << endl << endl;
		cout << "共" << amount_of_all_books_of_cart << "本书，" << price_of_all * float(0.01) << "元" << endl << endl;
		show_all_book();
		cout << endl << endl << "返回上一层请按 ESC";
		while (1)
		{
			if (_kbhit() && _getch() == 27)
				break;
		}
		display_menu();
		break;

	case 7:
		return;

	default:
		cout << "Invalid choice!" << endl;
		Sleep(1000);
		display_menu();
		break;
	}

}


status cart::add_to_cart(const int& book_id, const date& add_to_cart_date, const int& purchase_amount)
{
	book_data book;
	status s=book_management::get_book_by_id(book, book_id);

	if (book_id <= 0 || purchase_amount <= 0)
	{
		cout << "输入数据非法，请确认输入无误！";
		return FAIL;
	}
	else if (s == NOT_PRESENT)
	{
		cout << "本图书管理系统未收录该图书，请确认输入无误！";
		return NOT_PRESENT;
	}
	else if (purchase_amount > book.amount)
	{
		cout << "库存不足!" << endl << " ID：" << book.book_id << "  "
			 << book.book_name << "  库存" << book.amount << "本" << endl;
		return RANGE_ERROR;
	}
	else
	{
		amount_of_all_books_of_cart += purchase_amount;
		price_of_all += book.price * purchase_amount;

		BinTreeNode* p = find_node(book_id);
		if (p != nullptr)
		{
			p->data.add_to_cart_date = add_to_cart_date;
			p->data.purchase_amount += purchase_amount;

			cout << "图书已存在!" << endl;
			cout  << "ID:" << p->data.book_id << "  " << p->data.book_name <<"  新加入"<<purchase_amount<<"本后，"
				 << "当前购买数量：" << p->data.purchase_amount << "本" << endl;
		}
		else
		{
			
			book.add_to_cart_date = add_to_cart_date;
			book.purchase_amount = purchase_amount;
			book.purchase_money = book.price * purchase_amount;
			cart.insert(book);
			cout << "添加成功！"<< endl;
			cout << "ID:" << book.book_id << "  " << book.book_name
				<< "  购买数量：" << book.purchase_amount << "本" << endl;
		}	
		return SUCCESS;
	}
}
