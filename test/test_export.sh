#!/bin/bash

./sltm <<'EOF'
load sample_launches_full.csv
export out_full_export.csv
exit
EOF
