﻿//191.位1的个数
//编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为汉明重量）
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int hammingWeight(uint32_t n) {
    int sum = 0;
    while (n != 0)
    {
        sum++;
        n = n & (n - 1);
    }
    return sum;
}

int main()
{
    cout << hammingWeight(3) << endl;
    return 0;
}