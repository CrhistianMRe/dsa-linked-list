# Space Launch Timeline Manager (SLTM)

**SLTM** is a command-line tool written in C for managing a space launch event timeline using **singly linked lists**.

---

## 1. Environment & Build Requirements

- **Operating System:** Ubuntu (tested in console/TTY only)
- **Compiler:** `gcc` with C11 standard (`-std=c11`)
- **Libraries:** Standard C library only (`stdio.h`, `stdlib.h`, etc.)
- **Input/Output:** UTF-8 plain text
- **Memory:** Must be memory-safe with no leaks

---

## 2. Project Goals

- Load launch data from CSV files
- Maintain a sorted singly linked list by launch date
- Support searching, updating, and deleting launch records
- Validate and skip invalid or malformed records
- Export the current list back to a CSV file
- Implement an interactive shell (`sltm`) that executes sub-commands sequentially
  
---

## 3. Required Features

**Main Command:** `sltm`

| Sub-Command | Description |
|-------------|-------------|
| `load <file>` | Load a CSV file into a sorted singly linked list by date. Skip and count invalid/missing records. |
| `add <record>` | Insert a new launch record into the correct chronological position. |
| `update <id> <field>=<value> ...` | Modify existing record(s) by ID. |
| `delete <id>` | Remove a record by ID. |
| `range <start_date> <end_date>` | Print launches within the inclusive date range. |
| `find <keyword>` | Case-insensitive substring search on mission or vehicle. |
| `export <file>` | Write the current list back to a CSV file. |

**Notes:**

- **Date format:** `YYYY-MM-DD` only  
- Invalid or malformed date lines (e.g., `2025-06-xx`) or missing fields are skipped and counted as ignored.
- **Fields** (CSV Header): `id,date,vehicle,mission,site,status`
- status ∈ {Scheduled, Success, Failure, Delayed, Cancelled}
- **Data structure** : You must define your own struct Event and struct Node (singly linked). No arrays or vectors as main container.
  
---

## 4. Submission
- Source code
- **Makefile** or build.sh (choose one, not both required).
- CSV dataset (≥30 lines curated by your team) including some invalid entries.
- At least **6 custom test scripts** (against your dataset) and their expected outputs described in `Our_Tests.md`.
  
--- 

## 5. Starter Data
### - sample_launches.csv
<details>

<summary>sample</summary>

```csv
id,date,vehicle,mission,site,status
SLV001,2025-01-15,Falcon 9,Starlink Group 9-1,CCSFS SLC-40,Success
SLV002,2025-01-20,Ariane 6,Artemis Supply Test,Kourou ELA-4,Delayed
SLV003,2025-02-05,Long March 5B,Chinese Space Lab Module,WSLC LC-101,Success
SLV004,2025-02-18,H3,HTV-X Cargo to ISS,Tanegashima LA-Y,Failure
SLV005,2025-03-01,Falcon Heavy,Lunar Probe Pathfinder,KSC LC-39A,Scheduled
SLV006,2025-03-10,Electron,WeatherSat-3,Mahia LC-1B,Success
SLV007,2025-03-25,Starship,Deep Space Cargo Test,Boca Chica Orbital Pad,Delayed
SLV008,2025-04-02,Vega C,Earth Imaging Cluster,Vega Launch Zone,Success
SLV009,2025-04-12,PSLV,NavIC Expansion,Satish Dhawan FLP,Success
SLV010,2025-04-30,Falcon 9,Starlink Group 9-2,CCSFS SLC-40,Cancelled
SLV011,2025-05-10,New Glenn,Orbital Tourism Demo,LC-36,Scheduled
SLV012,2025-05-22,Long March 7,Space Station Cargo,WSLC LC-201,Success
```
</details>

---

## 6. Invalid Data Example
### - test_invalid.csv
<details>
  
<summary>sample</summary>

```csv
id,date,vehicle,mission,site,status
X001,2025-06-01,Falcon 9,Starlink Batch X,CCSFS SLC-40,Success
X002,2025-06-xx,Falcon 9,Starlink Batch Y,CCSFS SLC-40,Success
X003,2025-07-10,,New Satellite Deployer,WSLC LC-201,Scheduled
X004,2025-07-20,Electron,Small Payload Orbit,Mahia LC-1B,
X005,06-30-2025,Starship,Mars Cargo Demo,Boca Chica Orbital Pad,Delayed
```

</details>
