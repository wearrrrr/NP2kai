/**
 * @file	pccore.h
 * @brief	Interface of the core
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <nevent.h>

enum {
	PCBASECLOCK25		= 2457600,
	PCBASECLOCK20		= 1996800
};

enum {
	CPUMODE_8MHZ		= 0x20,

	PCMODEL_VF			= 0,
	PCMODEL_VM			= 1,
	PCMODEL_VX			= 2,
	PCMODELMASK			= 0x3f,
	PCMODEL_PC9821		= 0x40,
	PCMODEL_EPSON		= 0x80,

	PCHDD_SASI			= 0x01,
	PCHDD_SCSI			= 0x02,
	PCHDD_IDE			= 0x04,

	PCROM_BIOS			= 0x01,
	PCROM_SOUND			= 0x02,
	PCROM_SASI			= 0x04,
	PCROM_SCSI			= 0x08,
	PCROM_BIOS9821		= 0x10,

	PCCBUS_PC9861K		= 0x0001,
	PCCBUS_MPU98		= 0x0002,
	PCCBUS_SMPU98		= 0x0004
};

/**
 * Sound ID
 */
enum tagSoundId
{
	SOUNDID_NONE				= 0,		//!< No boards
	SOUNDID_PC_9801_14			= 0x01,		//!< PC-9801-14
	SOUNDID_PC_9801_26K			= 0x02,		//!< PC-9801-26K
	SOUNDID_PC_9801_86			= 0x04,		//!< PC-9801-86
	SOUNDID_PC_9801_86_26K		= 0x06,		//!< PC-9801-86 + 26K
	SOUNDID_PC_9801_118			= 0x08,		//!< PC-9801-118
	SOUNDID_PC_9801_86_ADPCM	= 0x14,		//!< PC-9801-86 with ADPCM
	SOUNDID_SPEAKBOARD			= 0x20,		//!< Speak board
	SOUNDID_86_SPEAKBOARD		= 0x24,		//!< PC-9801-86 + Speak board
	SOUNDID_SPARKBOARD			= 0x40,		//!< Spark board
#if defined(SUPPORT_SOUND_SB16)
	SOUNDID_SB16				= 0x41,		//!< Sound Blaster 16
	SOUNDID_PC_9801_86_WSS_SB16	= 0x42,		//!< PC-9801-86 + Mate-X PCM(B460) + Sound Blaster 16
	SOUNDID_WSS_SB16			= 0x43,		//!< Mate-X PCM(B460) + Sound Blaster 16
	SOUNDID_PC_9801_86_SB16		= 0x44,		//!< PC-9801-86 + Sound Blaster 16
	SOUNDID_PC_9801_118_SB16	= 0x45,		//!< PC-9801-118 + Sound Blaster 16
	SOUNDID_PC_9801_86_118_SB16 = 0x46,		//!< PC-9801-86 + PC-9801-118(B460) + Sound Blaster 16
#endif
	SOUNDID_MATE_X_PCM			= 0x60,		//!< Mate-X PCM
	SOUNDID_PC_9801_86_WSS		= 0x64,		//!< PC-9801-86 + Mate-X PCM(B460)
	SOUNDID_PC_9801_86_118		= 0x68,		//!< PC-9801-86 + PC-9801-118(B460)
	SOUNDID_WAVESTAR			= 0x70,		//!< Wave Star
	SOUNDID_AMD98				= 0x80,		//!< AMD-98
	SOUNDID_SOUNDORCHESTRA		= 0x32,		//!< SOUND ORCHESTRA
	SOUNDID_SOUNDORCHESTRAV		= 0x82,		//!< SOUND ORCHESTRA-V
	SOUNDID_LITTLEORCHESTRAL	= 0x22,		//!< LITTLE ORCHESTRA L
	SOUNDID_MMORCHESTRA			= 0x26,		//!< MULTIMEDIA ORCHESTRA

#if defined(SUPPORT_PX)
	SOUNDID_PX1					= 0x30,
	SOUNDID_PX2					= 0x50,
#endif

	SOUNDID_INVALID				= 0xff,		/*!< for new statesave checker */
};
typedef enum tagSoundId		SOUNDID;

enum {
	FPU_TYPE_SOFTFLOAT	= 0, /* Berkeley SoftFloat */
	FPU_TYPE_DOSBOX		= 1, /* DOSBox FPU */
	FPU_TYPE_DOSBOX2	= 2  /* DOSBox FPU+INT64 */
};

/**
 * @brief config
 */
struct tagNP2Config
{
	// エミュレート中によく参照される奴
	uint8_t  uPD72020;
	uint8_t	 DISPSYNC;
	uint8_t	 RASTER;
	uint8_t	 realpal;
	uint8_t	 LCD_MODE;
	uint8_t	 skipline;
	uint16_t skiplight;

	uint8_t	KEY_MODE;
	uint8_t	XSHIFT;
	uint8_t	BTN_RAPID;
	uint8_t	BTN_MODE;

	uint8_t	dipsw[3];
	uint8_t	MOUSERAPID;

	uint8_t	calendar;
	uint8_t	usefd144;
	uint8_t	wait[6];

	uint8_t	davolume;
	uint8_t	modelnum;

	uint8_t timerfix;

#if defined(SUPPORT_ASYNC_CPU)
	uint8_t	asynccpu; // 非同期CPUモード有効
#endif
	uint8_t	consttsc; // RDTSCをAsyncクロック変更によらず一定間隔にする
#if defined(SUPPORT_IDEIO)
	uint8_t	idebaddr; // IDE BIOS アドレス（デフォルト：D8h(D8000h)）
#endif

	// リセット時とかあんまり参照されない奴
	char model[8];
	uint32_t baseclock;
	uint32_t multiple;

	uint8_t	usebios;

	uint8_t	memsw[8];

	uint8_t	ITF_WORK;
#if defined(SUPPORT_LARGE_MEMORY)
	uint16_t EXTMEM;
#else
	uint8_t	 EXTMEM;
#endif
	uint8_t	grcg;
	uint8_t	color16;
	uint32_t	BG_COLOR;
	uint32_t	FG_COLOR;

	uint32_t	samplingrate;
	uint16_t	delayms;
	uint8_t	SOUND_SW;
	uint8_t	snd_x;

	uint8_t	snd14opt[3];
	uint8_t	snd26opt;
	uint8_t	snd86opt;
	uint8_t	spbopt;
	uint8_t	spb_vrc;												// ver0.30
	uint8_t	spb_vrl;												// ver0.30
	uint8_t	spb_x;													// ver0.30

	uint16_t	snd118io;
	uint8_t	snd118id;
	uint8_t	snd118dma;
	uint8_t	snd118irqf;
	uint8_t	snd118irqp;
	uint8_t	snd118irqm;
	uint8_t	snd118rom;

	uint8_t	sndwssid;
	uint8_t	sndwssdma;
	uint8_t	sndwssirq;

#if defined(SUPPORT_SOUND_SB16)
	uint8_t	sndsb16io;
	uint8_t	sndsb16dma;
	uint8_t	sndsb16irq;
	uint8_t	sndsb16at;
#endif	/* SUPPORT_SOUND_SB16 */

	uint8_t	BEEP_VOL;
	uint8_t	vol14[6];
	uint8_t	vol_master;
	uint8_t	vol_fm;
	uint8_t	vol_ssg;
	uint8_t	vol_adpcm;
	uint8_t	vol_pcm;
	uint8_t	vol_rhythm;
	uint8_t	vol_midi;

	uint8_t	mpuenable;
	uint8_t	mpuopt;
	uint8_t	mpu_at;

#if defined(SUPPORT_SMPU98)
	uint8_t	smpuenable;
	uint8_t	smpuopt;
	uint8_t	smpumuteB;
#endif	/* SUPPORT_SMPU98 */

	uint8_t	pc9861enable;
	uint8_t	pc9861sw[3];
	uint8_t	pc9861jmp[6];

#if defined(SUPPORT_FMGEN)
	uint8_t	usefmgen;
#endif	/* SUPPORT_FMGEN */

	uint8_t	fddequip;
	uint8_t	MOTOR;
	uint8_t	MOTORVOL;
	uint8_t	PROTECTMEM;
	uint8_t	hdrvacc;
	uint8_t	hdrvenable;

	uint8_t	savefddfile;											// ver0.86w rev20
	char fddfile[4][MAX_PATH];									// ver0.86w rev20

#if defined(SUPPORT_IDEIO)
	char	sasihdd[4][MAX_PATH];									// ver0.86w
	uint8_t	idetype[4];												// ver0.86w
	char	idecd[4][MAX_PATH];										// ver0.85w
	uint8_t	idebios;												// ver0.86w rev20
	uint8_t	autoidebios;												// ver0.86w rev36
	uint32_t	iderwait; // IDE読み取りの割り込み遅延時間(clock)。  np21w ver0.86 rev19
	uint32_t	idewwait; // IDE書き込みの割り込み遅延時間(clock)。  np21w ver0.86 rev18
	uint32_t	idemwait; // IDE BIOSがある場合の割り込み遅延最小値  np21w ver0.86 rev26 廃止
	uint8_t	savecdfile;
	uint8_t	useasynccd;
	uint8_t	allowcdtraycmd;
	uint8_t	useasynchd;
#else
	char sasihdd[2][MAX_PATH];									// ver0.74
#endif
#if defined(SUPPORT_SCSI)
	char scsihdd[4][MAX_PATH];									// ver0.74
#endif
	char fontfile[MAX_PATH];
	char biospath[MAX_PATH];
	char hdrvroot[MAX_PATH];

#ifdef SUPPORT_NET
	char np2nettap[MAX_PATH];
	uint8_t	np2netpmm;
#endif
#ifdef SUPPORT_LGY98
	uint8_t	uselgy98;
	uint16_t lgy98io;
	uint8_t	lgy98irq;
	uint8_t lgy98mac[6];
#endif
#ifdef SUPPORT_WAB
    uint8_t wabasw;
#endif
#ifdef SUPPORT_CL_GD5430
	uint8_t usegd5430;
	uint16_t gd5430type;
	uint8_t gd5430fakecur;
	uint8_t gd5430melofs;
	uint8_t ga98nb_bigscrn_ex;
#endif
#if defined(SUPPORT_VGA_MODEX)
	uint8_t	usemodex;
#endif
#if defined(SUPPORT_GPIB)
	uint8_t	usegpib; // GPIB使用
	uint8_t	gpibirq; // GPIB IRQ
	uint8_t	gpibmode; // GPIB Master/Slave
	uint8_t	gpibaddr; // GPIB Address
	uint8_t	gpibexio; // GPIB custom I/O port base
#endif
#if defined(SUPPORT_PCI)
	uint8_t	usepci; // PCI Bus使用
	uint8_t	pci_bios32; // BIOS32使用
	uint8_t	pci_pcmc; // PCMC選択
#endif

#if defined(SUPPORT_STATSAVE)
	uint8_t	statsave;
#endif
	uint8_t	fddrive3;
	uint8_t	fddrive4;

	uint8_t	winntfix;
	uint16_t	sysiomsk;

	uint8_t	memchkmx;
	uint8_t	sbeeplen;
	uint8_t	sbeepadj;

	uint8_t	biosioemu;

	char cpu_vendor[16]; // ベンダー（12byte）
	uint32_t cpu_family; // ファミリ
	uint32_t cpu_model; // モデル
	uint32_t cpu_stepping; // ステッピング
	uint32_t cpu_feature; // 機能フラグ
	uint32_t cpu_feature_ex; // 拡張機能フラグ
	char cpu_brandstring[64]; // ブランド名（48byte）
	char cpu_vendor_o[16]; // ベンダー（12byte）OEMCHAR
	char cpu_brandstring_o[64]; // ブランド名（48byte）OEMCHAR
	uint32_t cpu_brandid; // ブランドID
	uint32_t cpu_feature_ecx; // ECX機能フラグ
	uint32_t cpu_feature_ex_ecx; // ECX拡張機能フラグ
	uint32_t cpu_eflags_mask; // EFLAGSマスク

	uint8_t	fpu_type; // FPU種類（0=Berkeley SoftFloat, 1=DOSBox FPU, 2=DOSBox FPU+INT64）

#if defined(SUPPORT_FAST_MEMORYCHECK)
	uint8_t	memcheckspeed; // メモリチェック速度
#endif

	uint8_t	useram_d; // EPSONでなくてもD0000h-DFFFFhをRAMに（ただしIDE BIOS D8000h-DBFFFhは駄目）
	uint8_t	usepegcplane; // PEGC プレーンモードサポート

	uint8_t	usecdecc; // CD-ROM EDC/ECC エミュレーションサポート
	uint8_t	cddtskip; // CD-ROM オーディオ再生時にデータトラックをスキップ

#if defined(SUPPORT_GAMEPORT)
	uint8_t	gameport; // 118音源のゲームポートを使用する
#endif
	uint8_t	allowMOVCS; // mov cs,xx命令の実行を許可する（8086）
	uint8_t	usetexthook; // Text Hookを有効にする（海外向け）
	uint8_t	rascsi92; // 92互換でRaSCSI形式(*.HDN)を読む

#if defined(SUPPORT_DEBUGSS)
	uint8_t	debugss;
#endif

#if defined(SUPPORT_VIDEOFILTER)
	bool     vf1_enable;
	bool     vf1_bmponly;
	uint8_t  vf1_pcount;
	uint8_t  vf1_pno;
	uint8_t  vf1_profile[3][2];
	uint32_t vf1_param[3][3][8];
#endif

	// Setting Keyrepeat
	uint8_t	keyrepeat_enable;
	uint16_t keyrepeat_delay;		// Keyrepeat delay time(ms)
	uint16_t keyrepeat_interval;	// Keyrepeat interval time(ms)
};
typedef struct tagNP2Config  NP2CFG;		/*!< The define of config */

typedef struct {
	uint32_t baseclock;
	uint32_t multiple;

	uint8_t cpumode;
	uint8_t model;
	uint8_t hddif;
#if defined(SUPPORT_LARGE_MEMORY)
	uint16_t extmem;
#else
	uint8_t extmem;
#endif
	uint8_t dipsw[3];		// リセット時のDIPSW
	uint8_t rom;

	SOUNDID sound;
	uint32_t device;

	uint32_t realclock;

	uint32_t maxmultiple;
} PCCORE;

enum {
	COREEVENT_SHUT		= 0,
	COREEVENT_RESET		= 1,
	COREEVENT_EXIT		= 2
};

typedef struct
{
	uint8_t	screenupdate;
	uint8_t	screendispflag;
	uint8_t	drawframe;
	uint8_t	hardwarereset;
} PCSTAT;


#ifdef __cplusplus
extern "C" {
#endif

extern const char np2version[];

extern NP2CFG	np2cfg;
extern PCCORE	pccore;
extern PCSTAT	pcstat;
extern uint8_t	soundrenewal;
extern uint32_t drawcount;
#if defined(SUPPORT_FMGEN)
extern	UINT8	enable_fmgen;
#endif	/* SUPPORT_FMGEN */

void getbiospath(char *path, const char *fname, int maxlen);
void screendisp(NEVENTITEM item);
void screenvsync(NEVENTITEM item);


void pccore_cfgupdate(void);

#if defined(SUPPORT_IA32_HAXM)
void pccore_mem_malloc(void);
void pccore_mem_free(void);
#endif
void pccore_init(void);
void pccore_term(void);
void pccore_reset(void);
void pccore_exec(bool draw);

void pccore_postevent(uint32_t event);

#ifdef SUPPORT_ASYNC_CPU
extern int asynccpu_lateflag;
extern int asynccpu_fastflag;
extern LARGE_INTEGER asynccpu_lastclock;
extern LARGE_INTEGER asynccpu_clockpersec;
extern LARGE_INTEGER asynccpu_clockcount;
#endif

#if defined(CPUCORE_IA32)
extern int GetCpuTypeIndex();
extern int SetCpuTypeIndex(UINT index);
#endif

#if !defined(_WINDOWS) && !defined(__MINGW32__) && !defined(__CYGWIN__)
extern BOOL QueryPerformanceCounter(LARGE_INTEGER* count);
extern BOOL QueryPerformanceFrequency(LARGE_INTEGER* freq);
#endif

#ifdef __cplusplus
}
#endif
