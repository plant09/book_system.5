#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include<conio.h>
#include"BinSortTree.h"
#include"assistance.h"
#include"book_management.h"
//#include"favorites.h"

class cart
{
private:
    //用二叉排序树作为购物车的存储结构
    BinSortTree cart;   

    //设置日期
    date set_date();

    //通过id寻找图书在购物车中的结点
    BinTreeNode* find_node(const int& book_id);

    //辅助折半查找读入文件的递归函数
    void assis_read(ifstream& file,int low,int high);

    //辅助中序遍历写入按id顺序写入文件的递归函数
    void assis_write(ofstream& file, BinTreeNode* p);



    //查询指定图书的信息
    status query_cart_book(const int& book_id);

    //修改指定图书的购买数量
    status modify_purchase_num(const int& book_id, const int& book_num);

    //删除购物车图书并移至收藏夹
    status move_to_favorites(const int& book_id, const date& add_to_favorites_date);

    //直接删除购物车图书
    status delete_cart_book(const int& book_id);

    //显示购物车内所有图书的信息
    status show_all_book();

public:

   // 所有图书的数量
    int amount_of_all_books_of_cart=0;
    //购物车内图书的总价
    int price_of_all=0;

    //读取二进制文件重构排序二叉树
    /*通过 折半查找 的方式 反序列化读取二进制文件
    重构折半查找的判断二叉树，也就是一颗 平衡二叉树，
    从而维护二叉排序树的性能*/
    status read();
    
    //通过中序遍历将购物车的二叉树结点数据顺序写入文件
    status write();
    
    //购物车菜单
    void display_menu();

    //加入购物车
    status add_to_cart(const int& book_id, const date& add_to_cart_date, const int& purchase_amount);

};

#endif
