

(HuC exclusive) C language comment Cutter.(preprocessor)

Delete huc comment.

  between / * to * /
  / / Or later
  Also cuts assembler comments ( ; and later) between #asm .... #endasm.

Huc �̃R�����g���폜���܂�
Huc�ɓ��{���^����ƃG���[�ɂȂ��Ă��܂��܂��B
�Ȃ̂őO������c�\�[�X������{����폜���܂��B
Windows SHIFT-JIS����z�肵�Ă��܂��B
#asm....#endasm�Ԃ̃A�Z���u���̃R�����g(;�ȍ~)���J�b�g���܂�
HuC�������ł��Ȃ� / / �ȍ~�̃R�����g���폜�ł��܂��B

:--------------------------------------------

USAGE:

>HuC_comment_cut test.c _test.c
Output to _test.c

only command ... usage
>HuC_comment_cut

Output to STDOUT when only infile name.
>HuC_comment_cut test.c >out.txt

:--------------------------------------------
Example of use

<< source files >>

I have these files.There is a Japanese description in the comment.
  define.h
  lib.c
  main.c

main.c
	#include "_define.h"   //�o�͂���郏�[�N�t�@�C���̂ق����C���N���[�h
	#include "_lib.c"      //workfile included.
	/* main loop */
	main(){
		int i;       // ���[�v�ϐ�
		for(;;){     // �i�v���[�v
			vsync();   // ������A�����荞�ݑ҂�
		}
	}


<< Batch file for build. >>

(build.bat)
SET PATH=.......(HuC installed folder. HuC_comment_cut is also placed here.)
SET PCE_INCLUDE=(HuC installed folder.)

:Save to work file by preprocessor
HuC_comment_cut define.h _define.h
HuC_comment_cut lib.c  _lib.c
HuC_comment_cut main.c _main.c

:compile.
huc.exe -v _main.c > errors.txt

: work file delete.
del _define.h
del _*.c


<< in conclusion  >>
Don't overwrite important files.


:--------------------------------------------
License

The MIT License.
