#!/bin/bash

./sltm <<'EOF'
load sample_launches_full.csv
add SLV100,2026-01-01,Falcon 9,New Year Test,CCSFS SLC-40,Scheduled
add SLV100,2026-01-02,Falcon 9,Duplicate ID Test,CCSFS SLC-40,Scheduled
find New Year
export out_test_add.csv
exit
EOF
