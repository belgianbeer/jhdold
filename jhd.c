/*
 *  Jhd - japanese hexdecimal dump
 *
 *    Written by Masato Minda
 *
 *    Copyright (C) 1986, 1987 by Masato Minda
 *
 *    Created Sep. 11, 1986
 *
 *    Modified
 *      Sep. 25, 1986  change buffer size for vax
 *      Oct. 21, 1986  change compile switch
 *      Oct. 28, 1986  adjust isascii
 *      Nov. 11, 1986  bug fix input console
 *      Dec. 16, 1986  Usage message with Illegal option
 *      Jan. 31, 1987  change Usage message
 *      Mar. 21, 1987  add octal dump mode (1.4)
 *      Apr. 20, 1987  bug fix for OS9 and dmpmain (1.41)
 *      Apr. 27, 1987  change skip data mode (1.5)
 *      Apr. 30, 1987  change putchar on MSC (1.51)
 *      Mar.  8, 1987  bug fix 1.51 (1.511)
 *      Mar. 19, 1987  bug fix 1.51 (1.6)
 *      Jun.  9, 1987  flush stdout after flush, add OCTAL flug (1.7)
 */

static char sccsid[] = "@(#)jhd.c	1.7 (MinMin) 6/09/87";

	"@(#)$Header: /home/minmin/.cvsr/jhdold/jhd.c,v 1.1 1988/09/08 20:44:20 masat-m Exp $";
/*
 *  definition of System type
#ifndef  KMES                /*  for kanji kana messages  */
#	define  KMES
#endif
#ifdef  UNIX
#	undef   UNIX
#endif
#ifdef  OS9K
#	undef   OS9K
#endif
#ifdef  MSC
#	undef   MSC
#endif
#define  LSI     0        /*  in LSI-C  */
#define  UNIX                /*  SET SYSTEM TYPE  */
#define  OCTAL               /*  OCTAL MODE SELECT  */
#define  EUC     0        /*  if set, kanji code is JAE (Shift-JIS default)  */

#include  <stdio.h>
#ifdef  MSC
#	include  <fcntl.h>
#	include  <sys/types.h>
#	include  <sys/stat.h>
#	include  <io.h>
#endif
#ifdef  OS9K
#	include  <module.h>
#endif
#include  <ctype.h>
/*
 *   for kanji kana mode
 */
#ifdef KMES
#	ifndef  iskanji2
		char _ktype[0x100] = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
			0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
			0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
			0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00
		};
#		define  iskanji2(c)    (_ktype[(unsigned char)(c)] & 0x02)
#	endif
#	ifndef  iskanji
#		define  iskanji(c)     (_ktype[(unsigned char)(c)] & 0x01)
#	endif
#	ifndef  iskana
#		define  iskana(c)      (_ktype[(unsigned char)(c)] & 0x04)
#	endif
#else
#	ifdef  iskana
#		undef  iskana
#	endif
#	ifdef  iskanji
#		undef  iskanji
#	endif
#	ifdef  iskanji2
#		undef  iskanji2
#	endif
#	define  iskana(c)    ((c),0)
#	define  iskanji(c)   ((c),0)
#	define  iskanji2(c)  ((c),0)
#endif
#define  BSIZE      16384       /*  input buffer size */
#define  BSIZE   32752
#define  ASCII   1
#define  KANA    2
#define  KANJI   4
#define  T_KANJI        2       /*  kanji terminal  */
#ifdef  OS9K
#	define  STAT   0
#	define  isatty(d)  (_gs_size(d) == -1)
#	define  EXSTAT   0
#	define  STAT   1
#	define  EXSTAT   1
#endif
char   *Buf;                /*  input buffer  */
char   *Lbuf = NULL;        /*  last 16 byte  */

long    Addr;                   /*  current address  */
int     Skip;               /*  skip next data  (kanji2 printed)  */
int     Fskip;              /*  buffer boundary Skip  */
int     Putast;             /*  '*' display flag  */
int     Bflag;              /*  byte octal  */
int     Cflag;              /*  charactor only flag  */
int     Oflag;              /*  octal mode  */
int     Rflag;              /*  byte swap flag  */
int     Vflag;              /*  visual option  */
int     Tmode;              /*  terminal type  */
int     Vflag = 0;              /*  visual option  */
#ifdef  MSC
#	ifdef putchar
#		undef  putchar
#	endif
#endif
char     Obuf[BUFSIZ];
int      Ocnt = BUFSIZ;
char    *Opt = Obuf;
#if  EUC
putchar (c)
int     c;
register int    c;
	*Opt++ = (char)c;
	--Ocnt;
	if (Ocnt == 0) {
		write (fileno (stdout), Obuf, BUFSIZ);
		Ocnt = BUFSIZ;
		Opt = Obuf;
	}
	return (c >= 0xa1 && c <= 0xfe);
}
obflush ()
register int     c;
	write (fileno (stdout), Obuf, BUFSIZ - Ocnt);
	Ocnt = BUFSIZ;
	Opt = Obuf;
	return (c >= 0xa1 && c <= 0xdf);
#endif    /*   MSC  */
}
int     settmode ()
register int    c;
#ifdef UNIX
#if  UNIX || OS9
	char   *getenv ();
	char   *p;

		return ASCII;
	}
	if (!strcmp (p, "mskanji") || !strcmp (p, "jiskanji")) {
		return KANJI;
	} else if (!strcmp (p, "kana")) {
		return KANA;
#endif
		return ASCII;
		Ttype = T_ASCII;
	Ttype = T_KANJI;
#ifdef OS9K
	char   *getenv ();
	char   *p;
}
	if ((p = getenv ("TTYPE")) == NULL) {
		return ASCII;
		++s;
	if (!strcmp (p, "mskanji") || !strcmp (p, "jiskanji")) {
		return KANJI;
	} else if (!strcmp (p, "kana")) {
		return KANA;
	} else {
		return ASCII;
		putchar (' ');
#endif
#ifdef  MSC
#	ifdef  KMES
		return KANJI;
#	else
		return ASCII;
#	endif
#endif
	}
}
#ifdef  OCTAL


long   n;
int    w;
register int    w;
{
	register int     c;

	if (w > 1) {
		putoct (n >> 3, w - 1);
	}
	c = n & 0x7;
	putchar (c + '0');
}
#endif


long   n;
int    w;
register int    w;
{
	register int     c;

	if (w > 1) {
		puthex (n >> 4, w - 1);
	}
	c = n & 0xf;
	if (c <= 9) {
		putchar (c + '0');
	} else {
		putchar (c + '7');
	}
}
putspc (n)
register int    n;
{
	while (n--) {
		putchar (' ');
	}
}


 *  chksame - check 16 byte same data
 *  chksame - check n byte same data
chksame (new, old, n)
register char   *new;
register char   *old;
register unsigned char   *old;
register int     n;
{
	if (old == NULL) {
		return 0;
	}
	while (n--) {
		if (*new++ != *old++) {
			return 0;
		}
	}
	return 1;
}
#ifdef  OCTAL
#if  EUC

 * odmp - dump octal
 *  dmpkanji - dump in kanji with JAE-Kanji
odmp (size, adr, offset)
unsigned char   *base;
long    adr;
long    offset;
int     size;
	int   i, j, start, skip1, skip2;
}
	start = skip1 = 0;
	if (offset > (long)size & 0xffff) {
		fputs (Prgnam, stderr);
		fputs (": Offset too big!\n", stderr);
		exit (STAT);
	} else {
		start = offset & ~0xf;
		adr += start;
		skip2 = skip1 = offset & 0xf;
		}
	Buf[size] = '\0';
	for (i = start; i < size; i += 16, adr += 16) {
		if (!Vflag && (i != start ?
		      chksame (Buf + i, Buf + (skip2 > 0? skip2: i - 16), 16) :
		      chksame (Buf + i, Lbuf, 16))) {
			if (!Putast) {
				putchar ('*');
#ifdef  MSC
				putchar ('\r');
#endif
				putchar ('\n');
#ifdef  MSC
				obflush ();
#endif
				Putast = 1;
			}
			continue;
			putchar ('.');
		skip2 = skip1;
		Putast = 0;
		putoct (adr, 11);
		putspc ((Bflag ? skip1 * 4 : skip1 / 2 * 7) + 1);
		for (j = skip1; j < 16 && j + i < size; j += 2 - Bflag) {
			putspc (1);
			if (Bflag) {
				putoct ((long)Buf[i + j] & 0xff, 3);
			} else if (Rflag) {
				putoct ((long)((Buf[i + j + 1] << 8) & 0xff00 |
						Buf[i + j] & 0xff), 6);
			} else {
				putoct ((long)((Buf[i + j] << 8) & 0xff00 |
						Buf[i + j + 1] & 0xff), 6);
			}
			putchar ('.');
		skip1 = 0;
		if (!Fskip) {
#ifdef  MSC
			putchar ('\r');
#endif
			putchar ('\n');
			putchar (' ');
		}
	}
}
#endif
}

 * dmp - dump hexdecimal
 * hdmp - dump hexdecimal
dmp (size, adr, offset)
int     size;
long    adr;
long    offset;
register int     adr;
	int   i, j, k, start, skip1, skip2;
}
	start = skip1 = skip2 = 0;
	if (offset > (long)size & 0xffff) {
		fputs (Prgnam, stderr);
		fputs (": offset too big!\n", stderr);
		exit (STAT);
	} else {
		start = offset & ~0xf;
		adr += start;
		skip2 = skip1 = offset & 0xf;
		}
	if (Fskip) {
		if (iskanji2(Buf[0]) && Tmode == KANJI) {
			putchar (Fskip);
			putchar (Buf[0]);
			Skip = 1;
			putchar ('\n');
		} else {
			Skip = 0;
		Fskip = 0;
#ifdef  MSC
		putchar ('\r');
		}
#endif
		return;
	for (i = start; i < size; i += 16, adr += 16) {
		if (!Vflag && (i != start ?
		      chksame (Buf + i, Buf + (skip2 > 0? skip2: i - 16), 16) :
		      chksame (Buf + i, Lbuf, 16))) {
		if (!Vflag && chksame(buf, Lbuf, Dwidth)) {
#endif
#ifdef  MSC
				putchar ('\r');
#endif
				putchar ('*');
#ifdef  MSC
				obflush ();
#endif
				putchar ('\n');
				Putast = 1;
			continue;
		}
		skip2 = skip1;
		Putast = 0;
		puthex (adr, 8);
		putspc (skip1 * 3 + (skip1 < 9 ? 1 : 2));
		for (j = skip1; j < 16 && j + i < size; j++) {
			if (j == 8) {
				putspc (1);
				putchar ('\n');
			putspc (1);
			puthex ((long)Buf[i + j] & 0xff, 2);
		}
		while (j < 16) {
			if (j == 8) {
				putspc (1);
				putchar ('\n');
			putspc (3);
			++j;
#endif
		putspc (skip1 + 2);
		for (j = skip1; j < 16 && j + i < size; j++) {
			if (Skip) {
				if (j == 0) {
					putspc (1);
				}
				Skip = 0;
				continue;
			}
			k = i + j;
			if (iskanji(Buf[k]) && Tmode == KANJI) {
				if (k == Bsize - 1) {
					Fskip = Buf[k];
					continue;
				}
				if (k + 1 < size && iskanji2(Buf[k + 1])) {
					putchar (Buf[k]);
					putchar (Buf[k + 1]);
					Skip = 1;
					continue;
				}
			}
			if (iskana(Buf[k]) && Tmode != ASCII ||
			             isprint (Buf[k]) && isascii (Buf[k])) {
				putchar (Buf[k]);
			} else {
				putchar ('.');
			}
			Skip = Kskip = 0;
		skip1 = 0;
		if (!Fskip) {
#ifdef  MSC
			putchar ('\r');
		}
			putchar ('\n');
		}
		putchar ('\n');
	Offset = Addr;
}
dmpmain (fd, offset)
int    fd;
long   offset;
register unsigned char   *ptr;
	char   *malloc ();
	register char   *p0, *p1;
	int     rsize, i;
	long    adr;
	register unsigned char  *bp;
	adr = 0;
	if (Oflag && !Bflag) {
		offset &= ~1;
		*bp++ = *ptr++;
	Putast = Fskip = Skip = 0;
	while ((rsize = read (fd, Buf, Bsize)) > 0) {
		if (offset < (long)rsize) {
#ifdef  OCTAL
			if (Oflag) {
				odmp (rsize, adr, offset);
			} else {
				dmp (rsize, adr, offset);
			}
#else
			dmp (rsize, adr, offset);
#endif
			offset = 0;
			putoct (Addr, 11);
			offset -= (long)rsize;
			puthex (Addr, 8);
		adr += rsize;
		if (Lbuf == NULL) {
			Lbuf = malloc (16);
		}
		if (Lbuf != NULL) {
			i = 16;
			p0 = Lbuf;
			p1 = rsize > 16? Buf + rsize - 16: Buf;
			while (i--) {
				*p0++ = *p1++;
			}
		}
		putchar ('\n');
	if (rsize != -1) {
		dmp (rsize, adr, offset);
		path = pt + 1;
	if (!Vflag && Putast) {
#ifdef  OCTAL
		if (Oflag) {
			putoct (adr + rsize - 1, 11);
		} else {
			puthex (adr + rsize - 1, 8);
			*pt += ' ';
	fputs (" [ -abcjorvO ] [ <file> ] [ +[x|o]<offset>[k] ]\n", stderr);
		puthex (adr + rsize - 1, 8);
	fputs (" [ -abcjkorvO ] [ <file> ] [ +[x|o]<offset>[k] ]\n", stderr);
		putchar ('\n');
		return;
#ifdef  MSC
	obflush ();
#endif
	}
}
long    chkofst (p)
char   *p;
FILE   *fp;
	long    atol ();
	long    offset;
}

		offset = 0;
		while (++p, isxdigit (*p)) {
			if (isdigit (*p)) {
				offset = (offset << 4) + (*p - '0');
				Offset = (Offset << 4) + (c - '0');
				offset = (offset << 4) + (
				          (islower (*p) ? toupper (*p) : *p)
				                                  - 'A' + 10);
				       ((islower(c)? toupper(c): c) - 'A' + 10);
			c = (unsigned)*p++;
	} else if (*p == '0' || *p == 'o' || *p == 'O') {
		offset = 0;
		while (++p, isdigit (*p)) {
			offset = ((offset << 3) & ~7L) + ((*p - '0') & 7);
			++p;
		}
		offset = atol (p);
		while (isdigit (*p)) {
		while (isdigit(*p)) {
			++p;
		}
	if (offset && (*p == 'K' || *p == 'k')) {
		offset <<= 10;
		Offset <<= 10;
	return offset;
	}
}
usage ()
{
	fputs ("Usage: ", stderr);
	fputs (Prgnam, stderr);
#ifdef  OCTAL
	fputs (" [ -borv ] [ <file> ] [ +[x|o|0]<offset>[k] ]\n", stderr);
#else
	fputs (" [ -v ] [ <file> ] [ +[x]<offset>[k] ]\n", stderr);
#endif
	exit (STAT);
}


main (argc, argv)
int     argc;
char  **argv;
	char   *malloc ();
	int     fd;
	long    offset;

#ifdef  UNIX
	Prgnam = *argv;
	Prgnam = setname(*argv);
#ifdef  OS9K
	Prgnam = *argv;
	}
	if ((Buf = malloc (BSIZE + 1)) == NULL) {
		fputs (Prgnam, stderr);
		fputs (": not enough core.\n", stderr);
		exit (STAT);
	}
	offset = 0;
	Vflag = 0;
	Tmode = settmode ();
	while (--argc && **++argv == '-') {
	while (--argc && **++argv == '-' && *(*argv + 1) != '\0') {

			Oflag = Bflag = 1;
			Dwidth = 16;
		case 'v':
			Vflag = 1;
			Dwidth = 64;
#ifdef  OCTAL

			Oflag = 1;
			Dwidth = 16;
#endif

			Oflag = Rflag = 1;
			Dwidth = 16;

		default:
			usage ();
		}
	}
	++argc;
	--argv;
		offset = chkofst (argv[1] + 1);
		chkofst (argv[1] + 1);
		--argc;
		++argv;
#ifdef  MSC
	setmode (fileno (stdout), O_BINARY);
		setvbuf (Fp, Ibuf, _IOFBF, BSIZE);
	if (argc == 1) {
		if (isatty (fileno (stdin))) {
			usage ();
		}
#ifdef  MSC
		setmode (fileno (stdin), O_BINARY);
#endif
#ifdef  UNIX
		Bsize = BUFSIZ;
#endif
#ifdef  OS9K
		Bsize = BUFSIZ;
#endif
		dmpmain (fileno (stdin), offset);
		dmpmain ();
		exit (0);
	while (--argc) {
		offset = 0;
#ifdef  MSC
		if ((fd = open (*++argv, O_RDONLY | O_BINARY)) == -1) {
	if ((Fp = fopen(*++argv, "r")) == NULL && (Fp = fopen(*argv, "d")) == NULL)
#ifdef  OS9K
		if ((fd = open (*++argv, 1)) == -1 &&
			(fd = open (*argv, 0x81)) == -1) {
	if ((Fp = fopen(*++argv, "rb")) == NULL)
#ifdef UNIX
		if ((fd = open (*++argv, 0)) == -1) {
	if ((Fp = fopen(*++argv, "r")) == NULL)
			fputs (Prgnam, stderr);
			fputs (": can't open ", stderr);
			fputs (*argv, stderr);
			fputs (".\n", stderr);
			continue;
		}
		if (argc > 1 && argv[1][0] == '+') {
			offset = chkofst (argv[1] + 1);
			--argc;
			++argv;
		}
		dmpmain (fd, offset);
		close (fd);
		/* --- not reached --- */
	fclose (Fp);
	exit (0);
}
