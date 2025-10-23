#!/bin/bash

./sltm <<'EOF'
load sample_launches_full.csv
range 2025-06-01 2025-07-31
find Starship
find Vega
exit
EOF
