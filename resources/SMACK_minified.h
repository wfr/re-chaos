
typedef struct SmackTag {
  unsigned int Version;           // SMK2 only right now
  unsigned int Width;             // Width (1 based, 640 for example)
  unsigned int Height;            // Height (1 based, 480 for example)
  unsigned int Frames;            // Number of frames (1 based, 100 = 100 frames)
  unsigned int MSPerFrame;        // Frame Rate
  unsigned int SmackerType;       // bit 0 set=ring frame
  unsigned int LargestInTrack[7]; // Largest single size for each track
  unsigned int tablesize;         // Size of the init tables
  unsigned int codesize;          // Compression info   
  unsigned int absize;            // ditto
  unsigned int detailsize;        // ditto
  unsigned int typesize;          // ditto
  unsigned int TrackType[7];      // high byte=0x80-Comp,0x40-PCM data,0x20-16 bit,0x10-stereo
  unsigned int extra;             // extra value (should be zero)
  unsigned int NewPalette;        // set to one if the palette changed
  unsigned char  Palette[772];      // palette data
  unsigned int PalType;           // type of palette
  unsigned int FrameNum;          // Frame Number to be displayed
  unsigned int FrameSize;         // The current frame's size in bytes
  unsigned int SndSize;           // The current frame sound tracks' size in bytes
  int LastRectx;         // Rect set in from SmackToBufferRect (X coord)
  int LastRecty;         // Rect set in from SmackToBufferRect (Y coord)
  int LastRectw;         // Rect set in from SmackToBufferRect (Width)
  int LastRecth;         // Rect set in from SmackToBufferRect (Height)
  unsigned int OpenFlags;         // flags used on open
  unsigned int LeftOfs;           // Left Offset used in SmackTo
  unsigned int TopOfs;            // Top Offset used in SmackTo
  unsigned int LargestFrameSize;  // Largest frame size
  unsigned int Highest1SecRate;   // Highest 1 sec data rate
  unsigned int Highest1SecFrame;  // Highest 1 sec data rate starting frame
  unsigned int ReadError;         // Set to non-zero if a read error has ocurred
  unsigned int addr32;            // translated address for 16 bit interface
} Smack;              


typedef struct SmackSumTag {
  unsigned int TotalTime;         // total time
  unsigned int MS100PerFrame;     // MS*100 per frame (100000/MS100PerFrame=Frames/Sec)
  unsigned int TotalOpenTime;     // Time to open and prepare for decompression
  unsigned int TotalFrames;       // Total Frames displayed
  unsigned int SkippedFrames;     // Total number of skipped frames
  unsigned int SoundSkips;        // Total number of sound skips
  unsigned int TotalBlitTime;     // Total time spent blitting
  unsigned int TotalReadTime;     // Total time spent reading 
  unsigned int TotalDecompTime;   // Total time spent decompressing
  unsigned int TotalBackReadTime; // Total time spent reading in background
  unsigned int TotalReadSpeed;    // Total io speed (bytes/second)
  unsigned int SlowestFrameTime;  // Slowest single frame time
  unsigned int Slowest2FrameTime; // Second slowest single frame time
  unsigned int SlowestFrameNum;   // Slowest single frame number
  unsigned int Slowest2FrameNum;  // Second slowest single frame number
  unsigned int AverageFrameSize;  // Average size of the frame
  unsigned int HighestMemAmount;  // Highest amount of memory allocated
  unsigned int TotalExtraMemory;  // Total extra memory allocated
  unsigned int HighestExtraUsed;  // Highest extra memory actually used
} SmackSum;



typedef struct _SMACKBLIT {
  unsigned int Flags;
  unsigned char * Palette;
  unsigned int PalType;
  unsigned short * SmoothTable;
  unsigned short * Conv8to16Table;
  unsigned int whichmode;
  unsigned int palindex;
  unsigned int t16index;
  unsigned int smoothindex;
  unsigned int smoothtype;
  unsigned int firstpalette;
} SMACKBLIT;



typedef struct SmackBufTag {
  unsigned int Reversed;             // 1 if the buffer is upside down
  unsigned int SurfaceType;          // SMACKSURFACExxxx defines
  unsigned int BlitType;             // SMACKxxxxBLIT defines
  unsigned int FullScreen;           // 1 if full-screen
  unsigned int Width;
  unsigned int Height;
  unsigned int Pitch;
  unsigned int Zoomed;
  unsigned int ZWidth;
  unsigned int ZHeight;
  unsigned int DispColors;           // colors on the screen
  unsigned int MaxPalColors;         // total possible colors in palette (usually 256)
  unsigned int PalColorsInUse;       // Used colors in palette (usually 236)
  unsigned int StartPalColor;        // first usable color index (usually 10)
  unsigned int EndPalColor;          // last usable color index (usually 246)
  RGBQUAD Palette[256];
  unsigned int PalType;
  unsigned int forceredraw;  // force a complete redraw on next blit (for >8bit)
  unsigned int didapalette;  // force an invalidate on the next palette change

  void * Buffer;
  void * DIBRestore;
  unsigned int OurBitmap;
  unsigned int OrigBitmap;
  unsigned int OurPalette;
  unsigned int WinGDC;
  unsigned int FullFocused;
  unsigned int ParentHwnd;
  unsigned int OldParWndProc;
  unsigned int OldDispWndProc;
  unsigned int DispHwnd;
  unsigned int WinGBufHandle;
  void * lpDD;
  void * lpDDSP;
  unsigned int DDSurfaceType;
  unsigned int DDblit;
  int ddSoftwarecur;
  int didaddblit;
  int lastwasdd;
  RECT ddscreen;
  int manyblits;
  int * blitrects;
  int * rectsptr;
  int maxrects;
  int numrects;
  HDC lastdc;
} SmackBuf;

