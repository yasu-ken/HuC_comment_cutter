
/****************************************

   (HuC exclusive) C language comment Cutter.(preprocessor)


Delete huc comment.

  between / * to * /
  / / Or later
  Also cuts assembler comments ( ; and later) between #asm .... # endasm.


Huc �̃R�����g���폜���܂�
Huc�ɓ��{���^����ƃG���[�ɂȂ��Ă��܂��܂��B
�Ȃ̂őO������c�\�[�X������{����폜���܂��B
Windows SHIFT-JIS����z�肵�Ă��܂��B
  #asm....#endasm�Ԃ̃A�Z���u���̃R�����g(;�ȍ~)���J�b�g���܂�
  HuC�������ł��Ȃ� / / �ȍ~�̃R�����g���폜�ł��܂��B

*****************************************/


#include	<windows.h>
#include	<stdio.h>
#include	<string.h>

#define FILESIZE_MAX 0x100000
unsigned char readBuffer[FILESIZE_MAX];

void usage();


#define	TRUE        1
#define ERRLEVEL    1
char name_bfr[256+2];


void main(int argc, char *argv[])
{
	long fileSize;

	FILE *fp1,*fp2;
	int lp;
	int rtn;
	int arg_file;
	int arg_com;


	//***********************************************************
	if ( argc < 2 )
	{

		printf( "Delete the comment text from the C language source.\n" );
		printf( "C����\�[�X����A�R�����g�����폜���܂�\n\n" );
		printf( "USAGE:\n" );
		printf( ">comment_cut infile.c outfile.c\n" );
		printf( "  infile  ... textfile( .txt .s .h .cpp .src )\n" );
		printf( "  outfile ... If not specified, it will be output to STDOUT.\n" );

	    exit(1);   //Abnormal termination

	}

	//***********************************************************
	// text file read.

	fp1 = fopen( argv[1], "rt" );
	if( fp1 == NULL )
	{
		printf("infile( %s ) not found.\n",  argv[1] );
	    exit(1);  //Abnormal termination
	}

	rtn = fread(readBuffer,sizeof(char),FILESIZE_MAX,fp1);

	fclose(fp1);

	if(rtn== -1)
	{
		printf("\7\Read Error. ( %s )\n",argv[arg_file]);
	    exit(1);  //Abnormal termination
	}
	fileSize = rtn;  // file size !!


	// mode
	// 0...Not specified(Normal processing)
	// 1...Old comment On
	// 2...#ASM...#ASMEND mode

	int mode = 0; //0=�w��Ȃ� 1=���R�����g�I�� 2=ASM�I��

	for(lp=0; lp<fileSize; lp++)
	{
		//------------------------------
		//new comment "//"
		if((readBuffer[lp]=='/') &&
		   (readBuffer[lp+1]=='/'))
		{
			//Ignore it because it is #ASMmode
			if( mode == 2 )continue;

			//�󔒂�
			readBuffer[lp]=' ';
			readBuffer[lp+1]=' ';
			lp++;

			for( ; lp<fileSize; lp++ )
			{
				//End of line / bin=0x0d 0x0a / text=0x0a only.
				if( readBuffer[lp]==0x0a )
				{
					break;
				}

				//�󔒂ɕϊ�
				readBuffer[lp] = ' ';
			}
		}

		//------------------------------
		// old type comment "/ * "...."* /"
		if((readBuffer[lp]=='/')&&(readBuffer[lp+1]=='*'))
		{
			//Ignore it because it is #ASMmode
			if( mode == 2 )continue;

			//Inconsistency between comment start and end, error
			if( mode == 1 ){
				printf( " /* Comment start double declaration.\n" );
			    exit(1);   //Abnormal termination
			}

			mode = 1;   //old comment mode on.

			//start to cut comment.
			readBuffer[lp]=' ';
			readBuffer[lp+1]=' ';

			lp++;
			lp++;

			for( ; lp<fileSize; lp++)
			{
                //found the end of the comment. -> break
				if((readBuffer[lp]=='*')&&(readBuffer[lp+1]=='/'))
				{
					readBuffer[lp]=' ';
					readBuffer[lp+1]=' ';
					lp++;
					lp++;

					mode = 0; //@Normal processing �ʏ폈��
					break;
				}

				//Convert to blank   �󔒂ɕϊ�
				readBuffer[lp] = ' ';
			}
		}

		//------------------------------
		// asm mode start.
		if((readBuffer[lp+0]=='#')&&
		   (readBuffer[lp+1]=='a')&&
		   (readBuffer[lp+2]=='s')&&
		   (readBuffer[lp+3]=='m'))
		{
			mode = 2;  //asm���[�h
			//asmflg=1;
			lp+=3;
		}

		if((readBuffer[lp+0]=='#')&&
		   (readBuffer[lp+1]=='A')&&
		   (readBuffer[lp+2]=='S')&&
		   (readBuffer[lp+3]=='M'))
		{
			mode = 2;  //asm���[�h
			//asmflg=1;
			lp+=3;
		}

		//mode==2 ASMmode
		// �A�Z���u�����̒��ł� ���R�����g�A�V�R�����g�ł��邩�͖�������
		// �����̋L��������ꍇ�ł����Ă�;�ŃR�����g�ɂȂ��Ă���K�v������܂�
		// C++ Old and new comments are ignored in the assembler text.
		// Must be commented on " ; " even if those symbols are present.

		if( mode == 2 )  //ASM���������ŏ���
		{

			for( ; lp<fileSize; lp++ )
			{

				//asm���甲���邽�߂̔��f
				if((readBuffer[lp+0]=='#')&&
				   (readBuffer[lp+1]=='e')&&
				   (readBuffer[lp+2]=='n')&&
				   (readBuffer[lp+3]=='d')&&
				   (readBuffer[lp+4]=='a')&&
				   (readBuffer[lp+5]=='s')&&
				   (readBuffer[lp+6]=='m'))
				{
					mode = 0;  //@�ʏ폈��
					//asmflg=0;
					lp+=6;
					break;
				}

				if((readBuffer[lp+0]=='#')&&
				   (readBuffer[lp+1]=='E')&&
				   (readBuffer[lp+2]=='N')&&
				   (readBuffer[lp+3]=='D')&&
				   (readBuffer[lp+4]=='A')&&
				   (readBuffer[lp+5]=='S')&&
				   (readBuffer[lp+6]=='M'))
				{
					mode = 0;  //@Normal processing

					lp+=6;
					break;
				}

				if(readBuffer[lp]==';')
				{
					//����ς�󔒂�22/02/20
					readBuffer[lp]=' ';
					lp++;

					for( ; lp<fileSize; lp++ )
					{
						//End of line
						if( readBuffer[lp]==0x0a )
						{
							break;
						}

						//Convert to blank
						readBuffer[lp] = ' ';
					}
				}
			}
		}
	}

	//***********************************************************
	// file save.
	//***********************************************************

	fp2 = fopen( argv[2] , "wt" );
	if( fp2 == NULL )
	{
		fprintf(stdout,"%s",readBuffer );
		exit(0);  //normal termination
	}

	fwrite( readBuffer , sizeof(char) , fileSize , fp2 );
	fclose(fp2);

	exit(0);  //normal termination ����I��
}

