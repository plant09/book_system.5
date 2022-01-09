//
// Created by lhh on 2022/1/2.
//

#ifndef ASSISTANCE_H
#define ASSISTANCE_H
// 辅助软件包

// ANSI C++标准库头文件
//#include <cstring>                     // 标准串操作
#include <iostream>                    // 标准流操作
#include <limits>                      // 极限
#include <cmath>                       // 数据函数
#include <fstream>                     // 文件输入输出
#include <cctype>                      // 字符处理
#include <cstdlib>                     // 标准库
#include <cstdio>                      // 标准输入输出
#include <iomanip>                     // 输入输出流格式设置
#include <cstdarg>                     // 支持变长函数参数
#include <cassert>                     // 支持断言
#include <windows.h>                   // 标准系统调用
#include<tuple>

using namespace std;                   // 标准库包含在命名空间std中

// 自定义类型
enum status {
    SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR,
    NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};

// 日期
struct date {
    int year;
    int month;
    int day;

    friend bool operator<(const date &lhs, const date &rhs) {
        return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
    }

    friend bool operator>(const date &lhs, const date &rhs) { return rhs < lhs; }

    friend bool operator<=(const date &lhs, const date &rhs) { return !(lhs > rhs); }

    friend bool operator>=(const date &lhs, const date &rhs) { return !(lhs < rhs); }

    friend bool operator==(const date &lhs, const date &rhs) {
        return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
    }

    friend bool operator!=(const date &lhs, const date &rhs) { return !(lhs == rhs); }

    date &operator++() {
        if (++day > 31) {
            day = 1;
            if (++month > 12) {
                month = 1;
                ++year;
            }
        }
        return *this;
    }

    date operator++(int) &{
        date tmp = *this;
        operator++();
        return tmp;
    }
};


#define BOOK_NAME_LENGTH 20                        // 默认书名长度
#define AUTHOR_NAME_LENGTH 20                      // 默认作者名长度
#define PUBLISHER_NAME_LENGTH 20                   // 默认出版社名长度

// 书籍信息
struct book_data {
    int book_id;                                   // 图书号
    char book_name[BOOK_NAME_LENGTH];              // 书名
    char author_name[AUTHOR_NAME_LENGTH];          // 作者
    char publisher_name[PUBLISHER_NAME_LENGTH];    // 出版社
    date publish_date;                             // 出版日期
    int price;                                     // 价格（分）
    date add_to_favorites_date;                    // 收藏日期
    int purchase_amount;                           // 购买数量
    int purchase_money;                            // 购买金额（分）
    date add_to_cart_date;                         // 加入购物车日期
    int amount;                                    // 数量
    date storage_date;                             // 入库日期
    book_data &operator=(const book_data &other) {
        if (this == &other)
            return *this;
        this->book_id = other.book_id;
        strcpy_s(this->book_name, other.book_name);
        strcpy_s(this->author_name, other.author_name);
        strcpy_s(this->publisher_name, other.publisher_name);
        this->publish_date = other.publish_date;
        this->price = other.price;
        this->add_to_favorites_date = other.add_to_favorites_date;
        this->purchase_amount = other.purchase_amount;
        this->purchase_money = other.purchase_money;
        this->add_to_cart_date = other.add_to_cart_date;
        this->amount = other.amount;
        this->storage_date = other.storage_date;
        return *this;
    }
};

#endif // ASSISTANCE_H
