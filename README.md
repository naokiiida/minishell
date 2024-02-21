# Minishell
8th project for 42cursus

## 機能

- コマンド入力を待機時、プロンプト表示(入力開始位置を示す文字)
- history保持(実行したコマンドの履歴)
- PATH変数および相対パス/絶対パスを用いた、正しいファイルの実行
- グローバル変数1個、signal handlerのための数値
- メタ文字(特殊記号による)展開
  - `'` (single quotation) 展開しない
  - `"` (double quotation) $ (dollar sign)が含まれる場合のみ展開する

リダイレクト
- 「<」入力のリダイレクト
- 「>」出力のリダイレクト
- 「<<」入力の読込。指定した任意の区切り文字列だけを含む行が現れるまで。履歴の更新はしない
- 「>>」追記モードの出力のリダイレクト

パイプ「|」
- パイプラインの各コマンドの出力を、パイプを通して次コマンドの入力に接続

環境変数（「$」に続く文字列）展開
- 「$?」
  直近にフォアグラウンドで実行されたパイプラインのコマンドの終了ステータス展開

「ctrl-C」、「ctrl-D」、「ctrl-\」動作、bash順守

インタラクティブのとき（コマンド入力待ちの状態）：
- Ctrl - C : 次の行に、プロンプトを表示
- Ctrl - D : シェルを終了
- Ctrl - ¥ : 何も行わない

### 非対応
閉じられていない引用符や、指定されていない特殊文字（\ や ;）

### Built-in Commands
- echo （-n オプションの挙動を含む）
- cd　（相対パス、または絶対パスのみで動作する）
- pwd　（オプションの処理を含まない）
- export　（オプションの処理を含まない）
- unset　（オプションの処理を含まない）
- env　（オプションと引数の処理を含まない）
- exit　（オプションの処理を含まない）

## 使用する外部関数
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

macOS環境にGNU readlineをソースからコンパイル
- [GNU readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
	- [Download version 8.2 stable](https://git.savannah.gnu.org/cgit/readline.git?h=devel)

root権限なしでインストールしたい場合、configure時prefixで指定
```bash
curl -O ftp://ftp.cwru.edu/pub/bash/readline-8.2.tar.gz
tar -xvf readline-8.2.tar.gz
#optional:
# curl -O ftp://ftp.cwru.edu/pub/bash/readline-8.2.tar.gz.sig
# gpg --verify readline-8.2.tar.gz.sig readline-8.2.tar.gz
cd readline-8.2
# インストール場所をサブディレクトリに指定
./configure —prefix=<サブディレクトリの絶対パス>
make
make install
# manページを~/.zshrcなどシェルの設定ファイルに環境変数として指定
export MANPATH="`manpath`:<サブディレクトリの絶対パス>/share/man"
man 3 readline
man 3 history
```

> [!NOTE]
> readlineをサブディレクトリにインストールした場合、
> `-I`includeオプションと`-DREADLINE_LIBRARY`コンパイルフラグが必要
