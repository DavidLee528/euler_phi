// 定理7求欧拉函数

#include <iostream>
#include <vector>
#include <set>

using namespace std; 

/**
 * @description: 分解质因数
 * @param {uint64_t} n 例如100
 * @return {vector<uint64_t>} 例如 2 2 5 5
 */
vector<uint64_t> breakdown(uint64_t n) {
    vector<uint64_t> ret { }; 
    for (uint64_t i = 2; i <= n / i; ++i) {
        while (n % i == 0) {
            ret.push_back(i); 
            n /= i; 
        }
    }
    if (n != 1) ret.push_back(n); 
    return ret; 
}

/**
 * @description: 使整数序列不重复
 *               std::set的底层实现是红黑树的平衡二叉树，
 *               其元素value唯一，可以用于去重和排序
 * @param {vector<uint64_t>&} arr 例如 2 2 5 5
 * @return {vector<uint64_t>} 例如 2 5
 */
vector<uint64_t> remove_number_dup(const vector<uint64_t> &arr) {
    set<uint64_t> s {arr.begin(), arr.end()}; 
    vector<uint64_t> ret {s.begin(), s.end()}; 
    return ret; 
}

uint64_t euler_phi_demo_3(uint64_t n) {
    // 欧拉函数结果
    uint64_t ret {n}; 

    // 分解质因数
    vector<uint64_t> bd {breakdown(n)}; 

    // 去除重复质因数
    bd = remove_number_dup(bd); 

    // 代入定理7公式计算结果
    for (auto elem : bd) ret *= ((double)(elem - 1) / elem); 

    // 返回结果
    return ret; 
}

int main() {

    uint64_t n { }; 
    cout << "> 请输入n: "; 
    cin >> n; 
    cout << endl; 

    cout << endl << "> phi(" << n << ") = " << euler_phi_demo_3(n) << endl; 

    return 0; 
}