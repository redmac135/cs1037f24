#include "avl.h"
#include "myrecord_avl.h"
#include <stdio.h>

int main() {
  // Create two AVLDS structures.
  AVLDS ds1;
  ds1.root = NULL;
  ds1.count = 0;
  ds1.mean = 0.0;
  ds1.stddev = 0.0;

  AVLDS ds2;
  ds2.root = NULL;
  ds2.count = 0;
  ds2.mean = 0.0;
  ds2.stddev = 0.0;

  // Add records to the first AVLDS structure.
  RECORD data1 = {"Alice", 1};
  RECORD data2 = {"Bob", 2};
  RECORD data3 = {"Charlie", 3};
  add_record(&ds1, data1);
  add_record(&ds1, data2);
  add_record(&ds1, data3);

  // Add records to the second AVLDS structure.
  RECORD data4 = {"David", 4};
  RECORD data5 = {"Eve", 5};
  RECORD data6 = {"Frank", 6};
  add_record(&ds2, data4);
  add_record(&ds2, data5);
  add_record(&ds2, data6);

  // Print the statistics of the two AVLDS structures.
  printf("ds1: count=%d, mean=%.2f, stddev=%.2f\n", ds1.count, ds1.mean,
         ds1.stddev);
  printf("ds2: count=%d, mean=%.2f, stddev=%.2f\n", ds2.count, ds2.mean,
         ds2.stddev);

  // Merge the second AVLDS structure into the first AVLDS structure.
  merge_avlds(&ds1, &ds2);

  // Print the statistics of the first AVLDS structure after merging.
  printf("ds1: count=%d, mean=%.2f, stddev=%.2f\n", ds1.count, ds1.mean,
         ds1.stddev);

  return 0;
}
