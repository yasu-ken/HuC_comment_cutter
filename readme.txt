

(HuC exclusive) C language comment Cutter.(preprocessor)

Delete huc comment.

  between / * to * /
  / / Or later
  Also cuts assembler comments ( ; and later) between #asm .... #endasm.

Huc のコメントを削除します
Hucに日本語を与えるとエラーになってしまいます。
なので前処理でcソースから日本語を削除します。
Windows SHIFT-JIS環境を想定しています。
#asm....#endasm間のアセンブラのコメント(;以降)もカットします
HuCが処理できない / / 以降のコメントも削除できます。

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
	#include "_define.h"   //出力されるワークファイルのほうをインクルード
	#include "_lib.c"      //workfile included.
	/* main loop */
	main(){
		int i;       // ループ変数
		for(;;){     // 永久ループ
			vsync();   // 垂直回帰線割り込み待ち
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
