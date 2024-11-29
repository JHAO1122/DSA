# include <iostream>
# include <algorithm>
# include <vector>
template <typename T>
void HeapSort(std::vector<T> & sequence){
    std::make_heap(sequence.begin(),sequence.end());//将序列建成一个最大堆
    for(int i = sequence.size()-1; i > 0; i--){
        std::pop_heap(sequence.begin(),sequence.begin() + i + 1);
    }//将堆顶最大元素和堆的末尾元素互换，每换一次都将最末尾元素排除出去   
}
