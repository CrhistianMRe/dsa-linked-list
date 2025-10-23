#!/bin/bash

./sltm <<'EOF'
load sample_launches_full.csv
update SLV005 status=Success date=2025-02-01
find Lunar
range 2025-02-01 2025-03-05
export out_test_update.csv
exit
EOF
