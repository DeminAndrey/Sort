//программа для сравнения времени работы четырех разных сортировок
#include "profile.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;


//вывод вектора в консоль
template<typename T=int>
void Print(const vector<T>& v)
{
    for(auto& i: v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}

//пузырьковая сортировка/ сложность: О(n2)
template<typename T>
void SortPuz(vector<T>& v)
{
    if(v.size()==1)
    {
        return;
    }
    bool flag;
    for (int i=0; i<(v.size()-1); ++i)
    {
        flag=false;
        for (int j=v.size()-1; j>i; --j)
        {
            if (v[j]<v[j-1])
            {
                swap(v[j], v[j-1]);
                flag=true;
            }
        }
        if(flag!=true) return;
    }
}

//сортировка слиянием
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin < 2)
    {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto it = begin(elements) + elements.size() / 2;
    MergeSort(begin(elements), it);
    MergeSort(it, end(elements));
    merge(begin(elements), it, it, end(elements), range_begin);
}

//сортировка методом sort STL/ сложность: O(n*log(n))
template <typename RandomIt>
void SortSTL(RandomIt range_begin, RandomIt range_end)
{
    sort(range_begin, range_end);
}

//быстрая сортировка/ сложность О(n*log(n))
template <typename RandomIt, typename T=int>
 void qSort(RandomIt range_begin, RandomIt range_end)
 {
    if(range_end-range_begin<=1)
        return;
    auto range_middle=*(range_begin+(range_end-range_begin)/2);
    auto it=partition(range_begin, range_end, [range_middle](const T& a){return a<(range_middle);});
    auto it1 = partition(it, range_end, [range_middle](const T& a){return a<=(range_middle);});
    qSort(range_begin, it);
    qSort(it1, range_end);
 }

main()
{
    srand(time(0));

    //создаем массив из n- элементов и заполняем его случайными числами от 1 до 10:
    vector<int> v;
    const int n=10000;

    for(int i=0; i<n; ++i)
    {
        v.push_back(rand()%10);
    }
    vector<vector<int>> vec(5, v);

    cout<<"VECTOR: "<<n<<" elements"<<endl;
//    Print(v);
//    cout<<endl;

    {
        LOG_DURATION("SORT_PUZ");
        SortPuz(vec[1]);

//       Print(vec[1]);
    }

    {
        LOG_DURATION("SORT_SLIYNIYEM");
        MergeSort(begin(vec[2]), end(vec[2]));
//        Print(vec[2]);
    }

    {
        LOG_DURATION("SORT_STL");
        SortSTL(begin(vec[0]), end(vec[0]));
//        Print(vec[0]);
    }

    {
        LOG_DURATION("QUIQ_SORT");
        qSort(begin(vec[3]), end(vec[3]));
//        Print(vec[3]);
    }



    return 0;
}
