#ifndef _STDIO_H
#define _STDIO_H 1

#include "../kernel.h"

#define BUFSIZ 1024
#define EOF (-1)
#define FILENAME_MAX
#define FOPEN_MAX
#define L_tmpnam
#define NULL
#define TMP_MAX
#define _IOFBF
#define _IOLBF
#define _IONBF
#define SEEK_CUR
#define SEEK_END
#define SEEK_SET

typedef struct FILE{

};

typedef struct fpos_t{

};

typedef struct size_t{

};

//File Opporations
int remove ( const char * filename );
int rename ( const char * oldname, const char * newname);
FILE * tmpfile ( void );
char * tmpnam ( char * str );

//File Access
int fclose ( FILE * stream );
int fflush ( FILE * stream );
FILE * fopen ( const char * filename, const char * mode );
FILE * freopen ( const char * filename, const char * mode, FILE * stream);
void setbuf ( FILE * stream, char * buffer);
int setvbuf ( FILE * stream, char * buffer, int mode, size_t size);

//Formated input/output
int fgetc ( FILE * stream );
int fscanf ( FILE * stream, const char * format, ...);
int printf ( const char * format, ...);

#endif