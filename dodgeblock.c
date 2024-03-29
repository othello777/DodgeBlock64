#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include <stdbool.h>
#include <stdlib.h>

/* hardware definitions */
#define HZ 60

// Pad buttons
#define A_BUTTON(a)     ((a) & 0x8000)
#define B_BUTTON(a)     ((a) & 0x4000)
#define Z_BUTTON(a)     ((a) & 0x2000)
#define START_BUTTON(a) ((a) & 0x1000)

// D-Pad
#define DU_BUTTON(a)    ((a) & 0x0800)
#define DD_BUTTON(a)    ((a) & 0x0400)
#define DL_BUTTON(a)    ((a) & 0x0200)
#define DR_BUTTON(a)    ((a) & 0x0100)

// Triggers
#define TL_BUTTON(a)    ((a) & 0x0020)
#define TR_BUTTON(a)    ((a) & 0x0010)

// Yellow C buttons
#define CU_BUTTON(a)    ((a) & 0x0008)
#define CD_BUTTON(a)    ((a) & 0x0004)
#define CL_BUTTON(a)    ((a) & 0x0002)
#define CR_BUTTON(a)    ((a) & 0x0001)

#define PAD_DEADZONE     5
#define PAD_ACCELERATION 10
#define PAD_CHECK_TIME   40

#define CHANNEL_SFX1    0

unsigned short gButtons = 0;
struct controller_data gKeys;
int fontsize = 1;
volatile int gTicks; // incremented every vblank
#ifndef NULL
	#define NULL 0
#endif
wav64_t sfx_beep;
int MusicCMDs[255][2];
int MusicTick = 0;
int MusicIndex = 0;
bool PlayingMusic = false;
bool PlayingSfx = false;
int SfxIndex = 0;
int sfxCMDs[7][2] = {
		{1000, 50},
		{1000, 50},
		{600, 50},
		{400, 50},
		{200, 50},
		{100, 50},
		{-1, -1},
	};


static void initMusic()
{
	int index = 0;
	void Beep(float freq, int ms)
	{
		MusicCMDs[index][0] = freq;
		MusicCMDs[index][1] = ms;
		index++;
	}
	void Sleep(int ms)
	{
		MusicCMDs[index][0] = 0;
		MusicCMDs[index][1] = ms;
		index++;
	}
	// 800 = 1/4 note
	// 400 = 8th note
	// 200 16th note

	//----
	Beep(480, 200);
	Beep(480, 200);

	Beep(1568, 200);

	Beep(1568, 200);

	Beep(1568, 200);



	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(783.99, 200);



	Beep(369.99, 200);

	Beep(392, 200);

	Beep(369.99, 200);

	Beep(392, 200);



	Beep(392, 400);

	Beep(196, 400);

	//---- start

	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(739.99, 200);



	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(739.99, 200);

	Beep(830.99, 200);



	Beep(880, 200);

	Beep(830.61, 200);

	Beep(880, 200);


	Beep(987.77, 400);


	Beep(880, 200);

	Beep(783.99, 200);

	Beep(698.46, 200);

	//----

	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(739.99, 200);



	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(739.99, 200);

	Beep(783.99, 200);



	Beep(880, 200);

	Beep(830.61, 200);

	Beep(880, 200);

	Beep(987.77, 400);

	//Thread.Sleep(200);

	//Beep(1108, 10);
	Beep(1174.7, 200);
	//Beep(1480, 10);
	Beep(1568, 200);

	Sleep(200);

	//---

	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(783.99, 200);

	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(880, 200);

	Beep(830.61, 200);

	Beep(880, 200);

	Beep(987.77, 400);


	Beep(880, 200);

	Beep(783.99, 200);

	Beep(698.46, 200);


	Beep(659.25, 200);

	Beep(698.46, 200);

	Beep(784, 200);

	Beep(880, 400);

	Beep(784, 200);

	Beep(698.46, 200);

	Beep(659.25, 200);



	Beep(587.33, 200);

	Beep(659.25, 200);

	Beep(698.46, 200);

	Beep(784, 400);

	Beep(698.46, 200);

	Beep(659.25, 200);

	Beep(587.33, 200);



	Beep(523.25, 200);

	Beep(587.33, 200);

	Beep(659.25, 200);

	Beep(698.46, 400);

	Beep(659.25, 200);

	Beep(587.33, 200);

	Beep(493.88, 200);

	Beep(523.25, 200);


	Sleep(400);
	Beep(349.23, 400);

	Beep(392, 200);

	Beep(329.63, 200);

	Beep(523.25, 200);

	Beep(493.88, 200);

	Beep(466.16, 200);



	Beep(440, 200);

	Beep(493.88, 200);

	Beep(523.25, 200);

	Beep(880, 200);

	Beep(493.88, 200);

	Beep(880, 200);

	Beep(1760, 200);

	Beep(440, 200);



	Beep(392, 200);

	Beep(440, 200);

	Beep(493.88, 200);

	Beep(783.99, 200);

	Beep(440, 200);

	Beep(783.99, 200);

	Beep(1568, 200);

	Beep(392, 200);



	Beep(349.23, 200);

	Beep(392, 200);

	Beep(440, 200);

	Beep(698.46, 200);

	Beep(415.2, 200);

	Beep(698.46, 200);

	Beep(1396.92, 200);

	Beep(349.23, 200);



	Beep(329.63, 200);

	Beep(311.13, 200);

	Beep(329.63, 200);

	Beep(659.25, 200);

	Beep(698.46, 400);

	Beep(783.99, 400);



	Beep(440, 200);

	Beep(493.88, 200);

	Beep(523.25, 200);

	Beep(880, 200);

	Beep(493.88, 200);

	Beep(880, 200);

	Beep(1760, 200);

	Beep(440, 200);



	Beep(392, 200);

	Beep(440, 200);

	Beep(493.88, 200);

	Beep(783.99, 200);

	Beep(440, 200);

	Beep(783.99, 200);

	Beep(1568, 200);

	Beep(392, 200);



	Beep(349.23, 200);

	Beep(392, 200);

	//Beep(440, 00);

	Beep(698.46, 200);

	Beep(659.25, 200);

	Beep(698.46, 200);

	Beep(739.99, 200);

	Beep(783.99, 200);

	Beep(392, 200);

	Beep(392, 200);

	Beep(392, 200);

	Beep(392, 200);

	Beep(196, 200);

	Beep(196, 200);

	Beep(196, 200);



	Beep(185, 200);

	Beep(196, 200);

	Beep(185, 200);

	Beep(196, 200);

	Beep(207.65, 200);

	Beep(220, 200);

	Beep(233.08, 200);

	Beep(246.94, 200);

	MusicCMDs[index][0] = -1;
	MusicCMDs[index][1] = -1;
}

static void updateMusic()
{
	if(MusicTick <= gTicks && PlayingMusic)//end of command, begin next
	{
		//if(!(MusicIndex == 0 && mixer_ch_playing(CHANNEL_SFX1)))
		MusicIndex++;
		mixer_ch_stop(CHANNEL_SFX1);//stop previous note
		if(MusicCMDs[MusicIndex][1] == -1) //if reached end, restart
			MusicIndex = 0;
		MusicTick = gTicks + (MusicCMDs[MusicIndex][1] / (1000.0 / 60.0));
		if(MusicCMDs[MusicIndex][0] > 0){
			wav64_play(&sfx_beep, CHANNEL_SFX1);
			int f = MusicCMDs[MusicIndex][0];
			//snprintf(smolbuf1, 20, "       Score: %d", Score);
			debugf("TEST: %d \n", f);
			mixer_ch_set_freq(CHANNEL_SFX1, sfx_beep.wave.frequency * (MusicCMDs[MusicIndex][0]/220.0));
		}
	}
	if(MusicTick <= gTicks && PlayingSfx)//end of command, begin next
	{
		mixer_ch_stop(CHANNEL_SFX1);//stop previous note
		SfxIndex++;
		if(sfxCMDs[SfxIndex][1] == -1) //if reached end, stop
		{
			SfxIndex = 0;
			PlayingSfx = false;
		}
		MusicTick = gTicks + (sfxCMDs[SfxIndex][1] / (1000.0 / 60.0));
		if(sfxCMDs[SfxIndex][0] > 0){
			wav64_play(&sfx_beep, CHANNEL_SFX1);
			mixer_ch_set_freq(CHANNEL_SFX1, sfx_beep.wave.frequency * (sfxCMDs[SfxIndex][0] / 220.0));
		}
	}
	if (audio_can_write() && (PlayingMusic || PlayingSfx))
	{
		short *buf = audio_write_begin();
		mixer_poll(buf, audio_get_buffer_length());
		audio_write_end();
	}
}

/* input - do getButtons() first, then getAnalogX() and/or getAnalogY() */
unsigned short getButtons(int pad)
{
    // Read current controller status
    controller_scan();
    gKeys = get_keys_pressed();
    return (unsigned short)(gKeys.c[0].data >> 16);
}

unsigned char getAnalogX(int pad)
{
    return (unsigned char)gKeys.c[pad].x;
}

unsigned char getAnalogY(int pad)
{
    return (unsigned char)gKeys.c[pad].y;
}

display_context_t lockVideo(int wait)
{
    display_context_t dc;

    if (wait)
        while (!(dc = display_lock()));
    else
        dc = display_lock();
    return dc;
}

void unlockVideo(display_context_t dc)
{
    if (dc)
        display_show(dc);
}

/* text functions */
void drawText(display_context_t dc, char *msg, int x, int y)
{
    if (dc)
        graphics_draw_text(dc, x, y, msg);
}

void printText(display_context_t dc, char *msg, int x, int y)
{
    if (dc)
        graphics_draw_text(dc, x*8*fontsize, y*8*fontsize, msg);
}

/* vblank callback */
void vblCallback(void)
{
    gTicks++;
}

void delay(int cnt)
{
    int then = gTicks + cnt + 1;
    while (then > gTicks)
    {
    	updateMusic();
    }
}

/* initialize console hardware */
void init_n64(void)
{
    /* Initialize peripherals */
    display_init( RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_OFF );

    register_VI_handler(vblCallback);

    controller_init();

    int ret = dfs_init(DFS_DEFAULT_LOCATION);
	assert(ret == DFS_ESUCCESS);

	debug_init_isviewer();

	audio_init(44100, 4);
	mixer_init(4);  // Initialize up to 4 channels
	wav64_open(&sfx_beep, "rom:/square.wav64");
	mixer_ch_set_limits(CHANNEL_SFX1, 0, 128000, 0);
	initMusic();
}

bool is_rumble_present(void)
{
    const int controllers = get_controllers_present();
    if (controllers & CONTROLLER_1_INSERTED)
    {
        const int accessories = get_accessories_present(NULL);
        if (accessories & CONTROLLER_1_INSERTED)
        {
            return identify_accessory(0) == ACCESSORY_RUMBLEPAK;
        }
    }
    return false;
}

static display_context_t _dc;
static sprite_t *custom_font;

/*#ifndef bool
	typedef enum { false, true } bool;
#endif*/
//#define bool _Bool;

//_____________________________________________________________________________________
// CORE START
//_____________________________________________________________________________________

//characters
static char Avatar;
static char Avatar2;
static char BonusPoint;
static char Backdrop;
static char Block;

//static Random random1 = new Random(DateTime.Now.Millisecond);
//static Random random2 = new Random(DateTime.Now.Second);
//static Write write = new Write();
//static GameMusic music = new GameMusic();
static char Stringbuilder[777]; // new StringBuilder();
//static KeyCode PressedKey = KeyCode.None;
//static KeyCode JustPressedKey = KeyCode.None;
static char WriteBoard[777];
//static char *Version = "1.5.2 - RB";
//static char *Title = dostrcat("DodgeBlock ", Version);
static int MaxMode = 4;
//static char *settingslocation;
//static char *SecretCode = "You have not died yet.";
//static bool loadsuccess;
static bool FlasherFlipFlop;
static bool PowerFliper;
static bool MuteMusic;
static bool MuteSfx;
static bool Refresh;
static bool GodMode;
static bool Quitting;
static bool TwoPlayerMode;
static bool AdminPlayer2;
static bool FullScreen;
static bool ColorMode;
static bool raadmodetimerding;
//static bool IsHolloween;
//static bool IsThanksgiving;
//static bool IsChristmas;
static bool UseNewControls;
static bool AllowInternet;
static bool UseCheckpoints;
static int BoardSize;
static int ScrResX;
static int ScrResY;
static int FlasherCounter;
static int TimerCounter;
static int ScoreFlashTimer;
static int explosiontimer;
static int snowflaketimer;
static int timer10;
static int timer100;
static int timer300;
static int MusicSelector;
//static ShotC shotc = new ShotC();
//static Bench BenchFPS = new Bench();
//static CustomModeC customModeC;
static int Ammo;
static int Shields;
static int Mode;
static int Score;
static int HighScore;
static int Tick;
static int BlockTickBase;
static int BlockTick;
static int BlockTickCounter;
static int CurveTimer;
static int GameWidth;
static int GameHeight;
static int Position;
static int Position2;
static int OldPosition;
static int OldPosition2;
static char BackBoard[20][20];
static char UseBoard[20][20];
static int button;

static char slog[20][40];
static int initfill = 0;
static int vl = 6;
static bool bluebg = false;
static int savedkey;
bool rumbling = false;

typedef enum {
		Black,
		White,
		Green,
		Yellow,
		Magenta,
		Red,
		Blue,
		Cyan,
		DarkMagenta,
		DarkGreen,
		DarkGray
} ConsoleColor;

static void dosnprintf(char * buf, int bufsize, char * formatted, ...)
{
	/*
	va_list va;
	va_start (va, formatted);
	vsnprintf(buf, bufsize, formatted, va);
	va_end (va);
	*/
}

static void dostrcat(char * to, const char * from)
{
	strcat(to, from);
}

static void dostrcpy(char * to, const char * from)
{
	strcpy(to, from);
}

static int GetRand(int from, int to)
{
	return from + (rand() / (RAND_MAX/(to - from)));
}

static int GetRand2(int from, int to)
{
	return GetRand(from, to);
}

static void SetFont(int fontsz)
{
	if(fontsz == 1)
		graphics_set_default_font();
	if(fontsz == 2)
		graphics_set_font_sprite( custom_font );
	fontsize = fontsz;
}

static void TextBoxReplace(char *input)
{
	char str[strlen(input) + 1];
	dostrcpy(str, input);
	char *save;
	char delim[] = "\n";
	char *ptr = strtok_r(str, delim, &save);
	int line = 0;
	unsigned int color;
	_dc = lockVideo(1);
	graphics_fill_screen(_dc, graphics_make_color(0x00, 0x00, 0xFF * bluebg, 0xFF));
	while(ptr != NULL)
	{
		//char **result = malloc(255);
		char *save2;
		char delim2[] = "\\";
		char *ptr2 = strtok_r(ptr, delim2, &save2);
		int col = 0;
		void setcolor(int r, int g, int b)
		{
			color = graphics_make_color(r, g, b, 0xFF);
			graphics_set_color(color, 0);
			memmove(ptr2, ptr2+1, strlen(ptr2));
		}
		while(ptr2 != NULL)
		{
			if(ptr2 != NULL)
				if(ptr2[0] == 'c')
					memmove(ptr2, ptr2+2, strlen(ptr2));
			//bool startofline = false;
			switch (ptr2[0])
			{
				case '0':
					color = Black;
					setcolor(0x00, 0x00, 0x00);
					break;
				case '1':
					setcolor(0xFF, 0xFF, 0xFF);
					break;
				case '2':
					color = Green;
					setcolor(0,255,0);
					break;
				case '3':
					color = Yellow;
					setcolor(255,255,0);
					break;
				case '4':
					color = Magenta;
					setcolor(255,0,255);
					break;
				case '5':
					color = Red;
					setcolor(255,0,0);
					break;
				case '6':
					color = Blue;
					setcolor(0,0,255);
					break;
				case '7':
					color = Cyan;
					setcolor(0,255,255);
					break;
				case '8':
					color = DarkMagenta;
					setcolor(255,120,0);
					break;
				case '9':
					color = DarkGreen;
					setcolor(0,100,0);
					break;
				default:
					//startofline = true;
					break;
			}
			printText(_dc, ptr2, col, line + 1);
			col += strlen(ptr2);
			ptr2 = strtok_r(NULL, delim2, &save2);
			//ptr2 = strstr(ptr2, delim2);// tokenize(NULL, save2, ptr, delim2);

		}
		ptr = strtok_r(NULL, delim, &save);
		line = line + 1;
	}
	unlockVideo(_dc);
}

static void TextBoxReplaceRtf(char *string)
{
	TextBoxReplace(string);
}

static void TextBoxWriteLine(char *line)
{
	//puts("log1");
	if(initfill > vl - 1)
	{
		//puts("log2");
		int n = 1;
		while(n <= vl)
		{
			dostrcpy(slog[n - 1], slog[n]);
			n = n + 1;
		}
		dostrcpy(slog[vl], line);

		dostrcpy(slog[initfill], line);
		char lined[350];
		int i = 0;
		while(i <= vl)
		{
			dostrcat(lined, "\n");
			dostrcat(lined, slog[i]);
			i = i + 1;
		}
		TextBoxReplace(lined);
	}
	else
	{
		//puts("log3");
		dostrcpy(slog[initfill], line);
		char lined[64] = "";
		int i = 0;
		//puts("log4");
		while(i <= vl)
		{
			dostrcat(lined, "\n");
			dostrcat(lined, slog[i]);
			i = i + 1;
		}
		//puts("log5");
		TextBoxReplace(lined);
		initfill = initfill + 1;
	}
}

static void TextBoxWriteLineRtf(char *string)
{
	TextBoxReplace(string);
}

static void GameInitialized(void)
{

}

static void BlueBackground(bool toggle)
{
	bluebg = toggle;
}

static void DoSleep(int ms)
{
	delay(HZ / 1000.0 * ms);
}

static bool IsKeyDown(int key)
{
	button = getButtons(0);
	bool pressed = false;

	if((DU_BUTTON(button) || CU_BUTTON(button)) && key == 0)
		pressed = true;
	if((DD_BUTTON(button) || CD_BUTTON(button)) && key == 1)
		pressed = true;
	if((DL_BUTTON(button) || CL_BUTTON(button)) && key == 2)
		pressed = true;
	if((DR_BUTTON(button) || CR_BUTTON(button)) && key == 3)
		pressed = true;

	if(pressed)
	{
		if(key == savedkey)
		{
			return false;
		}
		else
		{
			if(UseNewControls)
				savedkey = key;
			return true;
		}
	}
	if(key == savedkey)
		savedkey = -1;
	return false;
}

static void Initialize(void)
{
	Avatar = 'O';
	Avatar2 = 'S';
	BonusPoint = '$';
	Backdrop = '.';
	Block = '%';

	Score = 0;

	Mode = 1;
	Ammo = 0;
	Shields = 0;
	MusicSelector = 0;
	FlasherCounter = 0;
	TimerCounter = 0;
	ScoreFlashTimer = 0;
	explosiontimer = 0;
	timer10 = 0;
	timer100 = 0;
	timer300 = 0;
	snowflaketimer = 0;
	HighScore = 153;
	//WriteBoard = "";
	//settingslocation = "Settings.txt";
	if (GetRand2(0, 10) % 2 == 1)
		PowerFliper = true;
	else PowerFliper = false;
	MuteMusic = false;
	MuteSfx = false;
	Refresh = true;
	GodMode = false;
	Quitting = false;
	TwoPlayerMode = false;
	AdminPlayer2 = false;
	FullScreen = false;
	ColorMode = true;
	raadmodetimerding = false;
	UseNewControls = true;
	AllowInternet = false;
	UseCheckpoints = true;
	BoardSize = 40;
	ScrResX = 1920;
	ScrResY = 1080;
	Tick = 60;
	BlockTickBase = 6;
	BlockTick = BlockTickBase;
	BlockTickCounter = 0;
	CurveTimer = 0;
	GameWidth = 12;
	GameHeight = 7;
	Position = 6;
	Position2 = 7;
	OldPosition = 6;
	OldPosition2 = 7;
	srand(gTicks);
	//BackBoard = new char[16, 16];
	//write.DestinationFile = settingslocation;

	//Figure out if it is a holiday
	/*if (HolidayTest.IsHoloween())
	{
		IsHolloween = true;
	}
	else if (HolidayTest.IsThanksgiving())
	{
		IsThanksgiving = true;
	}
	else if (HolidayTest.IsChristmas())
	{
		IsChristmas = true;
	}
	else
	{
		IsHolloween = false;
		IsThanksgiving = false;
		IsChristmas = false;
	}

	customModeC = new CustomModeC();
*/
	//Generate Reference
	for (int i = 0; i < GameHeight; i++)
	{
		for (int j = 0; j < GameWidth; j++)
		{
			BackBoard[j][i] = '.';
		}
	}
	for (int i = 0; i < GameHeight; i++)
	{
		for (int j = 0; j < GameWidth; j++)
		{
			UseBoard[j][i] = '.';
		}
	}
	//dostrcpy(UseBoard, BackBoard);//.Clone() as char[,];

	//DiscordDB.DoesWork = false;//= DiscordDB.DiscordInit();

	GameInitialized();

	//DiscordDB.UpdatePresence();
}

/*static void ImportSettings(void)
{
	TextBoxWriteLine("Importing Settings From " + settingslocation);
	try
	{
		string[] Settings = File.ReadAllLines(settingslocation);

		MuteMusic = Boolconvert(Settings[5]);
		MuteSfx = Boolconvert(Settings[7]);
		GodMode = Boolconvert(Settings[9]);
		FullScreen = Boolconvert(Settings[11]);
		AllowInternet = Boolconvert(Settings[13]);
		AdminPlayer2 = Boolconvert(Settings[21]);
		customModeC.BoardX = Convert.ToInt32(Settings[15]);
		customModeC.BoardY = Convert.ToInt32(Settings[17]);
		UseNewControls = Boolconvert(Settings[19]);
		Mode = Convert.ToInt32(Settings[23]);
		customModeC.Tick = Convert.ToInt32(Settings[29]);
		MusicSelector = Convert.ToInt32(Settings[37]);
		UseCheckpoints = Boolconvert(Settings[39]);

		music.init();
		customModeC.SettingsChanged();

		if (IsHolloween || IsChristmas)
		{
			Mode = 4;
		}

		if (FullScreen)
		{
			TextBoxWriteLine("Fullscreening");
			Fullscreen(true);
		}

		loadsuccess = true;
		//ImportHighScore();

		TwoPlayerMode = false;
		ColorMode = true;
		//ConvertTwoPlayerMode();


	}
	catch (Exception ex)
	{
		TextBoxWriteLine("Could not import settings from " + settingslocation + " " + ex);
		TextBoxWriteLine("Press any key to continue...");
		Console.Beep();
		Console.Beep();
		loadsuccess = false;
		////Console.ReadKey();
		DoSleep(2000);
	}

}*/

/*static void InternetConnect()
{
	//See if we are allowed to use Internet
	if (!AllowInternet)
	{
		bool NotAnswered = true;
		while (NotAnswered)
		{
			TextBoxReplace(
				"Would you like to allow DodgeBlock \n" +
				"to connect to dodgeblock.cf to\n" +
				"retrieve basic information?\n \n" +
				"Left = Yes | Right = No");

			if (IsKeyDown(2))
			{
				write.ToThisTxt(13, "1");
				AllowInternet = true;
				NotAnswered = false;
			}
			if (IsKeyDown(3))
			{
				return;
			}
			DoSleep(150);
		}
	}

	TextBoxWriteLine("Connecting to dodgeblock.cf");

	bool Newer = false;
	try
	{
		//fix https error
		ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072;
		ServicePointManager.SecurityProtocol = SecurityProtocolType.Ssl3 | (SecurityProtocolType)(0xc0 | 0x300 | 0xc00);

		//Get Website HTML
		string htmlCode;
		using (WebClient client = new WebClient()) // WebClient class inherits IDisposable
		{
			htmlCode = client.DownloadString("https://dodgeblock.cf/index.html");
		}

		//Calculate if there is a "Newer" version
		int first = htmlCode.IndexOf("<!--$#$-->");
		int last = htmlCode.IndexOf("<!--#$#-->");
		first += 10;
		string DBVER = htmlCode.Substring(first, last - first);


		if (int.Parse(DBVER.Substring(0, 1)) > int.Parse(Version.Substring(0, 1)))
		{
			Newer = true;
		}

		if (int.Parse(DBVER.Substring(0, 1)) >= int.Parse(Version.Substring(0, 1)))
		{
			if (int.Parse(DBVER.Substring(2, 1)) > int.Parse(Version.Substring(2, 1)))
			{
				Newer = true;
			}
		}

		if (int.Parse(DBVER.Substring(0, 1)) >= int.Parse(Version.Substring(0, 1)))
		{
			if (int.Parse(DBVER.Substring(2, 1)) >= int.Parse(Version.Substring(2, 1)))
			{
				if (int.Parse(DBVER.Substring(4, 1)) > int.Parse(Version.Substring(4, 1)))
				{
					Newer = true;
				}
			}
		}
	}
	catch(WebException)
	{
		TextBoxWriteLine("Failed to connect");
	}
	catch (Exception)
	{
		TextBoxWriteLine("Failed to try to connect");
	}

	//Send Reaction
	bool NotReturned = false;
	if (Newer)
		NotReturned = true;
	while (NotReturned)
	{
		TextBoxReplace(
			"A newer version of DodgeBlock is \n" +
			"available from the website (dodgeblock.cf) \n \n" +
			"Press Down to Continue");

		if (IsKeyDown(1))
		{
			NotReturned = false;
		}
		DoSleep(150);
	}
}*/

static void StringBuilderSetColor(int color)
{
	switch (color)
	{
		case Black:
			 dostrcat(Stringbuilder,"\\cf0");
			break;
		case White:
			 dostrcat(Stringbuilder,"\\cf1");
			break;
		case Green:
			 dostrcat(Stringbuilder,"\\cf2");
			break;
		case Yellow:
			 dostrcat(Stringbuilder,"\\cf3");
			break;
		case Magenta:
			 dostrcat(Stringbuilder,"\\cf4");
			break;
		case Red:
			 dostrcat(Stringbuilder,"\\cf5");
			break;
		case Blue:
			 dostrcat(Stringbuilder,"\\cf6");
			break;
		case Cyan:
			 dostrcat(Stringbuilder,"\\cf7");
			break;
		case DarkMagenta:
			 dostrcat(Stringbuilder,"\\cf8");
			break;
		case DarkGreen:
			 dostrcat(Stringbuilder,"\\cf9");
			break;
		/*case DarkGray:
			 dostrcat(Stringbuilder,"\\cf10");
			break;*/
		default:
			 dostrcat(Stringbuilder,"\\cf1");
			break;

	}
}

static void InitConsoleColors(void)
{
	//StringBuilderSetBackgroundColor = ConsoleColor.Black;
	StringBuilderSetColor(White);
}

//also ye old code
static void SettingsMenu(void)
{
	SetFont(1);
	PlayingMusic = false;

	BlueBackground(true);
	StringBuilderSetColor(White);

	TextBoxReplace("  \n     ###########Settings###########\n     "
							"#                            #\n     "
							"#    Right = Mute/Unmute     #\n     "
							"#    Left = Control Type     #\n     "
							"#    Up = Return to Game     #\n     "
							"#                            #\n     "
							"##############################\n     ");
	int ButtonCooldown = 0;
	bool NotReturned = true;

	while (NotReturned)
	{
		if (IsKeyDown(2))
		{
			if (UseNewControls == true && ButtonCooldown == 0)
			{
				TextBoxWriteLine("Old Control Style");
				UseNewControls = false;
				ButtonCooldown = 5;
			}
			else if (UseNewControls == false && ButtonCooldown == 0)
			{
				TextBoxWriteLine("New Control Style");
				UseNewControls = true;
				ButtonCooldown = 5;
			}
		}

		if (IsKeyDown(3))
		{
			if (MuteMusic == true && ButtonCooldown == 0)
			{
				TextBoxWriteLine("Unmuted");
				MuteMusic = false;
				ButtonCooldown = 5;
			}
			else if (MuteMusic == false && ButtonCooldown == 0)
			{
				TextBoxWriteLine("Muted");
				MuteMusic = true;
				ButtonCooldown = 5;
			}
		}

		if (IsKeyDown(0))
		{
			NotReturned = false;
			InitConsoleColors();
		}

		if (ButtonCooldown > 0)
			ButtonCooldown = ButtonCooldown - 1;

		DoSleep(60);
	}
	if (MuteMusic == false)
		PlayingMusic = true;
	BlueBackground(false);
	SetFont(2);

}

static void TestKeydowns(void)
{
	//NativeKeyboard.Update();

	//Test Keydowns
	if (IsKeyDown(2))
	{
		OldPosition = Position;
		Position = Position - 1;
		if (Position < 0)
			Position = 0;
	}
	if (IsKeyDown(3))
	{
		OldPosition = Position;
		Position = Position + 1;
		if (Position > GameWidth - 1)
			Position = GameWidth - 1;
	}
	if (IsKeyDown(0))
	{
		/*if (!shotc.IsAlive && Ammo > 0 && shotc.ShootCooldown == 0)
		{
			Ammo -= 1;

			shotc.Y = 0;
			shotc.X = Position;
			shotc.IsAlive = true;

			shotc.ShootCooldown = 4;
		}*/
	}

	if (IsKeyDown(1))
	{
		if (Quitting == false)
		{
			SettingsMenu();
		}

	}
}

static void PositionPlayers(void)
{
	//Position
	UseBoard[Position][0] = 'O';
	if (OldPosition != Position && UseBoard[OldPosition][0] == 'O')
		UseBoard[OldPosition][0] = '.';

	//Design Shield (Shell)
	if (Shields > 0)
	{
		if (UseBoard[Position][1] == '.' || UseBoard[Position][1] == '%' || UseBoard[Position][1] == '-')
		{

			UseBoard[Position][1] = '-';

		}

		if (OldPosition != Position && UseBoard[OldPosition][1] == '-')
			UseBoard[OldPosition][1] = '.';
	}
}

/*static ConsoleColor StringBuilderSetBackgroundColor
{
	set
	{

		switch (value)
		{
			case ConsoleColor.Black:
				 dostrcat(Stringbuilder,"\highlight0");
				break;
			case ConsoleColor.White:
				 dostrcat(Stringbuilder,"\highlight1");
				break;
			case ConsoleColor.Magenta:
				 dostrcat(Stringbuilder,"\highlight4");
				break;
			case ConsoleColor.Green:
				 dostrcat(Stringbuilder,"\highlight2");
				break;
			case ConsoleColor.Yellow:
				 dostrcat(Stringbuilder,"\highlight3");
				break;
			case ConsoleColor.Red:
				 dostrcat(Stringbuilder,"\highlight5");
				break;
			case ConsoleColor.Blue:
				 dostrcat(Stringbuilder,"\highlight6");
				break;
			case ConsoleColor.Cyan:
				 dostrcat(Stringbuilder,"\highlight7");
				break;
			default:
				 dostrcat(Stringbuilder,"\highlight0");
				break;

		}


	}
}*/

static void InitStringBuilder(void)
{
	//prepare Stringbuilder
	dostrcpy(Stringbuilder, "");
	//Stringbuilder +=  ("" + BoardSize);
	StringBuilderSetColor(White);
	//if (Mode == 4 && customModeC.CustomModeAble)
	//	 dostrcat(Stringbuilder,"        Score:" + Score +  @" \n\n "
	//	   + "                     " + Math.Round(BenchFPS.DoGetFps(), 5) + "FPS");
	//else
	char smolbuf1[20];
	snprintf(smolbuf1, 20, "       Score: %d", Score);
	//dostrcat(Stringbuilder, smolbuf1);

	char smolbuf2[40];
	snprintf(smolbuf2, 40, "%s\n  High Score: %d\n", smolbuf1, HighScore);
	dostrcat(Stringbuilder, smolbuf2);
	//+ "                     " + Math.Round(BenchFPS.DoGetFps(), 5) + "FPS");
}

static bool Flasher(void)
{
	if (TimerCounter >= FlasherCounter + 10)
	{
		FlasherCounter = TimerCounter;
		if (FlasherFlipFlop)
			FlasherFlipFlop = false;
		else
			FlasherFlipFlop = true;
	}

	return FlasherFlipFlop;
}

static void BoardAppend(void)
{
	if (Mode == 1 /*|| Mode == 4 && !customModeC.CustomModeAble*/)
	{
		char smolbuf1[20];
		snprintf(smolbuf1, 20, "\n\n  Ammo=%d", Ammo);
		char smolbuf2[40];
		snprintf(smolbuf2, 40, "%s Shields=%d\n", smolbuf1, Shields);
		dostrcat(Stringbuilder, smolbuf2);

		InitConsoleColors();
	}
}

static bool CheckPointFlasher(void)
{
	if ((Mode == 0 || Mode == 2) && UseCheckpoints)
		if ((Score >= 1000 && Score <= 1010) || (Score >= 500 && Score <= 510))
			return true;
	return false;
}

static void SetCharacterColor(char character)
{
	switch(character)
	{
	case 'O':
			StringBuilderSetColor(Cyan);
		break;
	case '.':
			StringBuilderSetColor(Blue);
			break;
	case '$':
			StringBuilderSetColor(Magenta);
			break;
	case '%':
			StringBuilderSetColor(White);
			break;
	}
}

static void WriteToScreen(void)
{
	int Margin = 5;
	/*char *BoardToSide[20] =
	{
		"Player1 Arrow Keys",
		"Left&Right = Move",
		"Down = Settings",
		"",
		"",
		"",
		""
	};
	if (Mode == 1)
		BoardToSide[3] = "Up = Shoot";

	BoardToSide[0] = "0";
	BoardToSide[1] = "1";
	BoardToSide[2] = "2";*/

	InitConsoleColors();

	for (int i = GameHeight - 1; i >= 0; i--)
	{
		if ((Score == HighScore && !(Mode == 4/* && customModeC.CustomModeAble*/) && Flasher()) ||
			(ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20) ||
			CheckPointFlasher())
		{
			StringBuilderSetColor(Yellow);

			if (ScoreFlashTimer <= TimerCounter && ScoreFlashTimer >
			TimerCounter - 10 && ColorMode == true && TimerCounter > 20)
				StringBuilderSetColor(Magenta);

			if(CheckPointFlasher())
				StringBuilderSetColor(Cyan);
			 dostrcat(Stringbuilder,"\n  | ");
			InitConsoleColors();
		}
		else
			 dostrcat(Stringbuilder,"\n    ");

		//static char Buff[200];
		for (int j = 0; j < GameWidth; j++)
		{
			//StringBuilderSetBackgroundColor = UseBoard[j, i].BackColor;

			//StringBuilderSetColor(UseBoard[j, i].Color);
			SetCharacterColor((char)UseBoard[j][i]);
			//snprintf(Stringbuilder, 200, "%s", Stringbuilder);//, UseBoard[j][i]);
			char ape[2];// = {((char)UseBoard[j][i])};
			snprintf(ape, 2, "%c", (char)UseBoard[j][i]);
			dostrcat(Stringbuilder, ape);
			//char *a = dostrcat("","");
		}

		// dostrcat(Stringbuilder,"\highlight0 ");

		if ((Score == HighScore && !(Mode == 4/* && customModeC.CustomModeAble*/) && Flasher()) ||
			(ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20) ||
			CheckPointFlasher())
		{
			StringBuilderSetColor(Yellow);
			//Console.BackgroundColor = ConsoleColor.Black;

			if (ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20)
				StringBuilderSetColor(Magenta);

			if (CheckPointFlasher())
				StringBuilderSetColor(Cyan);

			 dostrcat(Stringbuilder," |");
		}
		else
		{
			 dostrcat(Stringbuilder,"  ");
		}
		InitConsoleColors();

		for (int m = 0; m < Margin; m++)
		{
			 dostrcat(Stringbuilder," ");
		}
		//if (GameHeight - 1 - i < sizeof BoardToSide / sizeof BoardToSide[0])
		//	 dostrcat(Stringbuilder,BoardToSide[GameHeight - 1 - i]);



	}

	BoardAppend();

	dostrcpy(WriteBoard, Stringbuilder);
	TextBoxReplaceRtf(WriteBoard);
}

static void FallingObjectTimers(void)
{
	if (TimerCounter >= timer10 + 10)
	{
		timer10 = TimerCounter;
	}

	if (TimerCounter >= timer100 + 100)
	{
		timer100 = TimerCounter;
	}

	if (TimerCounter >= timer300 + 300)
	{
		timer300 = TimerCounter;
	}
}


static void UpdateDificultyCurve(void)
{
	CurveTimer += 1;
	if (CurveTimer >= 250 && BlockTick > 0)
	{
		BlockTick -= 1;
		CurveTimer = 0;
	}
}

static void StringBuilderBuild(void)
{

	//Turn Arrays into a String
	for (int i = GameHeight - 1; i >= 0; i--)
	{
		if (ColorMode)
		{
			if ((Score == HighScore && Flasher()) || (ScoreFlashTimer <= TimerCounter &&
				ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20))
			{
				 dostrcat(Stringbuilder,"\n  | ");
			}
			else
				 dostrcat(Stringbuilder,"\n    ");
		}
		else
		{
			if ((Score == HighScore && Flasher()) || (ScoreFlashTimer <= TimerCounter &&
				ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20))
			{
				 dostrcat(Stringbuilder,"\n  | ");
			}
			else
				 dostrcat(Stringbuilder,"\n    ");
		}
		for (int j = 0; j < GameWidth; j++)
		{
			 //dostrcat(Stringbuilder,(char)UseBoard[j][i]);
			char ape[2];// = {((char)UseBoard[j][i])};
			snprintf(ape, 2, "%c", (char)UseBoard[j][i]);
			dostrcat(Stringbuilder, ape);
		}

		if ((Score == HighScore && Flasher()) || (ScoreFlashTimer <= TimerCounter &&
			ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20))
		{

			 dostrcat(Stringbuilder," |  ");

		}

	}

	dostrcpy(WriteBoard, Stringbuilder);;
}

static void DeathScreen(int Place)
{
	void deathinit(void)
	{
		 dostrcpy(Stringbuilder, "");
		 //dostrcat(Stringbuilder, BoardSize);
		StringBuilderSetColor(Red);
		 dostrcat(Stringbuilder,"\n\n\n \n\n ");
	}
	if (ColorMode)
	{
		deathinit();
		UseBoard[Place][0] = '#';
		StringBuilderBuild();
		TextBoxReplaceRtf(WriteBoard);
		if(is_rumble_present())
		{
			rumble_start(0);
			DoSleep(700);
			rumble_stop(0);
		}
		else
			DoSleep(700);

		deathinit();
		UseBoard[Place][0] = '@';
		StringBuilderBuild();
		TextBoxReplaceRtf(WriteBoard);
		DoSleep(700);

		deathinit();
		UseBoard[Place][0] = 'X';
		StringBuilderBuild();
		TextBoxReplaceRtf(WriteBoard);
		DoSleep(1400);
	}
	/*else
	{
		UseBoard[Place, 0] = '#';
		StringBuilderBuild();
		TextBoxReplace(WriteBoard);
		DoSleep(700);

		InitStringBuilder();//ConsoleColor.White);
		UseBoard[Place, 0] = '@';
		StringBuilderBuild();
		TextBoxReplace(WriteBoard);
		DoSleep(700);

		InitStringBuilder();//ConsoleColor.White);
		UseBoard[Place, 0] = 'X';
		StringBuilderBuild();
		TextBoxReplace(WriteBoard);
		DoSleep(1400);
	}*/
}

//ye old code
/*static void ChangeResolution(int ResolutionX, int ResolutionY)
{
	string FileName = @"c:\qres\qres.exe";
	string FileName2 = @"qres\qres.exe";
	try
	{
		Process proc = new Process();

		proc.StartInfo.FileName = FileName; // put full path in here
		proc.StartInfo.Arguments = ("/x " + ResolutionX + " /y " + ResolutionY).ToString(); // say
		proc.Start();
		proc.WaitForExit();
	}
	catch (System.ComponentModel.Win32Exception)
	{
		try
		{
			Process proc = new Process();

			proc.StartInfo.FileName = FileName2; // put full path in here
			proc.StartInfo.Arguments = ("/x " + ResolutionX + " /y " + ResolutionY).ToString(); // say
			proc.Start();
			proc.WaitForExit();
		}
		catch (System.ComponentModel.Win32Exception)
		{


			TextBoxWriteLine("Fullscreen Mode Error\nUnable to locate " + FileName + " or " + FileName2 +
				"\nPlease Specify the location of QRes.exe");
			TextBoxWriteLine("Press any key to continue...");
			Console.Beep();
			Console.Beep();
			//Console.ReadKey();
			FullScreen = false;
		}
	}
}*/

static void ResetGame(void)
{
	Tick = 60;
	if (Mode > MaxMode)
		Tick = 10;
	if (Mode < 4)
		snowflaketimer = 0;
	Score = 0;
	Ammo = 0;
	Shields = 0;
	CurveTimer = 0;
	GameWidth = 12;
	GameHeight = 7;
	BlockTick = BlockTickBase;
	for (int i = 0; i < GameHeight; i++)
	{
		for (int j = 0; j < GameWidth; j++)
		{
			UseBoard[j][i] = '.';
		}
	}
	//UseBoard = BackBoard.Clone() as char[,];
	TimerCounter = 0;
	ScoreFlashTimer = 0;
	timer10 = 0;
	timer100 = 0;
	timer300 = 0;
	raadmodetimerding = false;

	//customModeC.SettingsChanged();
}

static void DoCheckPoints(int savescore)
{
	if ((Mode == 0 || Mode == 2) && UseCheckpoints)
	{
		if (savescore >= 1000)
		{
			Score = 1000;
			TimerCounter = 1000;
			BlockTick = BlockTickBase - 4;
		}
		else if (savescore >= 500)
		{
			Score = 500;
			TimerCounter = 500;
			BlockTick = BlockTickBase - 2;
		}
	}
}

static void OnDeath(int j)
{
	(void)j;
	PlayingMusic = false;

	if (MuteSfx == false)
		PlayingSfx = true;

	/*// log highscore
	if (loadsuccess && Score == HighScore && !(Mode == 4 && customModeC.CustomModeAble))
	{
		if (Mode == 0)
			write.ToThisTxt(1, HighScore.ToString());
		else if (Mode == 1)
			write.ToThisTxt(25, HighScore.ToString());
		else if (Mode == 2)
			write.ToThisTxt(33, HighScore.ToString());
		else if (Mode == 3)
			write.ToThisTxt(3, HighScore.ToString());
		else if (Mode == 4 && IsHolloween)
			write.ToThisTxt(27, HighScore.ToString());
		else if (Mode == 4 && IsChristmas)
			write.ToThisTxt(35, HighScore.ToString());
	}*/

	// setting deathscreen
	void OnPostDeathScreen(void)
	{
		dostrcpy(Stringbuilder, "");

		/*if (IsHolloween)
		{
			StringBuilderSetColor = ConsoleColor.DarkMagenta;
			 dostrcat(Stringbuilder,"" + BoardSize + " ");
		}
		else if (IsThanksgiving)
		{
			StringBuilderSetColor = ConsoleColor.DarkGray;
			 dostrcat(Stringbuilder,"" + BoardSize + " ");
		}
		else
		{*/
			StringBuilderSetColor(Cyan);
			 //dostrcat(Stringbuilder,"" + BoardSize + " ");
		//}
	}
	// add endline
	void LineBreak(void)
	{
		if (ColorMode)
			dostrcat(Stringbuilder,"\n");
	}

	// kill the bloody loser
	/*if (TwoPlayerMode)
	{
		if (j == Position && j == Position2)
		{
			DeathScreen(Position);
			OnPostDeathScreen();
			 dostrcat(Stringbuilder,"Both Players Died!");
		}
		else if (j == Position2)
		{
			DeathScreen(Position2);
			OnPostDeathScreen();
			 dostrcat(Stringbuilder,"Player2 Died! (" + Avatar2 + ")");
		}
		else
		{
			DeathScreen(Position);
			OnPostDeathScreen();
			 dostrcat(Stringbuilder,"Player1 Died! (" + Avatar + ")");
		}
	}
	else
	{*/
		DeathScreen(Position);
		OnPostDeathScreen();
		dostrcat(Stringbuilder,"\n  You Died!");
	//}
	LineBreak();



	// add the results
	char smolbuf1[20];
	snprintf(smolbuf1, 20, "  Your Score: %d", Score);
	dostrcat(Stringbuilder, smolbuf1);
	LineBreak();
	if (Score >= HighScore)
	{
		StringBuilderSetColor(Yellow);
		dostrcat(Stringbuilder,"  *New High Score!*");
		/*if (ColorMode)
			StringBuilderSetColor = ConsoleColor.Yellow;

		if (IsHolloween)
		{
			StringBuilderSetColor = ConsoleColor.DarkMagenta;
		}
		else if (IsThanksgiving)
		{
			StringBuilderSetColor = ConsoleColor.DarkGray;
		}
		else
		{
			StringBuilderSetColor = ConsoleColor.Cyan;*/
			StringBuilderSetColor(Cyan);
		//}
		LineBreak();
	}
	else
	{
		char smolbuf2[20];
		snprintf(smolbuf2, 20, "  High Score: %d", HighScore);
		dostrcat(Stringbuilder, smolbuf2);
		LineBreak();
	}



	dostrcat(Stringbuilder,"  Playing: \n  ");
	if (Mode == 0)
	{
		 dostrcat(Stringbuilder,"Classic Mode");
	}
	else if (Mode == 1)
	{
		 dostrcat(Stringbuilder,"Normal Mode");
	}
	else if (Mode == 2)
	{
		 dostrcat(Stringbuilder,"Expert Mode");
	}
	/*else if (Mode == 3)
	{
		 dostrcat(Stringbuilder,"Two Player Mode");
	}
	else if (Mode == 4 && IsHolloween)
	{
		 dostrcat(Stringbuilder,"Halloween Event");
	}
	else if (Mode == 4 && IsChristmas)
	{
		 dostrcat(Stringbuilder,"Winter Event");
	}
	else if (Mode == 4)
	{
		 dostrcat(Stringbuilder,"Custom Mode");
	}*/
	else
	{
		 dostrcat(Stringbuilder,"raaad mode");
	}
	if((Mode == 0 || Mode == 2) && UseCheckpoints)
	{
		if (Score > 500)
			LineBreak();
		if (Score > 1000)
			 dostrcat(Stringbuilder,"Checkpoint Achieved: 1000");
		else if (Score > 500)
			 dostrcat(Stringbuilder,"Checkpoint Achieved: 500");
	}

	LineBreak();
	LineBreak();
	 dostrcat(Stringbuilder," \n  Up to Continue");
	LineBreak();
	 dostrcat(Stringbuilder,"  Down to Quit");

	dostrcpy(WriteBoard, Stringbuilder);;
	if (ColorMode)
		TextBoxReplaceRtf(WriteBoard);
	else
		TextBoxReplace(WriteBoard);


	/*if (loadsuccess)
	{
		char *modeAppend;
		if (Mode == 0)
			modeAppend = "C";
		else if (Mode == 1)
			modeAppend = "N";
		else if (Mode == 2)
			modeAppend = "H";
		else if (Mode == 3)
			modeAppend = "T";
		else if (Mode == 4 && (IsHolloween))
			modeAppend = "HW-EVNT";
		else if (Mode == 4 && (IsChristmas))
			modeAppend = "CHR-EVNT";
		//else if (Mode == 4 && (Mode == 4 || customModeC.CustomModeAble))
		//	modeAppend = "CSTM";
		else
			modeAppend = "R";
		//write.ToThisTxt(31, SecretCode);
		GameInitialized();
	}
	else
	{
		SecretCode = "WARNING: Settings.txt not loaded correctly. Please ensure that Settings.txt and Dodgeblock.exe are in the same directory and not zipped!";
		GameInitialized();
	}

	//DiscordDB.UpdatePresence();*/

	bool go = true;
	while (go)
	{
		if (IsKeyDown(0))
		{
			go = false;
		}
		if (IsKeyDown(1))
		{
			go = false;
			Refresh = false;
			Quitting = true;


		}
		DoSleep(80);
	}

	int savescore = TimerCounter;
	ResetGame();
	DoCheckPoints(savescore);

	if (MuteMusic == false)
		PlayingMusic = true;
	InitConsoleColors();
}

static void BlockHandling(void)
{
	if(rumbling)
		rumble_stop(0);
	//=======V====Falling=Objects====V======

	//H axis
	for (int i = 0; i < GameHeight; i++)
	{
		//W axis
		for (int j = 0; j < GameWidth; j++)
		{
			//only on block tick
			if (BlockTickCounter == 0)
			{
				if (UseBoard[j][i] == '$' || UseBoard[j][i] == '~' ||
						UseBoard[j][i] == '^' || UseBoard[j][i] == '%')
				{
					//testfor Bonus
					if (UseBoard[j][i] == '$')
					{
						UseBoard[j][i] = '.';

						//if not on bottom row
						if (i != 0)
						{
							UseBoard[j][i - 1] = '$';

							if ((GodMode == false) && ((j == Position && i == 1) ||
									(TwoPlayerMode == true && j == Position2 && i == 1)))
							{
								Score += 50;
								if(is_rumble_present())
								{
									rumble_start(0);
									rumbling = true;
								}

								ScoreFlashTimer = TimerCounter;
							}
						}
					}

					//testfor PowerUp
					if (UseBoard[j][i] == '^')
					{
						UseBoard[j][i] = '.';

						//if not on bottom row
						if (i != 0)
						{
							UseBoard[j][i - 1] = '^';

							if ((GodMode == false) &&
				((j == Position && i == 1) || (TwoPlayerMode == true && j == Position2 && i == 1)))
							{
								Ammo += 3;
							}
						}
					}
					if (UseBoard[j][i] == '~')
					{
						UseBoard[j][i] = '.';

						//if not on bottom row
						if (i != 0)
						{
							UseBoard[j][i - 1] = '~';

							if ((GodMode == false) &&
					((j == Position && i == 1) || (TwoPlayerMode == true && j == Position2 && i == 1)))
							{
								Shields += 1;
							}
						}
					}

					/*if (UseBoard[j, i] is HalloweenBomb)
					{
						UseBoard[j, i] = '.';

						//if not on bottom row
						if (i != 0)
						{
							UseBoard[j, i - 1] = new HalloweenBomb();

							if ((j == Position && i == 1 || TwoPlayerMode == true && j == Position2 && i == 1))
							{
								for (int z = 0; z < GameHeight; z++)
								{
									for (int l = 0; l < GameWidth; l++)
									{
										if (UseBoard[l, z] == '%')
										{
											UseBoard[l, z] = '.';
										}
									}
								}
								explosiontimer = 5;
								OrangeBackground(true);
							}
						}
					}

					if (UseBoard[j, i] is Snowflake)
					{
						UseBoard[j, i] = '.';

						//if not on bottom row
						if (i != 0)
						{
							UseBoard[j, i - 1] = new Snowflake();

							if ((j == Position && i == 1 || TwoPlayerMode == true && j == Position2 && i == 1))
							{
								for (int z = 0; z < GameHeight; z++)
								{
									for (int l = 0; l < GameWidth; l++)
									{
										if (UseBoard[l, z] == '%')
										{
											UseBoard[l, z] = '.';
										}
									}
								}
								snowflaketimer = 50;
							}
						}
					}*/


					//unsigned char test = UseBoard[j][i];
					//unsigned char test2 = '%';
					//move blocks

					if (UseBoard[j][i] == '%')//test == test2)// || raadmodetimerding)//testforblock
					{

						UseBoard[j][i] = '.';

						if (i != 0)//if not on bottom row
						{

							if (j == Position && i == 2 && Shields > 0)
							{
								Shields -= 1;

								if (Shields == 0 && UseBoard[j][i - 1] == '~')
								{
									UseBoard[j][i - 1] = '.';
								}
							}
							else
								UseBoard[j][i - 1] = '%';

							//would a player die? then kill them if they are not god.
							if (((GodMode == false) && ((j == Position && i == 1) ||
								(TwoPlayerMode == true && j == Position2 && i == 1))) || raadmodetimerding)
							{
								OnDeath(j);
							}

						}
					}
				}
				//DiscordDB.UpdatePresence();
			}//End of blocktick
		}
	}

	//add falling objects
	if (BlockTickCounter == 0)
	{
		//add Blocks or raaadmodethingies
		if (Mode > MaxMode)
			UseBoard[GetRand(0, GameWidth)][GameHeight - 1] = '$';
		else
		{
			if (Mode == 4 && false)//customModeC.CustomModeAble)
			{
				/*for(int i = 0; customModeC.Blocks > i; i++)
				{
					UseBoard[GetRand(0, GameWidth), GameHeight - 1] = '%';
				}*/
			}
			else
			{
				if (snowflaketimer > 0)
					UseBoard[GetRand(0, GameWidth)][GameHeight - 1] = '$';
				else
					UseBoard[GetRand(0, GameWidth)][GameHeight - 1] = '%';

				if (Mode == 2)
				{
					UseBoard[GetRand(0, GameWidth)][GameHeight - 1] = '%';
					UseBoard[GetRand(0, GameWidth)][GameHeight - 1] = '%';
				}
			}
		}
	}



	//Power-Up stuff
	if (snowflaketimer > 0)
	{
		snowflaketimer -= 1;
	}
	/*if (explosiontimer > 0)
	{
		explosiontimer -= 1;
		if (explosiontimer == 1)
		{
			for (int z = 0; z < GameHeight; z++)
			{
				for (int l = 0; l < GameWidth; l++)
				{
					if (UseBoard[l][z] == '%')
					{
						UseBoard[l][z] = '.';
					}
				}
			}
			OrangeBackground(false);
		}
	}*/
	FallingObjectTimers();
	if (Mode == 1 /*|| Mode == 4 && !(Mode == 4 && customModeC.CustomModeAble)*/)
	{
		if (timer100 == TimerCounter && TimerCounter != 0)//add bonuspoints
			UseBoard[GetRand2(0, GameWidth)][GameHeight - 1] = '$';


		if (CurveTimer == 0 && TimerCounter != 0)//add superpower
		{
			/*if (Mode == 4 && IsHolloween)
			{
				UseBoard[GetRand2(0, GameWidth), GameHeight - 1] = new HalloweenBomb();
			}
			if (Mode == 4 && IsChristmas)
			{
				UseBoard[GetRand2(0, GameWidth), GameHeight - 1] = new Snowflake();
			}
			else if (PowerFliper)
			{
				UseBoard[GetRand2(0, GameWidth), GameHeight - 1] = '^';
				PowerFliper = false;
			}
			else if (!PowerFliper)
			{
				UseBoard[GetRand2(0, GameWidth), GameHeight - 1] = '~';
				PowerFliper = true;
			}*/
		}


		//Move Shot
		/*if (shotc.IsAlive)
		{
			//kill block that is on shot
			if (UseBoard[shotc.X, shotc.Y] == '%' && shotc.IsAlive)
			{
				shotc.IsAlive = false;
				UseBoard[shotc.X, shotc.Y] = '.';
			}

			//move shot
			if (shotc.Y != 0)
				UseBoard[shotc.X, shotc.Y] = '.';
			if (shotc.Y < GameHeight - 1 && shotc.IsAlive)
			{
				shotc.Y += 1;

				//kill block that shot moved onto
				if (UseBoard[shotc.X, shotc.Y] == '%')
				{
					shotc.IsAlive = false;
					UseBoard[shotc.X, shotc.Y] = '.';
				}

				if (shotc.IsAlive)
					UseBoard[shotc.X, shotc.Y] = new Shot();
			}
			else
				shotc.IsAlive = false;
		}
		if (shotc.ShootCooldown > 0)
		{
			shotc.ShootCooldown -= 1;
		}*/
	}
	if (TimerCounter == 1500 && Mode > MaxMode)
	{
		raadmodetimerding = true;
	}

	//Update Block Tick
	if (BlockTickCounter > 0)
		BlockTickCounter = BlockTickCounter - 1;
	else
		BlockTickCounter = BlockTick;


}   //=====/\===================/\======

static void StartScreen(void)
{
	TextBoxWriteLine("CONGRATS! starting.");
	DoSleep(1000);

	//if(IsChristmas)
	//	Cutscene();

	int anim = 0;

	bool NotStarted = true;
	while (NotStarted)
	{
		char * introanim[33] = {
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#%......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.O..........................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.%.....@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..O.........................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.%.....@@@@@@@@@@@@.........#\n#...O........................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.....%.@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.%..O.......................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.....&.@@@@@@@@@@@@.........#\n#.%...O......................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.....&O.....................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.....&.O....................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#........O...................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.........O..................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..........O.................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#...........O................#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#............O...............#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#............O...............#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.............O..............#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@....%....#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..............O.............#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @...%.....#\n#.......@@@@@@@@@@@@.........#\n#...............O............#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @...%.....#\n#.......@@@@@@@@@@@@.........#\n#................O...........#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@..%......#\n#.................O..........#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@..%......#\n#..................O.........#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.................O.%........#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..................O.........#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#...................O........#\n##############################\n",
				"##############################\n#........................%...#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#....................O.......#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.....%...#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.....................O......#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.....%...#\n#.......@@@@@@@@@@@@.........#\n#......................O.....#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.....%...#\n#.......................O....#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.......................O%...#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @........%#\n#.......@@@@@@@@@@@@.........#\n#........................O...#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@........%#\n#.........................O..#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.........................O.%#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..........................O.#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#...........................O#\n##############################\n",
				"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @........%#\n#.......@@@@@@@@@@@@.........#\n#............................#\n##############################\n"
		   };
		char smolbuf1[270];
		snprintf(smolbuf1, 270, "\n     Version RockBox \n%s\n   (c) othello7 2019-2022", introanim[anim]);
		TextBoxReplace(smolbuf1);
		anim++;
		if(anim > 32)
			anim = 0;
		//Start Screen
		//Animations.PlayAnimatedStartScreen();

		if (IsKeyDown(0))
		{
			NotStarted = false;
		}
		DoSleep(150);
	}
	TextBoxReplace("");
	//music.PlayMusic();
}

/*static void ConvertTwoPlayerMode()
{
	if (Mode == 3)
		TwoPlayerMode = true;
	else
		TwoPlayerMode = false;
}

static char* Boolconvert(bool setting)
{
	char *str;
	if (setting)
		str = "1";
	else
		str = "0";
	return str;
}
static bool Boolconvert(char* setting)
{
	bool boolean;
	if (setting == "1")
		boolean = true;
	else
		boolean = false;
	return boolean;
}
static void ImportHighScore()
{
	if (loadsuccess)
	{
		try
		{
			string[] Settings = File.ReadAllLines(settingslocation);

			if (Mode == 0)
			{
				HighScore = Convert.ToInt32(Settings[1]);
			}
			else if (Mode == 1)
			{
				HighScore = Convert.ToInt32(Settings[25]);
			}
			else if (Mode == 2)
			{
				HighScore = Convert.ToInt32(Settings[33]);
			}
			else if (Mode == 3)
			{
				HighScore = Convert.ToInt32(Settings[3]);
			}
			else if (Mode == 4 && IsHolloween)
			{
				HighScore = Convert.ToInt32(Settings[27]);
			}
			else if (Mode == 4 && IsChristmas)
			{
				HighScore = Convert.ToInt32(Settings[35]);
			}

		}
		catch (Exception ex)
		{
			TextBoxWriteLine("Could not import settings from " + settingslocation + " " + ex);
			Console.Beep();
			Console.Beep();
			DoSleep(777);
		}
	}
}

//AGAIN whats with all this elden code?
static string Code(string Input)
{
	char[] charArray = Input.ToCharArray();

	int[] intarray = new int[charArray.Length];

	for (int i = 0; i < charArray.Length; i++)
	{
		intarray[i] = (int)charArray[i] + 17;

		charArray[i] = (char)intarray[i];
	}

	string b = new string(charArray);
	return b;
}

static void Cutscene()
{
	ZoomTextBox(ZoomTextBox() / 1.5f, true);


	int FrameCounter = 0;
	bool NotSkipped = true;
	while (NotSkipped)
	{
		TextBoxReplace(Playmation[FrameCounter] +
	"\nAnimated by The King of Ducks \nPress any (arrow) key to skip");

		if (FrameCounter == Playmation.Count - 1)
			NotSkipped = false;
		else
			FrameCounter = FrameCounter + 1;

		if (IsKeyDown(0) ||
			IsKeyDown(1) ||
			IsKeyDown(2) ||
			IsKeyDown(3))
		{
			NotSkipped = false;
		}
		if (FrameCounter < 21)
			DoSleep(200);
		if (FrameCounter < 33)
			DoSleep(100);
		DoSleep(100);
	}
	ZoomTextBox(ZoomTextBox() * 1.5f);
}*/

//Display&Delay
static void DisplayAndDelay(void)
{
	//Display
	WriteToScreen();
	//BenchFPS.OnMapUpdated();

	//Delay
	if (GodMode == false)
		Score += 1;
	TimerCounter += 1;
	UpdateDificultyCurve();
	if (Score > HighScore)
		HighScore = Score;
}

static void Run(void){
	//Run
	while (Refresh){

		TestKeydowns();

		PositionPlayers();

		/*if (ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 &&
				ColorMode == true && TimerCounter > 20)
			InitStringBuilder(ConsoleColor.Magenta);
		else*/
			InitStringBuilder();//ConsoleColor.White);

		BlockHandling();


		dostrcpy(WriteBoard, Stringbuilder);

		DisplayAndDelay();

		DoSleep(Tick);
	}
}

static void Game(void)
{
	TextBoxWriteLine("Start!");
	//init
	TextBoxWriteLine("Initializing");
	Initialize();
	//TextBoxWriteLine("Setting Colors");
	//InitConsoleColors();
	//BlueBackground(false);

	//ImportSettings();

	//InternetConnect();

	TextBoxWriteLine("Start Game");
	DoSleep(200);
	//StartScreen();

	//if (MuteMusic)
	//	music.PauseMusic();
	PlayingMusic = true;

	if (Mode > MaxMode)
	{
		Tick = 10;
		Avatar = '%';
		Avatar2 = '$';
		Backdrop = 'O';
		BonusPoint = '.';
	}



	Run();



	TextBoxWriteLineRtf("\nQuitting...");

	PlayingMusic = false;
	MusicIndex = 0;

	//DiscordDB.die();

	DoSleep(1000);
	//CloseThis();
}

/* main code entry point */
int main(void)
{
	char * introanim[33] = {
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#%......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.O..........................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.%.....@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..O.........................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.%.....@@@@@@@@@@@@.........#\n#...O........................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.....%.@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.%..O.......................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.....&.@@@@@@@@@@@@.........#\n#.%...O......................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.....&O.....................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.....&.O....................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#........O...................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.........O..................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..........O.................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#...........O................#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#............O...............#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#............O...............#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.............O..............#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@....%....#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..............O.............#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @...%.....#\n#.......@@@@@@@@@@@@.........#\n#...............O............#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @...%.....#\n#.......@@@@@@@@@@@@.........#\n#................O...........#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@..%......#\n#.................O..........#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@..%......#\n#..................O.........#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.................O.%........#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..................O.........#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#...................O........#\n##############################\n",
			"##############################\n#........................%...#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#....................O.......#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.....%...#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.....................O......#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.....%...#\n#.......@@@@@@@@@@@@.........#\n#......................O.....#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.....%...#\n#.......................O....#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.......................O%...#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @........%#\n#.......@@@@@@@@@@@@.........#\n#........................O...#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@........%#\n#.........................O..#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#.........................O.%#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#..........................O.#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @.........#\n#.......@@@@@@@@@@@@.........#\n#...........................O#\n##############################\n",
			"##############################\n#............................#\n#.......@@@@@@@@@@@@.........#\n#.......@ Press Up @........%#\n#.......@@@@@@@@@@@@.........#\n#............................#\n##############################\n"
       };
	int anim = 0;
    init_n64();
    rdp_init();
    dfs_init( DFS_DEFAULT_LOCATION );
    /* Read in the custom font */
	int fp = dfs_open("/libdragon-font.sprite");
	custom_font = malloc( dfs_size( fp ) );
	dfs_read( custom_font, 1, dfs_size( fp ), fp );
	dfs_close( fp );

    while (1)
    {
		unsigned int color;

        _dc = lockVideo(1);

        color = graphics_make_color(0x00, 0x00, 0x00, 0xFF);
		graphics_fill_screen(_dc, color);

		color = graphics_make_color(0xFF, 0xFF, 0xFF, 0xFF);
		int pad = 10;
		graphics_draw_line(_dc, pad, pad, 320-pad, pad, color);
		graphics_draw_line(_dc, pad, pad, pad, 240-pad, color);
		graphics_draw_line(_dc, 320-pad, pad, 320-pad, 240-pad, color);
		graphics_draw_line(_dc, pad, 240-pad, 320-pad, 240-pad, color);

		color = graphics_make_color(0xFF, 0xFF, 0xFF, 0xFF);
		graphics_set_color(color, 0);

		printText(_dc, introanim[anim], 5, 5);
		anim++;
		if(anim > 32)
			anim = 0;

        printText(_dc, "DodgeBlock  64", 320/16 - 8, 3);
        printText(_dc, "(c) othello7 2019-2022", 320/16 - 11, 13);

        unlockVideo(_dc);

		if (IsKeyDown(0))
		{
			SetFont(2);
			Game();
			SetFont(1);
		}
        delay(9);
    }
    return 0;
}
