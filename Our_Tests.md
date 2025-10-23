Our Tests - Expected Outputs (Description)

        test_load.sh - Expected:

Space Launch Timeline Manager (sltm)
Type 'help' for commands. Use Ctrl-C to exit.
sltm> Loaded 30 records, ignored 5 invalid/missing records.
sltm> Exiting...

        test_add.sh - Expected:

... (omitted) ...
sltm> Loaded 30 records, ignored 5 invalid/missing records.
sltm> Added SLV100
sltm> Error: id SLV100 already exists
sltm> SLV100,2026-01-01,Falcon 9,New Year Test,CCSFS SLC-40,Scheduled
sltm> Exported to out_test_add.csv
sltm> Exiting...

        test_update.sh - Expected:

sltm> Loaded 30 records, ignored 5 invalid/missing records.
sltm> Updated SLV005
sltm> SLV005,2025-02-01,Falcon Heavy,Lunar Probe Pathfinder,KSC LC-39A,Success
sltm> SLV005,2025-02-01,Falcon Heavy,Lunar Probe Pathfinder,KSC LC-39A,Success
sltm> Exported to out_test_update.csv
sltm> Exiting...

        test_delete.sh - Expected:

sltm> Loaded 30 records, ignored 5 invalid/missing records.
sltm> Deleted SLV010
sltm> Error: id SLV999 not found
sltm> SLV009,2025-04-12,PSLV,NavIC Expansion,Satish Dhawan FLP,Success
sltm> SLV011,2025-05-10,New Glenn,Orbital Tourism Demo,LC-36,Scheduled
sltm> Exported to out_test_delete.csv
sltm> Exiting...

        test_range_find.sh - Expected:

sltm> Loaded 30 records, ignored 5 invalid/missing records.
sltm> SLV013,2025-06-01,Falcon 9,Starlink Batch Alpha,CCSFS SLC-40,Success
sltm> SLV014,2025-06-15,Electron,Microsat Deployment,Mahia LC-1B,Success
sltm> SLV015,2025-06-20,H3,Communications Relay,Tanegashima LA-Y,Scheduled
sltm> SLV016,2025-07-02,Long March 5B,Lunar Lander Test,WSLC LC-101,Failure
sltm> SLV017,2025-07-18,Vega C,Polar Imaging,ESA Vega Site,Delayed
sltm> SLV018,2025-07-25,Starship,Mars Cargo Demo,Boca Chica Orbital Pad,Scheduled
sltm> SLV018,2025-07-25,Starship,Mars Cargo Demo,Boca Chica Orbital Pad,Scheduled
sltm> SLV008,2025-04-02,Vega C,Earth Imaging Cluster,Vega Launch Zone,Success
sltm> Exiting...

        test_export.sh - Expected:

sltm> Loaded 30 records, ignored 5 invalid/missing records.
sltm> Exported to out_full_export.csv
sltm> Exiting...
