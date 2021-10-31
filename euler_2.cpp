// 定理6求欧拉函数

#include <iostream>
#include <vector>
#include <cmath>
#include <map>

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
 * @description: 利用以下两个公式计算欧拉函数
 *               - phi(mn) = phi(m) * phi(n)
 *               - phi(p^k) = p ^ k - p ^ (k - 1)
 * @param {uint64_t} n
 * @return {*}
 */
uint64_t euler_phi_demo_2(uint64_t n) {
    // 生成质因数序列
    vector<uint64_t> bd {breakdown(n)}; 

    // 创建标准分解式
    map<uint64_t, size_t> stdFactor { }; 

    // 生成标准分解式
    for (auto elem : bd) {
        if (stdFactor.find(elem) == stdFactor.end()) {
            stdFactor.insert({elem, (size_t)1}); 
        } else {
            ++stdFactor[elem]; 
        }
    }

    // 欧拉函数结果
    uint64_t ret = 1; 

    // 计算欧拉函数
    for (auto elem : stdFactor) {
        ret *= pow(elem.first, elem.second) - pow(elem.first, elem.second - 1); 
    }

    // 返回欧拉函数结果
    return ret; 
}

int main() {

    uint64_t n; 
    cout << "> 请输入n: "; 
    cin >> n; 
    cout << endl; 

    cout << "> phi(" << n << ") = " << euler_phi_demo_2(n) << endl; 

    return 0; 
}