
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

/* hardware definitions */
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


unsigned short gButtons = 0;
struct controller_data gKeys;

volatile int gTicks;                    /* incremented every vblank */

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
        graphics_draw_text(dc, x*8, y*8, msg);
}

/* vblank callback */
void vblCallback(void)
{
    gTicks++;
}

void delay(int cnt)
{
    int then = gTicks + cnt;
    while (then > gTicks) ;
}

/* initialize console hardware */
void init_n64(void)
{
    /* Initialize peripherals */
    display_init( RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );

    register_VI_handler(vblCallback);

    controller_init();
}

static display_context_t _dc;

//#define NULL 0
//typedef enum { false, true } ;

//____________________________________________
// CORE START
//____________________________________________

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
static char Stringbuilder[400]; // new StringBuilder();
//static KeyCode PressedKey = KeyCode.None;
//static KeyCode JustPressedKey = KeyCode.None;
static char WriteBoard[400];
//static char *Version = "1.5.2 - RB";
//static char *Title = strcat("DodgeBlock ", Version);
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
//static int button;

static char slog[7][23];
static int initfill = 0;
static int vl = 6;
//static int randseed = 0;

// Fair and fast random generation (using xorshift32, with explicit seed)
static uint32_t rand_state = 1;
static uint32_t rand(void) {
	uint32_t x = rand_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 5;
	return rand_state = x;
}
#define RANDN(n) ({ \
	__builtin_constant_p((n)) ? \
		(rand()%(n)) : \
		(uint32_t)(((uint64_t)rand() * (n)) >> 32); \
})

static int GetRand(int from, int to)
{
	return from + (int)RANDN(to);//(rand() / (RAND_MAX/(to - from)));
}

static int GetRand2(int from, int to)
{
	return GetRand(from, to);
}

static void TextBoxReplace(char *input)
{
	char str[strlen(input) + 1];
	strcpy(str, input);
	char *save;
	char delim[] = "\n";

	char *ptr = strtok_r(str, delim, &save);

	int line = 0;

	//lcd_clear_display();
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

	while(ptr != NULL)
	{
		printText(_dc, ptr, 3, line + 3);
		//lcd_puts(0, line, ptr);
		ptr = strtok_r(NULL, delim, &save);
		line = line + 1;
	}
	//lcd_update();
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
			strcpy(slog[n - 1], slog[n]);
			n = n + 1;
		}
		strcpy(slog[vl], line);

		strcpy(slog[initfill], line);
		char lined[127] = "";
		int i = 0;
		while(i <= vl)
		{
			strcat(lined, "\n");
			strcat(lined, slog[i]);
			i = i + 1;
		}
		TextBoxReplace(lined);
	}
	else
	{
		//puts("log3");
		strcpy(slog[initfill], line);
		char lined[64] = "";
		int i = 0;
		//puts("log4");
		while(i <= vl)
		{
			strcat(lined, "\n");
			strcat(lined, slog[i]);
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

//static void BlueBackground(bool toggle){}

static void DoSleep(int ms)
{
	delay(60.0 / 1000.0 * ms);
}

static bool IsKeyDown(int key)
{
	unsigned short button = getButtons(0);
	//button = button_status();
		if(DU_BUTTON(button) && key == 0)
			return true;

		if(DD_BUTTON(button) && key == 1)
			return true;

		if(DL_BUTTON(button) && key == 2)
			return true;

		if(DR_BUTTON(button) && key == 3)
			return true;

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
	HighScore = 1530;
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
	rand_state = (int)gTicks;
	//rand_state = GetRand(1, 60);
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
	//strcpy(UseBoard, BackBoard);//.Clone() as char[,];

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

static void InitConsoleColors(void)
{
	//StringBuilderSetBackgroundColor = ConsoleColor.Black;
	//StringBuilderSetColor = ConsoleColor.White;
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
			//NewSettingsMenu.SettingsMenu();
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

/*static ConsoleColor StringBuilderSetColor
{
	set
	{

		switch (value)
		{
			case ConsoleColor.Black:
				 strcat(Stringbuilder,"\cf0");
				break;
			case ConsoleColor.White:
				 strcat(Stringbuilder,"\cf1");
				break;
			case ConsoleColor.Green:
				 strcat(Stringbuilder,"\cf2");
				break;
			case ConsoleColor.Yellow:
				 strcat(Stringbuilder,"\cf3");
				break;
			case ConsoleColor.Magenta:
				 strcat(Stringbuilder,"\cf4");
				break;
			case ConsoleColor.Red:
				 strcat(Stringbuilder,"\cf5");
				break;
			case ConsoleColor.Blue:
				 strcat(Stringbuilder,"\cf6");
				break;
			case ConsoleColor.Cyan:
				 strcat(Stringbuilder,"\cf7");
				break;
			case ConsoleColor.DarkMagenta:
				 strcat(Stringbuilder,"\cf8");
				break;
			case ConsoleColor.DarkGreen:
				 strcat(Stringbuilder,"\cf9");
				break;
			case ConsoleColor.DarkGray:
				 strcat(Stringbuilder,"\cf10");
				break;
			default:
				 strcat(Stringbuilder,"\cf1");
				break;

		}


	}
}

static ConsoleColor StringBuilderSetBackgroundColor
{
	set
	{

		switch (value)
		{
			case ConsoleColor.Black:
				 strcat(Stringbuilder,"\highlight0");
				break;
			case ConsoleColor.White:
				 strcat(Stringbuilder,"\highlight1");
				break;
			case ConsoleColor.Magenta:
				 strcat(Stringbuilder,"\highlight4");
				break;
			case ConsoleColor.Green:
				 strcat(Stringbuilder,"\highlight2");
				break;
			case ConsoleColor.Yellow:
				 strcat(Stringbuilder,"\highlight3");
				break;
			case ConsoleColor.Red:
				 strcat(Stringbuilder,"\highlight5");
				break;
			case ConsoleColor.Blue:
				 strcat(Stringbuilder,"\highlight6");
				break;
			case ConsoleColor.Cyan:
				 strcat(Stringbuilder,"\highlight7");
				break;
			default:
				 strcat(Stringbuilder,"\highlight0");
				break;

		}


	}
}*/

static void InitStringBuilder(void)
{
	//prepare Stringbuilder
	strcpy(Stringbuilder, "");
	//Stringbuilder +=  ("" + BoardSize);
	//StringBuilderSetColor = color;
	//if (Mode == 4 && customModeC.CustomModeAble)
	//	 strcat(Stringbuilder,"        Score:" + Score +  @" \n\n "
	//	   + "                     " + Math.Round(BenchFPS.DoGetFps(), 5) + "FPS");
	//else
	char smolbuf1[20];
	snprintf(smolbuf1, 20, "        Score: %d", Score);
	//strcat(Stringbuilder, smolbuf1);

	char smolbuf2[40];
	snprintf(smolbuf2, 40, "%s\n   High Score: %d\n", smolbuf1, HighScore);
	strcat(Stringbuilder, smolbuf2);
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
		snprintf(smolbuf1, 20, "\n\n Ammo = %d", Ammo);
		char smolbuf2[40];
		snprintf(smolbuf2, 40, "%s Shields = %d\n", smolbuf1, Shields);
		strcat(Stringbuilder, smolbuf2);

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
		if (/*(Score == HighScore && !(Mode == 4 && customModeC.CustomModeAble) && Flasher()) ||*/
(ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && ColorMode == true && TimerCounter > 20) ||
			CheckPointFlasher())
		{
			//StringBuilderSetColor = ConsoleColor.Yellow;

			/*if (ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && ColorMode == true && TimerCounter > 20)
				StringBuilderSetColor = ConsoleColor.Magenta;

			if(CheckPointFlasher())
				StringBuilderSetColor = ConsoleColor.Cyan;*/
			 strcat(Stringbuilder,"\n  | ");
			InitConsoleColors();
		}
		else
			 strcat(Stringbuilder,"\n    ");

		//static char Buff[200];
		for (int j = 0; j < GameWidth; j++)
		{
			//StringBuilderSetBackgroundColor = UseBoard[j, i].BackColor;

			//StringBuilderSetColor = UseBoard[j, i].Color;
			//snprintf(Stringbuilder, 200, "%s", Stringbuilder);//, UseBoard[j][i]);
			char ape[2];// = {((char)UseBoard[j][i])};
			snprintf(ape, 2, "%c", (char)UseBoard[j][i]);
			strcat(Stringbuilder, ape);
			//char *a = strcat("","");
		}

		// strcat(Stringbuilder,"\highlight0 ");

		if ((Score == HighScore && !(Mode == 4/* && customModeC.CustomModeAble*/) && Flasher()) ||
			(ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20) ||
			CheckPointFlasher())
		{
			/*StringBuilderSetColor = ConsoleColor.Yellow;
			Console.BackgroundColor = ConsoleColor.Black;

			if (ScoreFlashTimer <= TimerCounter && ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20)
				StringBuilderSetColor = ConsoleColor.Magenta;

			if (CheckPointFlasher())
				StringBuilderSetColor = ConsoleColor.Cyan;*/

			 strcat(Stringbuilder,"  |");
		}
		else
		{
			 strcat(Stringbuilder,"  ");
		}
		InitConsoleColors();

		for (int m = 0; m < Margin; m++)
		{
			 strcat(Stringbuilder," ");
		}
		//if (GameHeight - 1 - i < sizeof BoardToSide / sizeof BoardToSide[0])
		//	 strcat(Stringbuilder,BoardToSide[GameHeight - 1 - i]);



	}

	BoardAppend();

	strcpy(WriteBoard, Stringbuilder);
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
				 strcat(Stringbuilder,"\n  | ");
			}
			else
				 strcat(Stringbuilder,"\n    ");
		}
		else
		{
			if ((Score == HighScore && Flasher()) || (ScoreFlashTimer <= TimerCounter &&
				ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20))
			{
				 strcat(Stringbuilder,"\n  | ");
			}
			else
				 strcat(Stringbuilder,"\n    ");
		}
		for (int j = 0; j < GameWidth; j++)
		{
			 //strcat(Stringbuilder,(char)UseBoard[j][i]);
			char ape[2];// = {((char)UseBoard[j][i])};
			snprintf(ape, 2, "%c", (char)UseBoard[j][i]);
			strcat(Stringbuilder, ape);
		}

		if ((Score == HighScore && Flasher()) || (ScoreFlashTimer <= TimerCounter &&
			ScoreFlashTimer > TimerCounter - 10 && TimerCounter > 20))
		{

			 strcat(Stringbuilder," |  ");

		}

	}

	strcpy(WriteBoard, Stringbuilder);;
}

static void DeathScreen(int Place)
{
	void deathinit(void)
	{
		 strcpy(Stringbuilder, "");
		 //strcat(Stringbuilder, BoardSize);
		//StringBuilderSetColor = ConsoleColor.Red;
		 strcat(Stringbuilder,"\n\n\n ");
	}
	if (ColorMode)
	{
		deathinit();
		UseBoard[Place][0] = '#';
		StringBuilderBuild();
		TextBoxReplaceRtf(WriteBoard);
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
	/*music.PauseMusic();

	if (MuteSfx == false)
		music.DieNoise();

	// log highscore
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
		strcpy(Stringbuilder, "");

		/*if (IsHolloween)
		{
			StringBuilderSetColor = ConsoleColor.DarkMagenta;
			 strcat(Stringbuilder,"" + BoardSize + " ");
		}
		else if (IsThanksgiving)
		{
			StringBuilderSetColor = ConsoleColor.DarkGray;
			 strcat(Stringbuilder,"" + BoardSize + " ");
		}
		else
		{
			StringBuilderSetColor = ConsoleColor.Cyan;
			 strcat(Stringbuilder,"" + BoardSize + " ");
		}*/
	}
	// add endline
	void LineBreak(void)
	{
		if (ColorMode)
			strcat(Stringbuilder,"\n");
	}

	// kill the bloody loser
	/*if (TwoPlayerMode)
	{
		if (j == Position && j == Position2)
		{
			DeathScreen(Position);
			OnPostDeathScreen();
			 strcat(Stringbuilder,"Both Players Died!");
		}
		else if (j == Position2)
		{
			DeathScreen(Position2);
			OnPostDeathScreen();
			 strcat(Stringbuilder,"Player2 Died! (" + Avatar2 + ")");
		}
		else
		{
			DeathScreen(Position);
			OnPostDeathScreen();
			 strcat(Stringbuilder,"Player1 Died! (" + Avatar + ")");
		}
	}
	else
	{*/
		DeathScreen(Position);
		OnPostDeathScreen();
		strcat(Stringbuilder,"You Died!");
	//}
	LineBreak();



	// add the results
	char smolbuf1[20];
	snprintf(smolbuf1, 20, "Your Score: %d", Score);
	strcat(Stringbuilder, smolbuf1);
	LineBreak();
	if (Score >= HighScore)
	{
		strcat(Stringbuilder,"*New High Score!*");
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
			StringBuilderSetColor = ConsoleColor.Cyan;
		}*/
		LineBreak();
	}
	else
	{
		char smolbuf2[20];
		snprintf(smolbuf2, 20, "High Score: %d", HighScore);
		strcat(Stringbuilder, smolbuf2);
		LineBreak();
	}



	strcat(Stringbuilder,"Playing: ");
	if (Mode == 0)
	{
		 strcat(Stringbuilder,"Classic Mode");
	}
	else if (Mode == 1)
	{
		 strcat(Stringbuilder,"Normal Mode");
	}
	else if (Mode == 2)
	{
		 strcat(Stringbuilder,"Expert Mode");
	}
	/*else if (Mode == 3)
	{
		 strcat(Stringbuilder,"Two Player Mode");
	}
	else if (Mode == 4 && IsHolloween)
	{
		 strcat(Stringbuilder,"Halloween Event");
	}
	else if (Mode == 4 && IsChristmas)
	{
		 strcat(Stringbuilder,"Winter Event");
	}
	else if (Mode == 4)
	{
		 strcat(Stringbuilder,"Custom Mode");
	}*/
	else
	{
		 strcat(Stringbuilder,"raaad mode");
	}
	if((Mode == 0 || Mode == 2) && UseCheckpoints)
	{
		if (Score > 500)
			LineBreak();
		if (Score > 1000)
			 strcat(Stringbuilder,"Checkpoint Achieved: 1000");
		else if (Score > 500)
			 strcat(Stringbuilder,"Checkpoint Achieved: 500");
	}

	LineBreak();
	LineBreak();
	 strcat(Stringbuilder,"Press Up to Continue");
	LineBreak();
	 strcat(Stringbuilder,"Press Down to Quit");

	strcpy(WriteBoard, Stringbuilder);;
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

	//if (MuteMusic == false)
	//	music.ResumeMusic();
	InitConsoleColors();
}

static void BlockHandling(void)
{
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

//also ye old code
/*static void SettingsMenu()
{
	TextBoxReplace("");
	music.PauseMusic();

	Console.BackgroundColor = ConsoleColor.DarkBlue;
	Console.ForegroundColor = ConsoleColor.White;

	TextBoxWriteLine(
"###########Settings###########\n" +
"#                            #\n" +
"#    Right = Mute/Unmute     #\n" +
"#    Left =  Quit & Quit     #\n" +
"#    Up = Return to Game     #\n" +
"#                            #\n" +
"##############################\n");
	int ButtonCooldown = 0;
	bool NotReturned = true;

	while (NotReturned)
	{
		if (IsKeyDown(2))
		{
			Refresh = false;
			NotReturned = false;
			InitConsoleColors();
			Console.ForegroundColor = ConsoleColor.Red;
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

		System.Threading.DoSleep(60);
	}
	if (MuteMusic == false)
		music.ResumeMusic();
	TextBoxReplace("");

}*/

/*static void StartScreen(void)
{
	TextBoxWriteLine("CONGRATS! starting.");
	DoSleep(1000);

	//if(IsChristmas)
	//	Cutscene();

	bool NotStarted = true;
	while (NotStarted)
	{

		TextBoxReplace(
"     Version RockBox \n##############################\n#............................#\n#........@@@@@@@@@@@@........#\n#........@ Press Up @........#\n#........@@@@@@@@@@@@........#\n#............................#\n##############################\n\n   (c) othello7 2019-2021"
				);
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
}*/

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


		strcpy(WriteBoard, Stringbuilder);

		DisplayAndDelay();

		DoSleep(Tick);
	}
}

void Game(void)
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

	TextBoxWriteLine("Start Screen");
	//StartScreen();

	//if (MuteMusic)
	//	music.PauseMusic();

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

	/*if (MuteMusic == false)
		music.TerminateMusic();
	else
	{
		music.ResumeMusic();
		music.TerminateMusic();
	}

	DiscordDB.die();*/

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
	unsigned short buttons;//, previous = 0;

    init_n64();

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
		if(anim > 31)
			anim = 0;

        printText(_dc, "DodgeBlock  64", 320/16 - 8, 3);
        printText(_dc, "(c) othello7 2019-2022", 320/16 - 11, 13);

        unlockVideo(_dc);

        buttons = getButtons(0);

        //if (DU_BUTTON(buttons ^ previous))
        //{
            // A changed
            if (DU_BUTTON(buttons))
			{
            	Game();
			}
		//}
        //previous = buttons;
        delay(9);
    }

    return 0;
}
