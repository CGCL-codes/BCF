# Better Choice Cuckoo Filter

## Overview
Better Choice Cuckoo Filter (BCF) is an efficient approximate membership test data structure. Different from the standard Cuckoo Filter (CF), BCF levearge the principle of the power of two choices to select the better candidate bucket during inserting an element. The advantages of DCF are as follows

* The BCF design achieve a more uniform distribution compared with the standard CF.
* BCF outperforms the state-of-the-art CF design in terms of the average number of relocations and the inserting latency.
* BCF reduces the average number of relocations of CF by 35%, as well as reducing item inserting latency by 25%.



## API
--------
A Better Choice Cuckoo Filter supports following operations:

*  `Add(item)`: insert an item to the filter
*  `Contain(item)`: return if item is already in the filter. Note that this method may return false positive results like Bloom filters
*  `Delete(item)`: delete the given item from the filter. Note that to use this method, it must be ensured that this item is in the filter (e.g., based on records on external storage); otherwise, a false item may be deleted.
*  `Size()`: return the total number of items currently in the filter
*  `SizeInBytes()`: return the filter size in bytes
*  `NumTagsInBucket()`: return the number of fingerprints stored in the bucket

Generate BCF according to the capacity of total_items, each item is of type size_t and use 12 bits for each item


```c++
CuckooFilter<size_t, 12> filter(total_items);
```

Inserting item using the power of two Choices

```c++
  GenerateIndexTagHash(item, &i1, &tag);
  i2 = AltIndex(i1,tag);
  number1=table_ -> NumTagsInBucket(i1);
  number2=table_ -> NumTagsInBucket(i2);

  if(number1 <= number2){
    i = i1;
  }else{
    i = i2;
  }
  return AddImpl(i, tag);

```


## How to use?
### Environment
We implement BCF in a Linux (Red Hat Enterprise Linux Server release 6.2) with an Intel(R) Xeon(R) CPU E5-2670 0 @ 2.60GHz CPU and OpenSSL library environment. 


Build and run the example

```txt
make test
./test
```


### Configurations
Configurations including the number of total items and dataset path.

```c++
size_t total_items = 1048576;
std::ifstream in("./input/ip_final.txt");
```


## Author and Copyright

BCF is developed in National Engineering Research Center for Big Data Technology and System, Cluster and Grid Computing Lab, Services Computing Technology and System Lab, School of Computer Science and Technology, Huazhong University of Science and Technology, Wuhan, China by Feiyue Wang (wangfy@hust.edu.cn), Hanhua Chen (chen@hust.edu.cn), Liangyi Liao (liaoliangyi@hust.edu.cn), Fan Zhang (zhangf@hust.edu.cn), Hai Jin (hjin@hust.edu.cn)

Copyright (C) 2017, [STCS & CGCL](http://grid.hust.edu.cn/) and [Huazhong University of Science and Technology](http://www.hust.edu.cn).

## Publication

If you want to know more detailed information, please refer to this paper:

Feiyue Wang, Hanhua Chen, Liangyi Liao, Fan Zhang, Hai Jin. The Power of Better Choice: Reducing Relocations in Cuckoo Filter. ICDCS. Dallas, Texas, USA. July 7-10, 2019.
# BCF
