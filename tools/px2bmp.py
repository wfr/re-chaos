#!/usr/bin/env python3
import os
import re
import shutil
import math
import sys
from pathlib import Path
from optparse import OptionParser


usage = "usage: %prog [options] /path/to/DATA/PX16/"
parser = OptionParser(usage=usage)
parser.add_option("--cpp",
                  action="store_true", dest="cpp", default=False,
                  help="print the C++ definition for all images")
(options, args) = parser.parse_args()

if len(args) == 1:
    px16 = Path(args[0]).expanduser()
    if not px16.is_dir():
        print("not a directory:", px16, file=sys.stderr)
else:
    parser.print_help()
    sys.exit(1)


def fix_bmp(path, width, height):
    with open(path, "r+b") as f:
        f.seek(0x12)
        f.write(width.to_bytes(4, byteorder='little'))
        f.seek(0x16)
        f.write(height.to_bytes(4, byteorder='little'))
        f.seek(0x1A)
        f.write((1).to_bytes(1, byteorder='little'))

if options.cpp:
    print('''static std::map<std::string, std::pair<uint16_t, uint16_t>> image_sizes = {''')

for path in sorted(px16.glob("PX*")):
    if path.suffix:
        continue
    
    outpath = path.with_suffix(".bmp")
    filesize = os.stat(path).st_size

    if path.name in ['PX00100', 'PX00128', 'PX00130', 'PX00143', 'PX00144', 'PX00145', 'PX00146']:
        width = 640
        height = 460
    elif path.name in ['PX00132']:
        width = 108
        height = 164
    elif path.name in ['PX00129']:
        width = 512
        height = 646
    elif path.name in ['PX00137', 'PX00139']:
        width = 220
        height = 72
    elif path.name in ['PX00138'] or filesize == 69174:
        width = 720
        height = 48
    elif filesize == 176022:
        width = 312
        height = 282
    elif filesize == 24694:
        width = 220
        height = 56
    elif filesize == 351014: # PX00200
        width = 428
        height = 410
    elif filesize == 153654: # PX00201
        width = 320
        height = 240
    elif filesize == 245286: # PX00202
        width = 312
        height = 393
    elif filesize == 41526: # PX00300
        width = 324
        height = 64
    elif filesize == 337974: # PX02000
        width = 120
        height = 1408
    elif filesize == 737334: # PX03000
        width = 640
        height = 576
    elif filesize == 51254: # PX04999
        width = 20
        height = 1280
    elif filesize == 143846: # PX05000
        width = 344
        height = 209
    elif filesize == 76526:
        width = 242
        height = 157
    elif filesize == 76042: # PX06008
        width = 242
        height = 157
    elif re.match(r'^PX07\d\d\d$', path.name):
        width = 512
        height = 64
    elif re.match(r'^PX1000\d$', path.name):
        width = 432
        height = 416
    else:
        raise "dimensions missing for {}".format(path.name)

    if options.cpp:
        print('''   {{ "{:s}", {{ {:d}, {:d} }} }},'''.format(
            path.name, width, height))
    else:
        print("{} => {} ({}, {})".format(path.name, outpath.name, width, height))
        shutil.copyfile(path, outpath)
        fix_bmp(outpath, width, height)

if options.cpp:
    print('''};''')

# vim:set expandtab tabstop=4 shiftwidth=4 softtabstop=4 nowrap:

