# -*- coding: utf-8 -*-
#
#  Developer name : ADMIS_Walker
#  Blog           : https://admiswalker.blogspot.jp/
#  Profile        : https://admiswalker.blogspot.jp/p/profile.html
#
#
#  The MIT License (MIT)
#  
#  Copyright (c) 2017 ADMIS_Walker
#  
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#  
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#  
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.
#
#
#  日本語訳
#  
#  The MIT License
#  Copyright (c) 2017 ADMIS_Walker
#  
#  以下に定める条件に従い，本ソフトウェアおよび関連文書のファイル
#  （以下「ソフトウェア」）の複製を取得するすべての人に対し，ソフトウェアを無制限
#  に扱うことを無償で許可します．これには，ソフトウェアの複製を使用，複写，変更，
#  結合，掲載，頒布，サブライセンス，および/または販売する権利，およびソフトウェア
#  を提供する相手に同じことを許可する権利も無制限に含まれます．
#  
#  上記の著作権表示および本許諾表示を，ソフトウェアのすべての複製または重要な部分
#  に記載するものとします．
#  
#  ソフトウェアは「現状のまま」で，明示であるか暗黙であるかを問わず，何らの保証も
#  なく提供されます．ここでいう保証とは，商品性，特定の目的への適合性，および権利
#  非侵害についての保証も含みますが，それに限定されるものではありません． 作者また
#  は著作権者は，契約行為，不法行為，またはそれ以外であろうと，ソフトウェアに起因
#  または関連し，あるいはソフトウェアの使用またはその他の扱いによって生じる一切の
#  請求，損害，その他の義務について何らの責任も負わないものとします．

# 想定するディレクトリ構成例
#
# exampledir/
#   |
#   + Makefile (this file)
#   |
#   + exe (executable file)
#   |
#   + make_temp/ (temporary directory for make)
#   |
#   + *.cpp
#   |
#   + source/
#   |   |
#   |   + *.cpp
#   |   |
#   |   + SubDir1/
#   |       |
#   |       + *.cpp
#   |
#   + include/
#       |
#       + *.hpp

# .o: Objects file
# .d: Depends file

#============================================================

# 各項目を設定してください

# ソースファイルの場所 ($make steps コマンドで，ヘッダファイルの行数もカウントする場合は，
# ヘッダファイルのディレクトリも追加する必要があります．また，拡張子を記述してはいけません)
# 例: SRCDIR = *. source/*. source/SubDir1/*.
DIR = *.

# 生成ファイル名
TARGET = exe
# 親ディレクトリ名にする場合
# TARGET = $(shell basename `readlink -f .`).exe

# コンパイルオプション
# 例: CFLAGS += -L/home/usr/lib -I/home/usr/include
# 例: CFLAGS += -lssl -lcrypto	# OpenSSL
# 例: CFLAGS += -pthread		# thread
# 例: CFLAGS += -std=gnu++0x	# C++11
CFLAGS  = -lm -lfftw3 -L./fftw_linux_lib -I./fftw_linux_include
CFLAGS += -std=gnu++0x
CFLAGS += -Wall
CFLAGS += -O3

#============================================================

SRCDIR   = $(patsubst %., %.cpp, $(DIR))
SRCS     = $(wildcard $(SRCDIR))

HDIR     = $(patsubst %., %.h, $(DIR))
HEADS    = $(wildcard $(HDIR))

HPPDIR   = $(patsubst %., %.hpp, $(DIR))
HEADppS  = $(wildcard $(HPPDIR))

TEMP_DIR = make_temp
OBJS     = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.o, $(SRCS)))
#OBJS     = $(addprefix $(TEMP_DIR)/, $(SRCS:%.cpp=%.o))#別表記

DEPS  = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.d, $(SRCS)))
#DEPS  = $(addprefix $(TEMP_DIR)/, $(SRCS:%.cpp=%.d))#別表記


# exe ファイルの生成
$(TARGET): $(OBJS)
	@echo ""
	@echo "============================================================"
	@echo ""
	
	@echo "SRCS: "
	@echo "$(SRCS)"
	@echo ""
	
	@echo "OBJS: "
	@echo "$(OBJS)"
	@echo ""
	
	@echo "CFLAGS: "
	@echo "$(CFLAGS)"
	@echo ""
	@echo "============================================================"
	@echo ""
	$(CXX) -o $(TARGET) $(OBJS) $(CFLAGS)
	@echo ""


# 各ファイルの分割コンパイル
$(TEMP_DIR)/%.o: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -c -o $@ $(CFLAGS)


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEMP_DIR)/%.d: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -MM $(CFLAGS)\
	| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;\
	[ -s $@ ] || rm -f $@
#	@echo $*	# for debug
#	@echo $@	# for debug


.PHONY: all
all:
	@(make clean)
	@(make)
#	make clean ; \	#別表記
#	make			#別表記


.PHONY: clean
clean:
	-rm -rf $(TEMP_DIR) $(TARGET)
#	-rm -f $(OBJS) $(DEPS) $(TARGET)


.PHONY: onece
onece:
	$(CXX) -o $(TARGET) $(SRCS) $(CFLAGS)


.PHONY: steps
steps: $(SRCS) $(HEADppS) $(HEADS)
	@echo "$^" | xargs wc -l


#動作未確認[12]
#.PHONY: steps2
#steps2: $(SRCS) $(HEADppS) $(HEADS)
#	@echo "$^" | xargs grep -Ev '^[[:space:]]*((/?\*.*/?)|(//.*))$' | wc -l


-include $(DEPS)


#============================================================

# 動作メモ: 

# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
#
#
#	入力: 
#			$(CXX) $< -MM $(CFLAGS)
#		->												myprint_o: source/myprint.cpp source/../include/myprint.hpp を得る．
#
#	出力: 
#			| sed 's/$(notdir $*).o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/'
#		->	make_temp/source/myprint.o make_temp/source/myprint.d: source/myprint.cpp source/../include/myprint.hpp
#			操作: myprint.o を make_temp/source/myprint.o make_temp/source/myprint.d に置換
#
#	動作の詳細: 
#			$*
#		->	source/myprint
#
#			$(notdir $*).o
#		->	myprint.o
#			操作: ディレクトリでない部分の名前を返却
#
#			$@
#		->	make_temp/source/myprint.d
#
#			$(patsubst %.d,%.o,$@)
#		->	make_temp/source/myprint.o
#			操作: .d を .o に置換
#
#			$(patsubst %.d,%.o,$@) $@
#		->	make_temp/source/myprint.o make_temp/source/myprint.d
#
#			$(subst /,\/,$(patsubst %.d,%.o,$@) $@)
#		->	make_temp\/source\/myprint.o make_temp\/source\/myprint.d
#			操作: / を \/ に置換．(sed に値を渡すために，エスケープする)
#
#			| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/'
#		->	make_temp/source/myprint.o make_temp/source/myprint.d: source/myprint.cpp source/../include/myprint.hpp
#			操作: | (パイプ) で $(CXX) $< -MM $(CFLAGS) の出力を入力として受け取る．
#				  入力 myprint.o: source/myprint.cpp source/../include/myprint.hpp の，
#				  myprint.o を，make_temp/source/myprint.o make_temp/source/myprint.d で置換する．
#
#			動作例: 
#				最初に出てきた aaaa を bbbb に置換する．
#					$ echo "aaaa" | sed -e "s/aaaa/bbbb/"
#					bbbb
#
#				$ echo "myprint.o: source/myprint.cpp source/../include/myprint.hpp" | sed "s/myprint\.o/make_temp\/source\/myprint.o make_temp\/source\/myprint.d/"
#				make_temp/source/myprint.o make_temp/source/myprint.d: source/myprint.cpp source/../include/myprint.hpp
#
#				ところで，下記のように，[.] をエスケープしないと，[.] が正規表現で任意の一文字を表すので，
#				myprint.o -> myprint_o と変更しても同様の出力を得てしまう．(したがって，上記のように "\.o" としてエスケープする必要がある)
#				例:
#					$ echo "myprint_o: source/myprint.cpp source/../include/myprint.hpp" | sed "s/myprint.o/make_temp\/source\/myprint.o make_temp\/source\/myprint.d/"
#					make_temp/source/myprint.o make_temp/source/myprint.d: source/myprint.cpp source/../include/myprint.hpp

# コンパイル (g++ -MM) に失敗し，空の .d ファイルが生成された場合，その .d ファイルを削除する．
#
#	ファイルが空かどうかを判定する．
#		./example.txt のサイズが 0 の時 empty を表示する．(0 以外のとき，なにも表示しない) || は，前のコマンドが失敗した場合，後のコマンドを実行する命令．
#		$ [ -s ./example.txt ]||echo "empty"



# メモ
#
#
# gcc コンパイルオプション
#	 -c: ソース・ファイルのコンパイル、または、アセンブルを行いますが、リンクは行いません。
#		分割コンパイルする際に使用する．
#	 -M: .cpp ファイルがインクルードするファイルを調べる．(システムファイルを含む    )
#	-MM: .cpp ファイルがインクルードするファイルを調べる．(システムファイルを含まない)
#
#
# makefile 中のコマンド
#
#	$(addprefix PREFIX, NAMES...)
#		NAMES の各要素の接頭辞として PREFIX を追加する。
#		※ -I とかを付けるときなどに使える。
#
#	$(patsubst PATTERN, REPLACEMENT, TEXT)
#		TEXT 内から PATTERN にマッチしたものを REPLACEMENT に置き換える。
#		※ subst の PATTERN が使えるバージョン。
#
#	$(subst FROM, TO, TEXT)
#		TEXT内のFROMをTOに置き換える。
#		※patsubstのPATTERNが使えないバージョン。
#
#	$(dir $@)
#		$@ のディレクトリ部分を抽出
#
#	mkdir
#		-p: 指定したディレクトリをサブディレクトリごと作成する。
#		ツリー状のディレクトリも作成可能
#
#	sed
#		$ file_name="linux.txt"
#		$ echo $file_name | sed -e "s/\.txt/.doc/"
#		linux.doc
#
#
# $@: $^
#	XXXXXX
#
#	$@: ターゲット名
#	$^: 依存ファイルのリスト
#	$<: 最初の依存ファイル
#	$%: ターゲットがアーカイブメンバだったときのターゲットメンバ名
#	$?: ターゲットより新しいすべての依存するファイル名
#	$+: Makefileと同じ順番の依存するファイルの名前
#	$*: サフィックスを除いたターゲットの名前
#
#
# shell script
#
#	 &: 並列実行
#	 ;: 逐次実行
#	 \: 改行したコマンドの接続
#	 |: パイプ．前のコマンドの標準出力を，後のコマンドの標準入力とする．
#	||: 前のコマンドが失敗した場合，後のコマンドを実行する．
#	&&: 前のコマンドが成功した場合，後のコマンドを実行する．
#	 >: 標準出力をファイルに出力する．すでにファイルがある場合は上書きする．

# 通常のコンパイル手順
#
# g++ -o exe main.cpp source/myprint.cpp -Wall -O3

# 手動分割コンパイル手順
#
# g++ main.cpp -MM -o main.d ;\
# g++ source/myprint.cpp -MM -o myprint.d ;\
#  \
# g++ main.cpp -c -o main.o ;\
# g++ source/myprint.cpp -c -o myprint.o ;\
#  \
# g++ -o exe main.o myprint.o -Wall -O3

#	参考資料: 
#		[1] Makefile 別ディレクトリに中間ファイル & 自動依存関係設定 - 電脳律速: http://d-rissoku.net/2013/06/makefile-%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E4%B8%AD%E9%96%93%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB-%E8%87%AA%E5%8B%95%E4%BE%9D%E5%AD%98%E9%96%A2%E4%BF%82/
#		[2] Makefileでワイルドカードを使う方法 - nao-bambooの日記: http://tech.chocolatoon.com/entry/2015/09/11/175832
#		[3] Makefileの関数 - Qiita: http://qiita.com/chibi929/items/b8c5f36434d5d3fbfa4a
#		[4] Makeでヘッダファイルの依存関係に対応する - wagavulin's blog: http://blog.wagavulin.jp/entry/20120405/1333629926
#		[5] シンプルで応用の効くmakefileとその解説 - URIN HACK: http://urin.github.io/posts/2013/simple-makefile-for-clang/
#
#		[6] シェルの初歩の初歩 - One Two.jp: http://www.onetwo.jp/proginfo/pub/unix/sh.htm
#		[7] sedコマンドの備忘録 - Qiita: http://qiita.com/takech9203/items/b96eff5773ce9d9cc9b3
#
#		[8] ディレクトリ構成図を書くときに便利な記号 - Qiita: http://qiita.com/paty-fakename/items/c82ed27b4070feeceff6
#
#		[9] https://github.com/T-matsuno07/mtnMakefile/blob/master/makefile
#
#		[10] プログラムのステップ数をカウントする方法 - nishio-dens's diary: http://nishio.hateblo.jp/entry/20101110/1289398449
#		[11] シェル（bash）のfor文の違いを吸収するMakefileの書き方 - 檜山正幸のキマイラ飼育記: http://d.hatena.ne.jp/m-hiyama/20080724/1216874932
#		[12] Javaのステップ数を数える - kumai@github: http://qiita.com/kumai@github/items/3b9e6f73d71323a1bc1d