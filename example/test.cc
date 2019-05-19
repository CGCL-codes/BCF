#include "cuckoofilter.h"

#include <assert.h>
#include <math.h>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using cuckoofilter::CuckooFilter;
size_t NumberOfBuckets_4;
size_t NumberOfBuckets_3;
size_t NumberOfBuckets_2;
size_t NumberOfBuckets_1;
size_t NumberOfBuckets_0;
size_t NumberOfRelocations;

int main(int argc, char **argv) {
  for(int i=1;i<=1;i++){

  
  size_t total_items = 1048576;
  NumberOfBuckets_0=total_items/4;
  NumberOfBuckets_1=0,NumberOfBuckets_2=0,NumberOfBuckets_3=0,NumberOfBuckets_4=0,NumberOfRelocations=0;

  // Create a cuckoo filter where each item is of type size_t and
  // use 12 bits for each item:
  //    CuckooFilter<size_t, 12> filter(total_items);
  // To enable semi-sorting, define the storage of cuckoo filter to be
  // PackedTable, accepting keys of size_t type and making 13 bits
  // for each key:
  //   CuckooFilter<size_t, 13, cuckoofilter::PackedTable> filter(total_items);
  CuckooFilter<size_t, 12> filter(total_items);
  
  
  size_t num_inserted = 0;
  size_t insert_time=0;
      struct timeval tv1,tv2;
    struct timezone tz1,tz2;
   std::ifstream in("./ip_final.txt");
  std::ofstream out("./ip_relocation_better"+ std::to_string(i)+".csv");
  // std::ofstream out ("./ip_inserttime_better_nobreak"+std::to_string(i)+".csv");
  // std::ifstream in("./phonenumberout.txt");
  // std::ofstream out("./phonenumberoutput.txt");

  uint64_t num;
  if(!in.is_open()){
    std::cout<<"Error opening file";
    return 0;
    
  }
  while(!in.eof()&&insert_time<=1048576){
    
    in >> num;
     if(insert_time++ % 10486==0){
      gettimeofday(&tv1,&tz1);
    }
    if((num_inserted-100)%10486==0){
            gettimeofday(&tv2,&tz2);
            out<< num_inserted << "," << (tv2.tv_sec-tv1.tv_sec)*1000000+(tv2.tv_usec-tv1.tv_usec)<<std::endl;
            sleep(1);
            std::cout  <<"当前负载： "<< num_inserted << "," << "插入速度： "<<(tv2.tv_sec-tv1.tv_sec)*1000000+(tv2.tv_usec-tv1.tv_usec)<<std::endl;
        }
    if(filter.Contain(num) == cuckoofilter::Ok)
      continue;
    if(filter.Add(num)!=cuckoofilter::Ok){
      // out << insert_time << ","<< NumberOfRelocations << std::endl;
      if(NumberOfRelocations>=499){
        std::cout<<num_inserted << std::endl;
        break;
      }
      NumberOfRelocations=0;
      continue;
    }
    // out << insert_time << ","<< NumberOfRelocations<< std::endl;
    NumberOfRelocations=0;
    num_inserted++;

    
    

  }
  // out << insert_time/10486+1 << "," << clock() << std::endl;
  // out << num_inserted << std::endl;
   in.close();
  out.close();
  }

  // Insert items to this cuckoo filter
  // size_t num_inserted = 0;
  // for (size_t i = 0; i < total_items; i++, num_inserted++) {
  //   if (filter.Add(i) != cuckoofilter::Ok) {
  //     break;
  //   }
  // }

  // Check if previously inserted items are in the filter, expected
  // true for all items
  // for (size_t i = 0; i < num_inserted; i++) {
  //   assert(filter.Contain(i) == cuckoofilter::Ok);
  // }

  // Check non-existing items, a few false positives expected
  // size_t total_queries = 0;
  // size_t false_queries = 0;
  // for (size_t i = total_items; i < 2 * total_items; i++) {
  //   if (filter.Contain(i) == cuckoofilter::Ok) {
  //     false_queries++;
  //   }
  //   total_queries++;
  // }

  // // Output the measured false positive rate
  // std::cout << "false positive rate is "
  //           << 100.0 * false_queries / total_queries << "%\n";

  return 0;
}
