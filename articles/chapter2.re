= Rubocopでコードの見た目をRubyっぽくする
「Rubyっぽい」コードを書くために最初に提案するのはRubocopの利用です。

RubocopはRubyで最もよく利用されている、静的コード解析を実行するgem(*1)です。
この空白はいらないよとか、この場合はこっちのメソッドを使った方がいいよ、といったことをアドバイスしてくれます。
コードの可読性向上をサポート上げてくれるとても頼もしいやつです。

RubocopはRuby開発者であれば知らない人はほとんどいない、といっても過言ではないgemです。
従ってRubocopに沿ったコードは多くのRuby開発者にとって見慣れたもの、もしくは見慣れたものであるべきと思われているコードであり、
本書の目的である「Rubyっぽい」コードを目指すにはもってこいなわけです。

まずはRubocopのアドバイスに従うことで、「Rubyっぽい」コードにしていきましょう。

ここからはRubocopの導入に関して段階的に説明していきます。
具体的には以下の流れです。必要な箇所から読んでいっていただければ幸いです。

 * Rubocop導入前の注意点
 * Rubocopのインストール
 * Rubocopの実施
 * Rubocop指摘の修正方法
 * Rubocopのカスタマイズ
 * 既存プロジェクトへRubocopを適用する際の注意事項
 * RubocopをCIツール等と連携する

== Rubocop導入前に意識しておきたい事
Rubocop導入前に以下2つほど意識しておきたい事があります。

=== Rubocopの本来の目的
本書ではRubocopを、自分が書いたコードを「Ruby」っぽくする目的で利用しますが、
これは一般的なRubocopの用途からは少しずれています。

Rubocopは基本的にチーム開発においてコーディングスタイルの統一を目的として利用されます。

コーディングスタイルとはプログラムの書き方に関する約束事です。
簡単な例で言えば、空白の数や改行、変数の名前、適切な文法の使い方などが挙げられます。
仕事として行うプログラミングはチームで行うことがほとんどです。
チームのメンバ間で可能な範囲で書き方を統一し、コードの可読性を高めて生産性を上げよう、
というのがコーディングスタイルの目的になります。

Rubocopはコーディングスタイルを統一するためのツールです。

もちろん個人のコードをより良くするためにRubocopを利用して問題はありませんが、

=== チームの方針を優先すること
前節の話とかぶる部分もありますが、コーディングスタイルはチーム毎にに関して優先する内容があるなら、,,,
(以下要作成)


== Rubocopのインストール
Rubocopの導入は以下の2パターンになると思います。
1. Gemfileに記載する(bundlerを利用)
2. gem install コマンドを用いる

基本的にはGemfileへの記載するやり方を取るのが良いと思います。
ただチーム開発の環境であれば、勝手にGemを追加するわけにいかない事も多いと思いますので、
自分だけでRubocopを使いたいような場合には、gem installを用いるのも良いでしょう。

なお両方やっていただいても問題ありません。

=== Gemfileに記載(bundlerを利用)
Gemfileに記載するに以下のように記載した上で、bundle install を実行するだけです。
//emlist{ 
gem 'rubocop', '~> 0.70.0', require: false
//}

Rubocopはバージョンによってチェックする内容が変わることが多々あります。
bundle installによって意図せずRubocopのバージョンが変わってしまうことを避けるため、
バージョンは指定しておいた方が良いです。

RailsプロジェクトのGemfileに記載する場合は、development以外で使うことはないと思いますので、
//emlist{
group 'development' do
  gem 'rubocop', '~> 0.70.0', require: false
end
//}
のような書き方が良いでしょう。

=== gem install コマンド
ターミナル上で以下のコマンドを実行するだけです。
//emlist{
$ gem install 'rubocop'
//}

Rubocopの最新バージョンがインストールされます。(本書執筆時点では0.74.0)
特定のバージョンを使いたいわけでない限り、バージョンを指定する必要はないでしょう。

== Rubocopの実施
インストールはできたのでRubocopが正しく動作するか確認してみましょう。

=== Rubocop実施コマンド
インストールの仕方によって、実行する際のコマンドが若干変わります。

「Gemfileに記載」した場合
//emlist{
$ bundle exec rubocop target.rb
//}

「gem installコマンド」を用いた場合
//emlist{
$ rubocop target.rb
//}

bundle execをつける場合とつけない場合では、利用するRubocopのバージョンが異なる可能性があります。
以下のようにそれぞれでバージョンを確認してみると違いがよく分かります。

//emlist{
$ bundle exec rubocop -v
0.70.0
$ rubocop -v
0.74.0
//}

=== Rubocopを実際にやってみる 
では実際にサンプルコードを用意して、Rubocopでチェックしてみます。

サンプルコードは以下を用います。
簡単なコードですが「Rubyっぽい」と言えない点が多数存在しています。
//emlist{
# target.rb
a=1
b = 3

if a.nil?
 result = 1
else
 result = 2
end

p result
//}

以下のような実行結果が表示されれば成功です。
//emlist{
$ bundle exec rubocop target.rb
Inspecting 1 file
W

Offenses:

target.rb:1:1: C: Style/FrozenStringLiteralComment: Missing magic comment # frozen_string_literal: true.
a=1
^
target.rb:1:2: C: Layout/SpaceAroundOperators: Surrounding space missing for operator =.
a=1
 ^
target.rb:2:1: W: Lint/UselessAssignment: Useless assignment to variable - b.
b = 3
^
target.rb:4:1: C: Style/ConditionalAssignment: Use the return of the conditional for variable assignment and comparison.
if a != nil ...
^^^^^^^^^^^
target.rb:4:6: C: Style/NonNilCheck: Prefer !expression.nil? over expression != nil.
if a != nil
     ^^
target.rb:10:1: C: Style/IfUnlessModifier: Favor modifier if usage when having a single-line body. Another good alternative is the usage of control flow &&/||.
if result == 1
^^
target.rb:11:1: C: Layout/IndentationWidth: Use 2 (not 1) spaces for indentation.
 p result
^

1 file inspected, 7 offenses detected
//}

== Rubocop指摘の修正方法
前節で確認したRubocopの実行結果を読んで、コードが「Rubyっぽく」なるように修正しましょう。

=== Rubocop実行結果の見方
まず一番最後の行を見ると、Rubocop実行結果の概要が記載されています。

//emlist{
1 file inspected, 7 offenses detected
//}
これは1つのファイルをRubocopでチェックし、7個のエラーを見つけたということです。

offense(s)はRubocopにおけるエラーを表しています。
offenseには「犯罪」という意味もあるので、
Rubocop(ロボコップ)が取り締まった「犯罪」という意味で、offenseという言葉が使われているのかもしれません。

今回は1つファイルを指定して実行しているため、実施結果には「1 file inspected」と記載されています。
仮に$ bundle exec rubocop . という形で実行した場合には、カレントディレクトリ以下の全てのrbファイルがRubocopのチェック対象となります。
その際は、XX files inspected という実行結果が表示されるでしょう。

では実際にoffenseの詳細を見て行きたいと思います。
実行結果の上の方に戻りまして、「Offenses:」と書かれた行から下にある7つのブロックがそれに該当します。
直感的にわかる箇所も多いですが、指摘を1つ抜き出して全て説明します。
この中からは以下3点を読み取れればOKです。

 * 指摘箇所はどこか？
 * チェックルール名(Cop)は何か？
 * チェックルールの概要

//emlist{
target.rb:1:2: C: Layout/SpaceAroundOperators: Surrounding space missing for operator =.
a=1
 ^
//}
"target.rb:1:2"は左からファイル名・行・列を表します。
この場合はtarget.rbというファイルの、1行目＆2列目にoffenseが存在する、という意味になります。
大抵の場合は、ファイル名と行が分かれば問題ないでしょう。

"C: "は指摘の重大さを表しています。
重大さはconvention, warning, error, fatal(この順に深刻度が高くなる)の4つに分類され、
実施結果にはそれぞれの頭文字が表示されます。
この場合は"C: "なのでconventionとなり、重大さは一番低い指摘であることが分かります。
とはいえ指摘の重大さに関わらず全て修正する、という方針を取る事が多いかと思いますので、
あまり気にしなくていい箇所かもしれません。

"Layout/SpaceAroundOperators:"はRubocopのチェックルールを示しています。
なおRubocopではチェックルールのことを「Cop」と読んでいます。
チェックルールの判別に必要なので、指摘内容の中で一番重要な情報です。
詳細は「Rubocop指摘の修正方法」を参考にしてください。

"Surrounding space missing for operator =."はCop(チェックルール)の概要を説明してくれています。
簡単なCop(チェックルール)であればここを見るだけで直せることも多いです。

"a=1"&" ^ "はコード上の該当箇所を示しています。ファイル名・行・列の情報と併せて確認することで、どこを直せば良いかわかります。

=== Rubocop指摘の修正方法
では実際に指摘内容を修正していきます。

前節でも説明に使った指摘内容を引き続き用います

//emlist{
target.rb:1:2: C: Layout/SpaceAroundOperators: Surrounding space missing for operator =.
a=1
 ^
//}

まずは「Cop(チェックルール)の概要」と「コード上の指摘箇所」を確認しましょう。これだけで解決できることも多いです。

 * Cop(チェックルール)の概要」
Surrounding space missing for operator =.
 * コード上の指摘箇所
a=1

直訳すると「演算子"="の周囲にスペースが無い」となります。
コードを見るとまさに"a=1"で正に"="の周囲にスペースがありませんね。
それを踏まえて以下のように修正すればOKです。

//emlist{
# 修正後
a = 1
//}

改めてRubocopを実行すると、指摘が1つ減っていることが確認できます。

//emlist{
$ bundle exec rubocop target.rb
Inspecting 1 file

(中略)

1 file inspected, 6 offenses detected
//}

さて今見てきた指摘はとても簡単な内容でした。
ではこちらの指摘はどうでしょうか？

//emlist{
target.rb:4:1: C: Style/ConditionalAssignment: Use the return of the conditional for variable assignment and comparison.
if a != nil ...
^^^^^^^^^^^
//}

まずは概要を見てみます。
Use the return of the conditional for variable assignment and comparison.

直訳すると
「変数(variable)の代入(assignment)と比較(comparison)は条件文(conditional)の戻り値(return)を使え」
となるでしょうか。

コード上の指摘箇所を踏まえるとifの使い方に問題があるように思いますが、これだけだと具体的にどうすれば良いかはちょっと分かりません。

そんな時は公式のドキュメントでCop(チェックルール)を調べてみましょう。
この場合のCop(チェックルール)は、「Style/ConditionalAssignment」になります。

これをRubocopの公式ドキュメント
https://rubocop.readthedocs.io/en/stable/
上の検索機能で検索してみます。

すると以下のようなページに辿り着けます。

//image[RubocopDoc_Style_ConditionalAssignment][連番つきの図]{
 代替テキスト等
//}

色々書いてありますが、ひとまずサンプルコードに注目してください。
「# bad」に記載されているようなコードを、「# good」の形に直すことが要求されているようです。

ここで改めてtarget.rb:4:1を見てみると似たようなコードがあることに気づくと思います。

//emlist{
if a.nil?
  result = 1
else
  result = 2
end
//}

このコードを、「# good」の形に修正すれば良さそうです。
直して見ると以下のようになります。

//emlist{
if a.nil?
  result = 1
else
  result = 2
end
//}

改めてRubocopを実行すると、指摘が更に1つ減っていることが確認できます。

//emlist{
$ bundle exec rubocop target.rb
Inspecting 1 file

(中略)

1 file inspected, 5 offenses detected
//}

残りの5つに関しても同じように指摘内容への修正を実施していけばOKです。
最終的には以下のようなコードになります。

//emlist{
# frozen_string_literal: true

a = 1

result =
  if !a.nil?
    1
  else
    2
  end

p result if result == 1
~
//}

==== rubocop --auto-correctを利用した修正
これまでは手動での修正を説明してきましたが、自動修正機能を使うこともできます。
--auto-correct(もしくは-a)オプションを追加して実行するだけです。
ただしこの機能は、手動で修正できる指摘内容に対してのみ使用するべきです。

修正内容に対して、どんなCop(チェックルール)に則って修正されたか分からない、という状況は望ましくありません。
Rubocopの使い始めの時期は利用を控えた方が良いでしょう。

//emlist{
$ bundle exec rubocop -a target_mod_auto.rb
Inspecting 1 file
W

Offenses:

target_mod_auto.rb:1:1: C: [Corrected] Style/FrozenStringLiteralComment: Missing magic comment # frozen_string_literal: true.
a=1
^
target_mod_auto.rb:1:2: C: [Corrected] Layout/SpaceAroundOperators: Surrounding space missing for operator =.
a=1
 ^
target_mod_auto.rb:4:1: W: Lint/UselessAssignment: Useless assignment to variable - b.
b = 3
^
target_mod_auto.rb:4:1: C: [Corrected] Style/ConditionalAssignment: Use the return of the conditional for variable assignment and comparison.
if a != nil ...
^^^^^^^^^^^
target_mod_auto.rb:4:6: C: [Corrected] Style/NonNilCheck: Prefer !expression.nil? over expression != nil.
if a != nil
     ^^
target_mod_auto.rb:7:3: C: [Corrected] Layout/IndentationWidth: Use 2 (not -7) spaces for indentation.
  1 ...
  ^
target_mod_auto.rb:8:1: C: [Corrected] Layout/ElseAlignment: Align else with if.
else
^^^^
target_mod_auto.rb:9:3: C: [Corrected] Layout/IndentationWidth: Use 2 (not -7) spaces for indentation.
  2 ...
  ^
target_mod_auto.rb:10:1: C: [Corrected] Style/IfUnlessModifier: Favor modifier if usage when having a single-line body. Another good alternative is the usage of control flow &&/||.
if result == 1
^^
target_mod_auto.rb:11:1: C: [Corrected] Layout/IndentationWidth: Use 2 (not 1) spaces for indentation.
 p result
^
target_mod_auto.rb:12:1: C: [Corrected] Style/IfUnlessModifier: Favor modifier if usage when having a single-line body. Another good alternative is the usage of control flow &&/||.
if result == 1
^^

1 file inspected, 11 offenses detected, 10 offenses corrected
//}

ただし全て修正できるわけではありません。残った修正は手動で行う必要があります。
例えばtarget.rbの場合は1件だけ自動修正できない指摘内容が残ります。

//emlist{
$ bundle exec rubocop target_mod_auto.rb
Inspecting 1 file
W

Offenses:

target_mod_auto.rb:4:1: W: Lint/UselessAssignment: Useless assignment to variable - b.
b = 3
^

1 file inspected, 1 offense detected
//}

== Rubocopのカスタマイズ
Rubocop実行時に適用するCop(チェックルール)はカスタマイズすることができます。
カスタマイズは'.rubocop.yml'というファイルを用いて行います。
プロジェクトのルートディレクトリに作成すると良いしょう。

Rubocopは実行時に.rubocop.ymlの存在を確認し、
.rubocop.ymlに記載された内容があればそちらを適用し、それ以外はRubocopのdefault設定を適用する、
という振る舞いをします。
(正確にはもう少し複雑ですが、分かりやすさ優先の説明をしています。詳細は公式ドキュメントをご参照ください)

例えば前節の最後に登場した、
Lint/UselessAssignment(rubocop --auto-correctで修正できなかったCop)をチェックの対象外にする場合には、
以下のような.rubocop.ymlを作成します。

//emlist{
Lint/UselessAssignment:
  Enabled: false
//}

実際にRubocopを運用する際には各チームの事情に合わせて.rubocop.ymlを作成することがほとんどです。
ただ本書の目的である「Rubyっぽい」を目指すという観点では、
カスタマイズはなるべく最小限にすることをオススメします。

(余裕があればカスタマイズ関連を記載する)

== 既存プロジェクトへRubocopを適用(--auto-config-genの利用): 
既存プロジェクトにRubocopを導入する際には、指摘が多すぎて一度に対応することが困難、ということが起こるかもしれません。
この本の対象読者(Ruby実務経験がおおよそ半年以内)の方が自己判断でRubocopを導入する状況で、
数千件のRubocop指摘が出ました！ということはあまりないかもしれません。
それでもRubocopの指摘が100件もあったらうんざりしてしまうでしょう。
それでRubocopの導入を諦めてしまったら元も子もありません。

rubocop --auto-config-genによって.rubocop_todo.ymlを作成することで、
既に存在するエラーを別ファイルに保存し、関連するCopを暫定的に無効にすることができます。

説明だけではピンと来ないと思いますので、target.rbを用いて実際にやってみます。

//emlist{
$ bundle exec rubocop --auto-gen-config
Added inheritance from `.rubocop_todo.yml` in `.rubocop.yml`.
Phase 1 of 2: run Metrics/LineLength cop
Inspecting 1 file
.

1 file inspected, no offenses detected
Created .rubocop_todo.yml.
Phase 2 of 2: run all cops
Inspecting 1 file
W

1 file inspected, 7 offenses detected


1. rubocop auto-config-gen
//}

この結果、.rubocop_todo.ymlと.rubocop.ymlが作成されました。
この後Rubocopを実施した場合は、Copを暫定的に無効しているため指摘が0件になります。

//emlist{
$ bundle exec rubocop
Inspecting 1 file
.

1 file inspected, no offenses detected
//}

=== .rubocop_todo.ymlと.rubocop.ymlの役割
どのようにしてCopを暫定的に無効化しているのでしょうか？
作成された.rubocop_todo.ymlと.rubocop.ymlの中身から説明します。

まずは.rubocop_todo.ymlから。

//emlist{
# This configuration was generated by
# `rubocop --auto-gen-config`
# on 2019-08-14 20:45:27 +0900 using RuboCop version 0.74.0.
# The point is for the user to remove these configuration records
# one by one as the offenses are removed from the code base.
# Note that changes in the inspected code, or installation of new
# versions of RuboCop, may require this file to be generated again.

# Offense count: 1
# Cop supports --auto-correct.
# Configuration parameters: Width, IgnoredPatterns.
Layout/IndentationWidth:
  Exclude:
    - 'target.rb'

(以下略)
//}
長いので最初の1項目だけ抜き出しました。まず"#"で始まっている行はコメントなので無視してください。
実際に理解しておくべきなのは以下の3行だけです。

//emlist{
Layout/IndentationWidth:
  Exclude:
    - 'target.rb'
//}
1行目は見覚えがあると思います。Cop(チェックルール)の名前です。
2行目3行目は読んだ通りの内容です。 'target.rb'を除外する(Exclude)という内容です。
まとめると、target.rbを「Layout/IndentationWidth:」の確認対象から除外する、という意味になります。
その結果target.rbに既に存在する「Layout/IndentationWidth:」の確認は今後行われなくなります。
この設定が7つのoffenseそれぞれに対して行われているのが.rubocop_todo.ymlです。

.rubocop.ymlの中身は以下の通りです。.rubocop_todo.ymlの設定を継承する宣言をしています。

//emlist{
inherit_from: .rubocop_todo.yml
//}

整理すると、
.rubocop_todo.ymlでCop毎に対象外とするファイルを指定
.rubocop.ymlで.rubocop_todo.ymlを継承する設定を記載する
ことによって、
「既に存在するエラーを別ファイルに保存し、関連するCopを暫定的に無効」を実現しています。

=== 注意点
2点注意してほしいことがあります。

1点目はファイル単位でCopが除外されているということです。
つまり.ruboco_todo.ymlでExcludeとして記載されたファイルに関しては、
今後新しい修正に対してもCopは適用されなくなります。
例えば上の例であれば、Layout/IndentationWidth:に該当するコードがtarget.rbに新しく追加されたとしても、Rubocopは検知してくれません。

2点目は1つのCopに対して、Exclude対象が15ファイル以上になった時には、Copそのものが無効化されてしまうということです。
その場合Excludeに記載されたファイルかに関わらず、そのCopに対するチェックは行われなくなります。
これを避ける方法としては"--exclude-limit"オプションの利用があります。
例えば以下のようにrubocop --auto-gen-configコマンドを実行することで、Copそのものが無効化される閾値を、
デフォルトの15から変更することができます。

//emlist{
bundle exec rubocop --auto-gen-config --exclude-limit=99999
//}
