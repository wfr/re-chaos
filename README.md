# Internals of Chaos Overlords (1996)

## Data file formats
* Strings are ASCII, not null-terminated.
* Integers are stored in Little Endian byte order.
* Offsets in this document are in base 16.

### SITES
22 * 62 byte = 1364 byte.

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
|     0 |
|     1 | SCIENCE CENTER (Tech 8)
|     2 | RESEARCH LAB (Tech 10)
|     3 | FACTORY

### GANGS
90 * 156 byte = 14040 byte

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
160 * 166 byte = 10624 byte

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
These are uncompress BMP images with the header zeroed out. The headers are hardcoded in the executable.

It is sufficient to fix up the following bytes to make the images readable:

| Offset | Length | Type   | Description
|-------:|-------:|--------|-------------
|     12 |      4 |  int32 | Width
|     16 |      4 |  int32 | Height
|     1A |      2 |  int16 | Color planes (1)
|     1C |      2 |  int16 | Bits per pixel (16)
