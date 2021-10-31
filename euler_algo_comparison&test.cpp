// 欧拉函数三种算法结果正确性测试与性能测试

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include "color.h"

using namespace std; 

uint64_t euler_phi_1(uint64_t); 
uint64_t euler_phi_2(uint64_t); 
uint64_t euler_phi_3(uint64_t); 
uint64_t gcd(uint64_t, uint64_t); 
vector<uint64_t> breakdown(uint64_t); 
vector<uint64_t> remove_number_dup(const vector<uint64_t>&); 

void TEST_RESULT(uint64_t); 
void TEST_TIME(uint64_t, size_t); 
template<typename T> inline bool
EXPECT_EQ(const T&, const T&); 

int main() {

    uint64_t n; 
    cout << "> input n: "; 
    cin >> n; 
    cout << endl; 

    // 算法结果正确性测试
    TEST_RESULT(n); 

    // 算法性能测试
    TEST_TIME(n, 100); 


    return 0; 
}

void TEST_RESULT(uint64_t n) {
    if (EXPECT_EQ<uint64_t>(euler_phi_1(n), euler_phi_2(n))) {
        PRINT_FONT_GRE
        printf("[ TEST  OK ] "); 
        PRINT_ATTR_REC
        printf("euler_phi_1 is equal to euler_phi_2\n"); 
    } else {
        PRINT_FONT_RED
        printf("[  FAILED  ] "); 
        PRINT_ATTR_REC
        printf("euler_phi_1 is not equal to euler_phi_2\n"); 
    }
    if (EXPECT_EQ<uint64_t>(euler_phi_1(n), euler_phi_3(n))) {
        PRINT_FONT_GRE
        printf("[ TEST  OK ] "); 
        PRINT_ATTR_REC
        printf("euler_phi_1 is equal to euler_phi_3\n"); 
    } else {
        PRINT_FONT_RED
        printf("[  FAILED  ] "); 
        PRINT_ATTR_REC
        printf("euler_phi_1 is not equal to euler_phi_3\n"); 
    }
    cout << endl; 
}

void TEST_TIME(uint64_t n, size_t loop) {
    const size_t LOOP {loop}; 
    double spent {0.0}; 

    cout << "loop times: " << LOOP << endl; 
    
    for (size_t i = 0; i < LOOP; ++i) {
        clock_t begin = clock(); 
        euler_phi_1(n); 
        clock_t end = clock(); 
        spent += (double)(end - begin) / CLOCKS_PER_SEC; 
    }
    printf("Average time of euler_phi_1: %.8lf seconds\n", spent / LOOP); 

    spent = 0.0; 
    for (size_t i = 0; i < LOOP; ++i) {
        clock_t begin = clock(); 
        euler_phi_2(n); 
        clock_t end = clock(); 
        spent += (double)(end - begin) / CLOCKS_PER_SEC; 
    }
    printf("Average time of euler_phi_2: %.8lf seconds\n", spent / LOOP); 

    spent = 0.0; 
    for (size_t i = 0; i < LOOP; ++i) {
        clock_t begin = clock(); 
        euler_phi_3(n); 
        clock_t end = clock(); 
        spent += (double)(end - begin) / CLOCKS_PER_SEC; 
    }
    printf("Average time of euler_phi_3: %.8lf seconds\n", spent / LOOP); 
}

template<typename T> inline bool
EXPECT_EQ(const T &lhs, const T &rhs) {
    return lhs == rhs; 
}

/**
 * @description: 定义法暴力求解欧拉函数值
 * @param {uint64_t} n 自变量
 * @return {uint64_t} 欧拉函数值
 */
uint64_t euler_phi_1(uint64_t n) {
    size_t cnt {0}; 
    for (uint64_t i = 1; i <= n; ++i) 
        if (gcd(i, n) == 1) ++cnt;
    return cnt; 
}

/**
 * @description: 利用以下两个公式计算欧拉函数
 *               - phi(mn) = phi(m) * phi(n)
 *               - phi(p^k) = p ^ k - p ^ (k - 1)
 * @param {uint64_t} n 自变量
 * @return {uint64_t} 欧拉函数值
 */
uint64_t euler_phi_2(uint64_t n) {
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

/**
 * @description: 利用以下公式求解欧拉函数
 *               - phi(n) = n * (1 - 1/p1) * ... * (1 - 1/pn)
 *               其中pi为n的标准分解式中的所有素数底
 * @param {uint64_t} n 自变量
 * @return {uint64_t} 欧拉函数值
 */
uint64_t euler_phi_3(uint64_t n) {
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

uint64_t gcd(uint64_t lhs, uint64_t rhs) {
    if (lhs > rhs) return gcd(rhs, lhs); 
    if (rhs % lhs == 0) return lhs; 
    return gcd(rhs % lhs, lhs); 
}

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