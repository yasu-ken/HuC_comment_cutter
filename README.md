# HuC_comment_cutter

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
