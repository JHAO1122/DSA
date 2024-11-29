# include <iostream>
# include <vector>
# include <random>
# include <algorithm>
# include <chrono>
# include "HeapSort.h"
template <typename T>
T createrandom(T smallest, T largest)
{
    std::random_device random;
    std::mt19937 gen(random());
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dis(smallest, largest);
        return dis(gen);
    } else {
        std::uniform_real_distribution<T> dis(smallest, largest);
        return dis(gen);
    }
}//一个随机数生成器，根据主函数的要求生成不同类型的随机数
template <typename T>
bool checksort(std::vector<T> seq)
{
    for(int i = 0; i < seq.size()-1; i++){
        if(seq[i] > seq[i+1]){return 0;}
    }
    return 1;
}

int main()
{
    const int N = 1000000;
    std::vector<double> randomseq(N);
    std::vector<double> randomseqclone(N);
    for(int i = 0; i < N; i++){
        randomseq[i] = createrandom(0.0,10.0);
    }//生成一个浮点型的无序随机数序列
    for(int i = 0; i < N; i++){
        randomseqclone[i] = randomseq[i];
    }

    std::vector<double> orderseq(N);
    std::vector<double> orderseqclone(N);
    orderseq[0] = createrandom(0.0,1.0);
    for(int i = 1;i < N; i++){
        double step = createrandom(0.0,0.001);
        orderseq[i] = orderseq[i-1] + step; 
    }//生成一个浮点型的正序随机数序列
        for(int i = 0; i < N; i++){
        orderseqclone[i] = orderseq[i];
    }

    std::vector<double> reverseorderseq(N);
    std::vector<double> reverseorderseqclone(N);
    reverseorderseq[0] = createrandom(0.0,1.0);
    for(int i = 1;i < N; i++){
        double step = createrandom(0.0,0.001);
        reverseorderseq[i] = reverseorderseq[i-1] - step; 
    }//生成一个浮点型的倒序随机数序列
        for(int i = 0; i < N; i++){
        reverseorderseqclone[i] = reverseorderseq[i];
    }

    std::vector<int> repeatrandomseq(N);
    std::vector<int> repeatrandomseqclone(N);
    for(int i = 0; i < N; i++){
        repeatrandomseq[i] = createrandom(0,100);
    }//生成一个整型的有重复数字的随机数序列
        for(int i = 0; i < N; i++){
        repeatrandomseqclone[i] = repeatrandomseq[i];
    }

    auto begin_sort = std::chrono::high_resolution_clock::now(); 
    HeapSort(randomseqclone);
    auto end_sort = std::chrono::high_resolution_clock::now();
    auto duration_sort = std::chrono::duration_cast<std::chrono::milliseconds>(end_sort-begin_sort);
    std::cout << duration_sort.count() << "ms" << std::endl; //使用chrono测试HeapSort()处理随机序列消耗时间
    std::cout << checksort(randomseqclone) << std::endl;

    auto begin2_sort = std::chrono::high_resolution_clock::now(); 
    HeapSort(orderseqclone);
    auto end2_sort = std::chrono::high_resolution_clock::now();
    auto duration2_sort = std::chrono::duration_cast<std::chrono::milliseconds>(end2_sort-begin2_sort);
    std::cout << duration2_sort.count() << "ms" << std::endl; //使用chrono测试HeapSort()处理正序序列消耗时间
    std::cout << checksort(orderseqclone) << std::endl;

    auto begin3_sort = std::chrono::high_resolution_clock::now(); 
    HeapSort(reverseorderseqclone);
    auto end3_sort = std::chrono::high_resolution_clock::now();
    auto duration3_sort = std::chrono::duration_cast<std::chrono::milliseconds>(end3_sort-begin3_sort);
    std::cout << duration3_sort.count() << "ms" << std::endl; //使用chrono测试HeapSort()处理倒序序列消耗时间
    std::cout << checksort(reverseorderseqclone) << std::endl;

    auto begin4_sort = std::chrono::high_resolution_clock::now(); 
    HeapSort(repeatrandomseqclone);
    auto end4_sort = std::chrono::high_resolution_clock::now();
    auto duration4_sort = std::chrono::duration_cast<std::chrono::milliseconds>(end4_sort-begin4_sort);
    std::cout << duration4_sort.count() << "ms" << std::endl; //使用chrono测试HeapSort()处理重复数字随机序列消耗时间
    std::cout << checksort(repeatrandomseqclone) << std::endl;


    std::make_heap(randomseq.begin(), randomseq.end());
    auto begin = std::chrono::high_resolution_clock::now(); 
    std::sort_heap(randomseq.begin(), randomseq.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    std::cout << duration.count() << "ms" << std::endl; //使用chrono测试std::sort_heap()处理随机序列消耗时间
    
    std::make_heap(orderseq.begin(),orderseq.end());
    auto begin2 = std::chrono::high_resolution_clock::now(); 
    std::sort_heap(orderseq.begin(), orderseq.end());
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2-begin2);
    std::cout << duration2.count() << "ms" << std::endl; //使用chrono测试std::sort_heap()处理正序序列消耗时间
    
    std::make_heap(reverseorderseq.begin(), reverseorderseq.end());
    auto begin3 = std::chrono::high_resolution_clock::now(); 
    std::sort_heap(reverseorderseq.begin(), reverseorderseq.end());
    auto end3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3-begin3);
    std::cout << duration3.count() << "ms" << std::endl; //使用chrono测试std::sort_heap()处理倒序序列消耗时间

    std::make_heap(repeatrandomseq.begin(), repeatrandomseq.end());
    auto begin4 = std::chrono::high_resolution_clock::now(); 
    std::sort_heap(repeatrandomseq.begin(), repeatrandomseq.end());
    auto end4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(end4-begin4);
    std::cout << duration4.count() << "ms" << std::endl; //使用chrono测试std::sort_heap()处理有重复数字的随机序列消耗时间
    return 0;
}
