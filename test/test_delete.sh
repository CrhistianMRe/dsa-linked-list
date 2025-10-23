#!/bin/bash

./sltm <<'EOF'
load sample_launches_full.csv
delete SLV010
delete SLV999
range 2025-04-01 2025-05-01
export out_test_delete.csv
exit
EOF
