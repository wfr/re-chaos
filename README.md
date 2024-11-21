# RE: Chaos Overlords (1996)
This repository documents the reverse engineering progress of the classic
turn-based strategy game [Chaos Overlords][Wikipedia_Chaos_Overlords].

All information here is based on the last available release for Windows 95:
```
$ sha256sum "Chaos Overlords.exe"
0791e6209d573a79882675d1236737f5c9b369ea4af541a7dbd03cbadf4493d5
```

## About this project

### Disclaimer
I began deconstructing and decompiling Chaos Overlords as a low-priority side
project in 2020, initially only to practice reverse engineering with a fun
target. It then lay dormant for a few years due to a lack of interest and time.
Now I have even less time to dedicate to it. Progress will continue at a
glacial pace. Do not expect to see a working re-implementation anytime soon; it
may never even be finished.  Nevertheless it would be a waste to let the
information gathered thus far rot on my SSD, so here it is.

### Goals
The hypothetical long-term goal is a modern, open-source re-implementation — a
perfectly deterministic copy of the original. That is, if one were to extract
the RNG seed from the original and start the clone with it, everything,
including the AI, should behave exactly the same.

Additionally, the clone should feature optional improvements:

- Display scaling (2x, 3x, 4x, etc. to keep the pixel art pristine).
- Widescreen support (more game state displayed on one screen).
- Improved keyboard controls

Compatibility may be broken for networking. The original networking code is not
robust or secure. I strongly recommend against exposing the original game to
the internet.

## Data file formats
* Most strings are ASCII, not null-terminated.
* Some strings are stored Pascal-style, i.e. not terminated but prefixed with
  their length (`uint8_t`).
* All integers are stored in Little Endian byte order.

### SITES
```
sizeof(Site): 62
len(sites): 22
Total: 1364 bytes
```

| Offset | Length | Type   | Description
|-------:|-------:|--------|-------------
|      0 |     20 | string | Name
|     14 |      2 | int16  | ID
|     16 |      2 | int16  | Resistance
|     18 |      2 | int16  | Support
|     1A |      2 | int16  | Frequency
|     1C |      2 | int16  | Tolerance
|     1E |      2 | int16  | Cash
|     20 |      2 | int16  | Combat
|     22 |      2 | int16  | Defense
|     24 |      2 | int16  | Stealth
|     26 |      2 | int16  | Detect
|     28 |      2 | int16  | Chaos
|     2A |      2 | int16  | Control
|     2C |      2 | int16  | Heal
|     2E |      2 | int16  | Influence
|     30 |      2 | int16  | Research
|     32 |      2 | int16  | Strength
|     34 |      2 | int16  | Blade
|     36 |      2 | int16  | Range
|     38 |      2 | int16  | Fighting
|     3A |      2 | int16  | Martial arts
|     3C |      2 | int16  | Special flags\*

#### Special flags
| Value | Meaning
|------:|---------
|     0 | Nothing
|     1 | SCIENCE CENTER (Tech 8)
|     2 | RESEARCH LAB (Tech 10)
|     3 | FACTORY

### GANGS
```
sizeof(Gang): 156 bytes
len(gangs): 90
Total: 14040 bytes
```

| Offset | Length | Type   | Description
|-------:|-------:|--------|-------------
|      0 |     30 | string | Name
|     1E |      2 | int16  | ID
|     20 |     90 | string | Description
|     7A |      2 | int16  | Force
|     7C |      2 | int16  | Upkeep
|     7E |      2 | int16  | Combat
|     80 |      2 | int16  | Defense
|     82 |      2 | int16  | Tech Level
|     84 |      2 | int16  | Stealth
|     86 |      2 | int16  | Detect
|     88 |      2 | int16  | Chaos
|     8A |      2 | int16  | Control
|     8C |      2 | int16  | Heal
|     8E |      2 | int16  | Influence
|     90 |      2 | int16  | Research
|     92 |      2 | int16  | Strength
|     94 |      2 | int16  | Blade
|     96 |      2 | int16  | Range
|     98 |      2 | int16  | Fighting
|     9A |      2 | int16  | Martial Arts

### ITEMS
```
sizeof(Item): 166 bytes
len(items): 160
Total: 10624 bytes
```

| Offset | Length | Type   | Description
|-------:|-------:|--------|-------------
|      0 |     30 | string | Name
|     1E |      2 | int16  | ID
|     20 |     90 | string | Description
|     7A |      2 | int16  | Type\*
|     7C |      2 | int16  | Research difficulty
|     7E |      2 | int16  | Cost
|     80 |      2 | int16  | Tech level
|     82 |      2 | int16  | Combat
|     84 |      2 | int16  | Defense
|     86 |      2 | int16  | Stealth
|     88 |      2 | int16  | Detect
|     8A |      2 | int16  | Chaos
|     8C |      2 | int16  | Control
|     8E |      2 | int16  | Heal
|     90 |      2 | int16  | Influence
|     92 |      2 | int16  | Research
|     94 |      2 | int16  | Strength
|     96 |      2 | int16  | Blade
|     98 |      2 | int16  | Range
|     9A |      2 | int16  | Fighting
|     9C |      2 | int16  | Martial arts
|     9E |      2 | int16  | Weapon attack animation
|     A0 |      2 | int16  | Weapon hit animation
|     A2 |      2 | int16  | Weapon sound
|     A4 |      2 | int16  | Unknown

## SND00xxx
Sounds are stored as regular WAV files.

RIFF (little-endian) data, WAVE audio, Microsoft PCM, 8 bit, mono 22050 Hz.

## PX16/PXxxxxx
These are uncompressed BMP images with parts of the header zeroed out. The
headers are hardcoded in the executable.

It is sufficient to fix up the following bytes to make the images readable:

| Offset | Length | Type   | Description
|-------:|-------:|--------|-------------
|     12 |      4 |  int32 | Width
|     16 |      4 |  int32 | Height
|     1A |      2 |  int16 | Color planes (1)
|     1C |      2 |  int16 | Bits per pixel (16)

## Save game format
There are two slightly different save game formats, 
determined by the magic marker at the start.

* If the save game starts with 0x57303453, the size is 45305 bytes.
* If the save game starts with 0x5730344E, the size is 45329 bytes.


| Offset | Length | Type                | Description
|-------:|-------:|---------------------|-------------
|      0 |      4 |               int32 | Magic (0x57303453 or 0x5730344E)
|      4 |  15552 | GangInstance[6][81] | Gang instances
|   3CC4 |   2304 |    SectorData36[64] | Sectors
|   45C4 |     24 |            int32[6] | Player cursor positions (sector ID)
|   45DC |      6 |             int8[6] | Player portraits
|   45E2 |     24 |            int32[6] | Player status (Human, AI, ...)
|   45FA |      4 |               int32 | Turn number
|   45FE |      4 |               int32 | Objective
|   4602 |      4 |               int32 | Max turns
|   4606 |     24 |            int32[6] | Cash `[player_id]`
|   461E |     18 |          int8[6][3] | `hire_pool[player_id][] = gang_id`
|   4630 |     18 |          int8[6][3] | `hire_pool_target[player_id][] = sector_id`
|   4642 |    384 |         int8[64][6] | `research_progress[item_id][player_id]`
|   47C2 |      6 |             int8[6] | `player_alive[player_id] = bool`
|   47C8 |   7776 |   GangData16[6][81] | `...[player_id][gang_nr]`
|   6628 |      6 |             int8[6] | UNKNOWN `[player_id]`
|   662E |     24 |            int32[6] | UNKNOWN `[player_id]`
|   6646 |   1944 |        int32[6][81] | UNKNOWN `[player_id][gang_nr]`
|   6DDE |      6 |             int8[6] | UNKNOWN `[player_id]`
|   6DE4 |     24 |            int32[6] | Initial HQ position + 64
|   6DFC |     24 |            int32[6] | UNKNOWN `[player_id]`
|   6E14 |     24 |            int32[6] | UNKNOWN `[player_id]`
|   6E2C |     24 |            int32[6] | Score
|   6E44 |    256 |        int16[64][2] | Sector crackdown history
|   6F44 |   1920 | Notification[6][32] | Notification queues
|   76C4 |   9600 |   SectorData150[64] | TBD
|   9C44 |   4860 |   GangData10[6][81] | TBD
|   AF40 |      2 |               int16 | Current player id
|   AF42 |     72 |         char[6][12] | Player names (Pascal style strings)
|   AF8A |     24 |            int32[6] | Total sectors overtaken
|   AFA2 |     24 |            int32[6] | Total damage inflicted
|   AFBA |     24 |            int32[6] | Total times hidden
|   AFD2 |     24 |            int32[6] | Total cash spent
|   AFEA |     24 |            int32[6] | Total casualties
|   B002 |     24 |            int32[6] | Total cash earned
|   B01A |    144 |         int32[6][6] | UNKNOWN
|   B0AA |     24 |            int32[6] | UNKNOWN
|   B0C2 |      6 |             int8[6] | UNKNOWN
|   B0C8 |     24 |            int32[6] | Luck boost
|   B0E0 |      6 |             int8[6] | Is player human?
|   B0E6 |      1 |                int8 | Preference: Difficulty
|   B0E7 |      1 |                int8 | Preference: Time Limit
|   B0E8 |      1 |                int8 | Preference: Objective
|   B0E9 |      6 |             int8[6] | Cheat Hubble Yes/No
|   B0EF |      6 |             int8[6] | Cheat Milk Yes/No
|   B0F5 |     24 |            int32[6] | UNKNOWN, only present if magic == 0x5730344E
|   B10D |      4 |               int32 | Magic (0x57303453 or 0x5730344E)


## References
* [Wikipedia: Chaos Overlords][Wikipedia_Chaos_Overlords]
* [GOG: Chaos Overlords](https://www.gog.com/de/game/chaos_overlords)

[Wikipedia_Chaos_Overlords]: https://en.wikipedia.org/wiki/Chaos_Overlords
