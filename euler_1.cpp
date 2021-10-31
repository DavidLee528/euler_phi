// 定义法求欧拉函数

#include <iostream>

using namespace std; 

uint64_t gcd(uint64_t lhs, uint64_t rhs) {
    if (lhs > rhs) return gcd(rhs, lhs); 
    if (rhs % lhs == 0) return lhs; 
    return gcd(rhs % lhs, lhs); 
}

uint64_t euler_phi_demo_1(uint64_t n, bool enableDemo = false) {
    if (enableDemo) {
        cout << "=============== 定义法求欧拉函数 ===============" << endl; 
        cout << "欧拉函数的定义：i遍历区间[1, n]，满足gcd(i, n)==1的i的个数。" << endl; 
        cout << "此算法时间复杂度O(nlogn)，下面开始演示：" << endl << endl; 
    }

    size_t cnt {0}; 
    for (uint64_t i = 1; i <= n; ++i) {
        if (enableDemo) cout << "当前遍历到" << i ;  
        if (gcd(i, n) == 1) {
            ++cnt;
            if (enableDemo) cout << ": 符合定义，cnt加1, cnt = " << cnt; 
        } 
        else {
            if (enableDemo) cout << ": 不符合定义"; 
        } 
        if (enableDemo) cout << endl; 
    }
    return cnt; 
}

int main() {

    uint64_t n {}; 
    cout << "> 请输入n: "; 
    cin >> n; 
    cout << endl; 

    cout << endl << "> phi(" << n << ") = " << euler_phi_demo_1(n, true) << endl; 

    return 0; 
}