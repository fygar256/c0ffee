/*
	16進数で表せる英単語を返す。
	Usage: hdw [-d=dicfile]
	to compile: hdw.c -o hdw
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

char hdc[]="O*********ABCDEF";
char defaultdic[]="/home/gar/hdw/EIJIRO-SAMPLE-1442.TXT";

int ffgetc(FILE *fp) {
	int c;
	c=fgetc(fp);
	if (c==EOF) exit(1);
	return(c);
}

char *getword(FILE *fp) {
	int idx;
	int c;
static	char word[1024];

	idx=0;
	c=ffgetc(fp);
	if (c==0x81) ffgetc(fp);
		else ungetc(c,fp);

	while(1) {
		c=ffgetc(fp);
		word[idx]=(unsigned char)c;

		if (c==' ') {
			int	c2;
			c2=ffgetc(fp);
			if (c2==' ') c='\t';
			else ungetc(c2,fp);
			}
		if (c=='(') {
			while(1) {
				c=ffgetc(fp);
				if (c=='\n') break;
				if (c==')') continue;
				}
			}
		if (c=='\n'||c=='\t'||
			c==','||c==':'||c=='{') break;
		idx++;
		}
		word[idx]='\0';
		ungetc(c,fp);
		while(ffgetc(fp)!='\n');
		if (word[idx-1]==' ')
			word[idx-1]='\0';
		return(word);
}

int isnullstring(char *s) {
	while(*s!='\0') {
		if (isalpha(*s)) return(0);
		if (*s!=' ') return(1);
		s++;
		}
	return(1);
}
		
int ishdc(char c) {
	int	i;
	for(i=0;i<=0xf;i++)
		if (toupper(c)==hdc[i]) return(1);
	return(0);
}

int ishdw(char *s) {
	while(1) {
		if (*s=='\0') return(1);
		if (ishdc(*s)==0) return(0);
		s++;
		}
}

int	main(int argc,char *argv[])
{
	FILE *fp;
	char *word,*s;
	char *dicfile=defaultdic;

	if (argc==2&&strncmp(*(argv+1),"-d=",3)==0)
			dicfile=&((*(++argv))[3]);

	fp=fopen(dicfile,"r");
	if (fp==NULL) exit(1);
	while((word=getword(fp))!=NULL) {
		if (ishdw(word)&&isnullstring(word)==0) {
			s=word;
			while(*s!='\0') *s++=toupper(*s);
			printf("%s\n",word);
			}
		}
	exit(0);
}
