= Rubocopでコードの見た目をRubyっぽくする
「Rubyっぽい」コードを書くために最初に提案するのはRubocopの利用です。
(https://github.com/rubocop-hq/rubocop)

RubocopはRubyで最もよく利用されている、静的コード解析を実行するgem(Rubyのライブラリ)です。
「この空白はいらないよ」とか「この場合はこっちのメソッドを使った方がいいよ」といったことをアドバイスしてくれます。
コードの品質向上をサポートしてくれるとても頼もしいやつです。

Rubocopは「Rubyエンジニアであれば知らない人はいない」といっても過言ではないgemです。
従ってRubocopに沿ったコードは多くのRubyエンジニアにとって見慣れたものである可能性が高く、
本書の目的である「Rubyっぽい」コードを目指す上で、最初に導入する内容としてもってこいです。
まずはRubocopのアドバイスに従うことで「Rubyっぽい」コードを目指しましょう。

ここからはRubocopの導入に関して以下の流れで段階的に説明していきます。

 1. Rubocopによるコード修正の例
 2. Rubocop導入前の注意点
 3. Rubocopのインストール
 4. Rubocopの実施
 5. Rubocop指摘の修正方法
 6. Rubocopのカスタマイズ
 7. 既存プロジェクトへRubocopを適用する際の注意事項
 8. Rubocopを部分的に無効化する 

== Rubocopによるコード修正の例
まずRubocopを使うと具体的にはどのようにコードを「Ruby」っぽく出来るか見てみましょう。
修正対象のサンプルコードとしては以下を用います。
単純なコードですが、Rubyっぽくない点が多数存在しています。

//list[rubocop_sample_before][target.rb: Rubyっぽくないコード]{
a=1
b = 3
c = [1, 2, 3, 4, 5]
d = []

if a > 10 then
  result = 1
else
  result = 2
end

if result == 1
 p result
end

for num in c do
  d << "#{num*10}"
end

p d
//}

Rubocopの指摘を元にコードを修正すると以下のようになります。(Rubocopの設定はデフォルトです)

//list[rubocop_sample_after][target_after_fix.rb: Rubocopによって修正したコード]{
# frozen_string_literal: true

a = 1
c = [1, 2, 3, 4, 5]
d = []

result = if a > 10
           1
         else
           2
         end

p result if result == 1

c.each do |num|
  d << (num * 10).to_s
end

p d
//}

まだまだ修正の余地はありますが、大分「Rubyっぽいコード」に近づいたと思います。
どのような手順で修正を行うか？は章の後半で紹介します。

== Rubocop導入前に意識しておきたい事
Rubocop導入前に2点ほど意識していただきたいことがあります。

=== Rubocopの本来の用途
本書ではRubocopを、自分が書いたコードを「Ruby」っぽくするという目的で利用しますが、
これは一般的なRubocopの用途からは少しずれています。

Rubocopは基本的にチーム開発におけるコーディングスタイルの統一を目的として利用されます。@<fn>{linter}
//footnote[linter][こういったツールは一般的にlinterと呼ばれ大抵の言語に存在しています。]
コーディングスタイルとはプログラムの書き方に関する約束事です。
簡単な例で言えば、空白の数や改行、変数の名前、適切な文法などが挙げられます。
仕事として行うプログラミングはたいてチームで行います。
チームメンバ間でなるべく書き方を統一し、コードの可読性を高めて生産性を上げよう、
というのがコーディングスタイル統一の目的であり、Rubocopはそのために用いられるのが一般的な用途です。

もちろん個人のコードをより良くするためにRubocopを利用して問題はありませんが、
本来の用途は頭に入れておくと良いです。

=== チームの方針を優先すること
前節の話とかぶる部分もありますが、コーディングスタイルはチーム毎に異なるのが普通です。
Rubocopを使わずに、チーム独自のコーディングスタイルが規定されているような場合もあると思いますが、
その場合はチームの方針を優先しましょう。

Rubocopを利用してより「Rubyっぽい」コードを目指すことにはもちろん価値があると思いますが、
前節において説明したような、「チーム開発においてコードの品質を統一すること」の方が優先されるべきです。

もちろんチームの方針に反しない範囲でRubocopを導入するのも良いと思います。
むしろ周囲がRubocopを使っていないなら、相対的により「Rubyっぽいコード」を書ける可能性が高く、周囲に差がつけられます。
あなたがもしRubocopを用いていない環境にいるならば、こっそり自分だけ使って見るのは良いアイデアかもしれません。

== Rubocopのインストール
ここからRubocopを本格的に導入していきます。まずはRubocopのインストールに関して説明します。やり方は以下の2パターンです。

 1. Gemfileに記載する(bundlerを利用)
 2. gem install コマンドを用いる

基本的にはGemfileに記載するのが良いと思います。
ただチーム開発の環境で自分だけでRubocopを使いたいような場合には、
(勝手にGemfileに追加できないと思いますので)gem installを用いるのも良いでしょう。
もしくは両方やっても問題ありません。

=== Gemfileに記載(bundlerを利用)
Gemfileに以下のように記載した上で、bundle install を実行するだけインストールが完了します。とても簡単です。
//cmd{ 
gem 'rubocop', '~> 0.70.0', require: false
//}

Rubocopはバージョンによってチェックする内容が変わることが多々あります。
後々bundle installによって意図せずにRubocopのバージョンが変わってしまうことを避けるため、
Gemfileには指定バージョンも記載した方が良いでしょう。

Railsを用いたプロジェクトのGemfileに記載する場合は、開発環境以外で使うことはないと思いますので、
//cmd{
group 'development' do
  gem 'rubocop', '~> 0.70.0', require: false
end
//}
のような書き方が良いでしょう。このように設定することで、本番環境でRailsのアプリケーションを動かした際、
使用しないRubocopが組み込まれることが無くなります。

=== gem install コマンド
ターミナル上で以下のコマンドを実行するだけです。
//cmd{
$ gem install 'rubocop'
//}

Rubocopの最新バージョンがインストールされます。(本書執筆時点では0.74.0)
特定のバージョンを使いたいわけでない限り、バージョンを指定する必要はないでしょう。

== Rubocopの実施
インストールはできたのでRubocopが正しく動作するか確認してみましょう。

=== Rubocop実施コマンド
インストールの仕方によって、実行する際のコマンドが若干変わります。

「Gemfileに記載」した場合
//cmd{
$ bundle exec rubocop target.rb
//}

「gem installコマンド」を用いた場合
//cmd{
$ rubocop target.rb
//}

bundle execをつける場合とつけない場合では、利用するRubocopのバージョンが異なる可能性があります。
以下のようにそれぞれ確認してみると違いが分かります。

//cmd{
$ bundle exec rubocop -v
0.70.0
$ rubocop -v
0.74.0
//}

=== Rubocopを実際に使ってみる
では実際にサンプルコードを用いて、Rubocopでコードのチェックを試してみます。
サンプルコードは@<list>{rubocop_sample_before}で示したコードを用います。
以下のような実行結果が表示されれば成功です。
//cmd{
$ rubocop target.rb
Inspecting 1 file
W

Offenses:

target.rb:1:1: C: Style/FrozenStringLiteralComment: Missing magic comment # frozen
_string_literal: true.
a=1
^
target.rb:1:2: C: Layout/SpaceAroundOperators: Surrounding space missing for opera
tor =.
a=1
 ^
target.rb:2:1: W: Lint/UselessAssignment: Useless assignment to variable - b.
b = 3
^
target.rb:6:1: C: Style/ConditionalAssignment: Use the return of the conditional f
or variable assignment and comparison.
if a > 10 then ...
^^^^^^^^^^^^^^
target.rb:6:11: C: Style/MultilineIfThen: Do not use then for multi-line if.
if a > 10 then
          ^^^^
target.rb:12:1: C: Style/IfUnlessModifier: Favor modifier if usage when having a s
ingle-line body. Another good alternative is the usage of control flow &&/||.
if result == 1
^^
target.rb:13:1: C: Layout/IndentationWidth: Use 2 (not 1) spaces for indentation.
 p result
^
target.rb:16:1: C: Style/For: Prefer each over for.
for num in c do ...
^^^^^^^^^^^^^^^
target.rb:17:8: C: Style/UnneededInterpolation: Prefer to_s over string interpolat
ion.
  d << "#{num*10}"
       ^^^^^^^^^^^
target.rb:17:14: C: Layout/SpaceAroundOperators: Surrounding space missing for ope
rator *.
  d << "#{num*10}"
             ^
target.rb:20:4: C: Layout/TrailingBlankLines: Final newline missing.
p d


1 file inspected, 11 offenses detected
//}

== Rubocop指摘の修正方法
前節で確認したRubocopの実行結果を参考にサンプルコードを修正して、「Rubyっぽい」コードにしてみましょう。

=== Rubocop実行結果の見方
まず実行結果の見方について説明していきます。

==== 実行結果の概要
一番最後の行にRubocop実行結果の概要が記載されています。

//cmd{
1 file inspected, 11 offenses detected
//}

これは1つのファイルをRubocopでチェックし、11個のルール違反を見つけたということです。
offense(s)はRubocopにおけるエラーを表しています。
offenseには「犯罪」という意味がありますので、Rubocop(ロボコップ)つながりでoffenseという言葉が使われているのかもしれません。

今回は1つのファイルを指定して実行しているため、実施結果には「1 file inspected」と記載されています。
仮に「$ bundle exec rubocop .」 という形で実行した場合には、カレントディレクトリ以下の全てのrbファイルがRubocopのチェック対象となります。
その際は、XX files inspected という実行結果が表示されるでしょう。

==== offenseの詳細
次にoffenseの詳細を見て行きたいと思います。
実行結果の「Offenses:」と書かれた行から下にある11個のまとまりがそれに該当します。
直感的にわかる箇所も多いですが、指摘を1つ抜き出して全て説明します。
指摘からは以下3点が読み取れればOKです。

 * 指摘箇所はどこか？
 * 指摘の深刻度はどの程度か？
 * チェックルール名(Cop)は何か？
 * チェックルールの概要

//cmd{
target.rb:1:2: C: Layout/SpaceAroundOperators: Surrounding space missing for opera
tor =.
a=1
 ^
//}
「target.rb:1:2」は指摘箇所はどこか？を示しています。左からファイル名・行・列を表します。
この場合はtarget.rbというファイルの、1行目＆2列目にoffenseが存在する、という意味になります。
大抵の場合は、ファイル名と行が分かれば問題ないでしょう。
さらに詳しい情報として、「a=1」のようなコード上の該当箇所を示しています。
ファイル名・行・列の情報と併せて確認することで、どこを直せば良いかわかります。

「C: 」は指摘の深刻さを表しています。
重大さはconvention, warning, error, fatal(この順に深刻度が高くなる)の4つに分類され、
実施結果にはそれぞれの頭文字が表示されます。
この場合は"C: "なのでconventionとなり、重大さは一番低い指摘であることが分かります。
あまりにも指摘が多い場合は「深刻度が高い指摘のみ対応する」という方針もあります。

「Layout/SpaceAroundOperators:」はRubocopのチェックルール名(Cop)は何か？を示しています。
なおRubocopではチェックルールのことを「Cop」と読んでいます。
チェックルールの判別と修正方法の調査に必要なので、指摘内容の中で一番重要な情報です。
詳細は「Rubocop指摘の修正方法」を参考にしてください。

「Surrounding space missing for operator =.」はCopの概要を説明してくれています。
簡単なCopであればここを見るだけで直せることも多いです。

=== Rubocop指摘の修正方法
では実際に指摘内容を修正していきます。

前節でも説明に使った指摘内容を引き続き用います

//cmd{
target.rb:1:2: C: Layout/SpaceAroundOperators: Surrounding space missing for operat
or =.
a=1
 ^
//}

まずは「Cop(チェックルール)の概要」と「コード上の指摘箇所」を確認しましょう。これだけで解決できることも多いです。

 * Cop(チェックルール)の概要
Surrounding space missing for operator =.
 * コード上の指摘箇所
a=1

直訳すると「演算子"="の周囲にスペースが無い」となります。
コードを見るとまさに"a=1"で正に"="の周囲にスペースがありませんね。
それを踏まえて以下のように修正すればOKです。

//cmd{
# 修正後
a = 1
//}

改めてRubocopを実行すると、指摘が1つ減っていることが確認できます。

//cmd{
$ bundle exec rubocop target.rb
Inspecting 1 file

(中略)

1 file inspected, 10 offenses detected
//}

さて今見てきた指摘はとても簡単な内容でした。
では次の指摘はどうでしょうか？

//cmd{
target.rb:6:1: C: Style/ConditionalAssignment: Use the return of the conditional f
or variable assignment and comparison.
if a > 10 then ...
^^^^^^^^^^^^^^
//}

まずは概要を見てみます。
//cmd{
Use the return of the conditional for variable assignment and comparison.
//}

直訳すると
「変数(variable)の代入(assignment)と比較(comparison)には条件文(conditional)の戻り値(return)を使え」
となるでしょうか。

コード上の指摘箇所を踏まえるとifの使い方に問題があるように思いますが、これだけだと具体的にどう直せば良いかはちょっと分かりません。

そんな時は公式のドキュメントでCopを調べてみましょう。
この場合のCopは、「Style/ConditionalAssignment」になります。

これをRubocopの公式ドキュメント
https://rubocop.readthedocs.io/en/stable/
上の検索機能で検索してみます。

すると次のページに辿り着きます。

//image[RubocopDoc_Style_ConditionalAssignment][Style/ConditionalAssignmentの解説]{
//}

色々書いてありますが、ひとまずサンプルコードに注目してください。
「# bad」に記載されているようなコードを、「# good」の形に直すことが要求されています。

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
result = if a > 10
           1
         else
           2
         end
//}

改めてRubocopを実行すると、指摘が更に1つ減っていることが確認できます。

Rubyのifは式なので値が戻ってくるのでこのような書き方が可能になります。
Rubyの特徴を押さえた「Rubyっぽい」コードになりました。

//cmd{
$ bundle exec rubocop target.rb
Inspecting 1 file

(中略)

1 file inspected, 10 offenses detected
//}

残りの10個に関しても同じように指摘内容への修正を実施していけばOKです。
最終的には以下のようなコードになります。
( @<list>{rubocop_sample_after} の再掲です)

//list[rubocop_sample_after_again][target_after_fix.rb: Rubocopによって修正したコード(再掲)]{
# frozen_string_literal: true

a = 1
c = [1, 2, 3, 4, 5]
d = []

result = if a > 10
           1
         else
           2
         end

p result if result == 1

c.each do |num|
  d << (num * 10).to_s
end

p d
//}

==== rubocop --auto-correctを利用した修正
これまでは手動での修正を説明してきましたが、自動修正機能を使うこともできます。
--auto-correct(もしくは-a)オプションを追加して実行するだけです。

ただしこの機能は、自力で修正できる指摘内容に対してのみ使用するべきです。
「修正内容がどんなCopに則った修正か分からない」という状況は望ましくありません。
Rubocopの使い始めの時期は利用を控え、慣れてきた頃に活用すると良いと思います。

//cmd{
$ rubocop -a target.rb
Inspecting 1 file
W

Offenses:

target.rb:1:1: C: [Corrected] Style/FrozenStringLiteralComment: Missing magic comm
ent # frozen_string_literal: true.
a=1
^
target.rb:1:2: C: [Corrected] Layout/SpaceAroundOperators: Surrounding space missi
ng for operator =.
a=1
 ^
target.rb:4:1: W: Lint/UselessAssignment: Useless assignment to variable - b.
b = 3
^
target.rb:6:1: C: [Corrected] Style/ConditionalAssignment: Use the return of the c
onditional for variable assignment and comparison.
if a > 10 then ...
^^^^^^^^^^^^^^
target.rb:6:11: C: [Corrected] Style/MultilineIfThen: Do not use then for multi-li
ne if.
if a > 10 then
          ^^^^
target.rb:9:3: C: [Corrected] Layout/IndentationWidth: Use 2 (not -7) spaces for i
ndentation.
  1 ...
  ^
target.rb:10:1: C: [Corrected] Layout/ElseAlignment: Align else with if.
else
^^^^
target.rb:11:3: C: [Corrected] Layout/IndentationWidth: Use 2 (not -7) spaces for 
indentation.
  2 ...
  ^
target.rb:12:1: C: [Corrected] Style/IfUnlessModifier: Favor modifier if usage whe
n having a single-line body. Another good alternative is the usage of control flow
 &&/||.
if result == 1
^^
target.rb:13:1: C: [Corrected] Layout/IndentationWidth: Use 2 (not 1) spaces for i
ndentation.
 p result
^
target.rb:14:1: C: [Corrected] Style/IfUnlessModifier: Favor modifier if usage whe
n having a single-line body. Another good alternative is the usage of control flow
 &&/||.
if result == 1
^^
target.rb:16:1: C: [Corrected] Style/For: Prefer each over for.
for num in c do ...
^^^^^^^^^^^^^^^
target.rb:17:8: C: [Corrected] Style/UnneededInterpolation: Prefer to_s over strin
g interpolation.
  d << "#{num*10}"
       ^^^^^^^^^^^
target.rb:17:14: C: [Corrected] Layout/SpaceAroundOperators: Surrounding space mis
sing for operator *.
  d << "#{num*10}"
             ^
target.rb:20:4: C: [Corrected] Layout/TrailingBlankLines: Final newline missing.
p d


1 file inspected, 15 offenses detected, 14 offenses corrected
//}

ただし--auto-correctオプションでoffenseを全て修正できるわけではありません。残った修正は手動で行う必要があります。
例えばtarget.rbの場合は1件だけ自動修正できないoffenseが残ります。

//cmd{
$ rubocop target.rb
Inspecting 1 file
W

Offenses:

target.rb:4:1: W: Lint/UselessAssignment: Useless assignment to variable - b.
b = 3
^

1 file inspected, 1 offense detected
//}

== Rubocopのカスタマイズ
Rubocop実行時に適用するCopはカスタマイズできます。
'.rubocop.yml'というファイルを用いてカスタマイズし、プロジェクトのルートディレクトリに作成すると良いでしょう。

Rubocopは実行時に
「.rubocop.ymlの存在確認＆記載内容の適用を行い、それ以外はRubocopのdefault設定を適用する」
という振る舞いをします。

例えば前節の最後に登場した、
Lint/UselessAssignmentをチェックの対象外にする場合には、
以下のような.rubocop.ymlを作成します。

//cmd{
Lint/UselessAssignment:
  Enabled: false
//}

実際にRubocopを運用する際には各チームの事情に合わせて.rubocop.ymlでカスタマイズを行うことがほとんどです。

もし個人開発等で.rubocop.ymlを0から作成する場合には、以下のような企業が公開している規約が参考にするのも良いでしょう。

 * クックパッド
https://github.com/cookpad/styleguide/blob/master/.rubocop.yml

 * airbnb
https://github.com/airbnb/ruby/tree/master/rubocop-airbnb

また本書の目的である「Rubyっぽい」を目指すという観点では、
カスタマイズはなるべく最小限にするのもアリかと思います。

== 既存プロジェクトへRubocopを適用(--auto-config-genの利用): 
既存プロジェクトにRubocopを導入する際には、指摘が多すぎて一度に対応することが困難かもしれません。
この本の対象読者(Ruby実務経験がおおよそ半年以内)の方が自己判断でRubocopを導入する状況で、
「数千件のRubocop指摘が出ました！」ということはあまりないかもしれません。
それでもRubocopの指摘が100件もあったらうんざりしてしまうでしょう。
それでRubocopの導入を諦めたら元も子もありません。

rubocop --auto-config-genによって.rubocop_todo.ymlを作成することで、
既に存在するエラーを別ファイルに保存し、関連するCopを暫定的に無効にすることができます。

説明だけではピンと来ないと思いますので、target.rbを用いて実際にやってみます。

//cmd{
$ bundle exec rubocop target.rb --auto-gen-config
Added inheritance from `.rubocop_todo.yml` in `.rubocop.yml`.
Phase 1 of 2: run Metrics/LineLength cop
Inspecting 1 file
.

1 file inspected, no offenses detected
Created .rubocop_todo.yml.
Phase 2 of 2: run all cops
Inspecting 1 file
W

1 file inspected, 11 offenses detected
Created .rubocop_todo.yml.
//}

この結果、.rubocop_todo.ymlと.rubocop.ymlが作成されました。
この後Rubocopを実施した場合は、Copを暫定的に無効しているため指摘が0件になります。

//cmd{
$ bundle exec rubocop target.rb
Inspecting 1 file
.

1 file inspected, no offenses detected
//}

=== .rubocop_todo.ymlと.rubocop.ymlの役割
どのようにしてCopを暫定的に無効化しているのでしょうか？
作成された.rubocop_todo.ymlと.rubocop.ymlの中身から説明します。

まずは.rubocop_todo.ymlから説明します。

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
1行目はCop(チェックルール)の名前です。2行目3行目は 'target.rb'を除外する(Exclude)という内容です。
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
デフォルトの15から変更できます。

//emlist{
bundle exec rubocop --auto-gen-config --exclude-limit=99999
//}

== Rubocopを部分的に無効化する
前節では新規プロジェクトにRubocopを導入する際の便利なオプションを紹介しましたが、
本節では、既にRubocop導入済みのプロジェクトにおいて、部分的にRubocopを無効化する方法を説明します。
例えば.rubocop.ymlではStyle/LineLength(1行あたり何文字まで許容するか)のCopを100文字に設定しているが、
ここはどうしても120文字位書きたい、といった際に便利です。

やり方はとても簡単です。以下のように無効化したい箇所をコメントで囲うだけです。

//emlist{
  # rubocop:disable all
  ***除外したいコード***
  # rubocop:disable all
//}

試しに@<list>{rubocop_sample_before}のサンプルコードを利用して、Rubocopを部分的に無効化してみます。

//listnum[rubocop_part_disable][部分的にRubocopを無効化]{
# rubocop:disable all
a=1
b = 3
c = [1, 2, 3, 4, 5]
d = []

if a > 10 then
  result = 1
else
  result = 2
end
# rubocop:emable all

if result == 1
 p result
end

for num in c do
  d << "#{num*10}"
end

p d
//}

//cmd{
$ bundle exec rubocop target_commentout.rb 
Inspecting 1 file
C

Offenses:

target_commentout.rb:14:1: C: Style/IfUnlessModifier: Favor modifier if usage when having a single-line body. Another good alternative is the usage of control flow &&/||.
if result == 1
^^
target_commentout.rb:15:1: C: Layout/IndentationWidth: Use 2 (not 1) spaces for indentation.
 p result
^
target_commentout.rb:18:1: C: Style/For: Prefer each over for.
for num in c do ...
^^^^^^^^^^^^^^^
target_commentout.rb:19:8: C: Style/UnneededInterpolation: Prefer to_s over string interpolation.
  d << "#{num*10}"
       ^^^^^^^^^^^
target_commentout.rb:19:14: C: Layout/SpaceAroundOperators: Surrounding space missing for operator *.
  d << "#{num*10}"
             ^
target_commentout.rb:22:4: C: Layout/TrailingBlankLines: Final newline missing.
p d


1 file inspected, 6 offenses detected
//}

結果を見ると指摘内容が14行目以降のものに限定されてお有り、
「2.4.2 Rubocop を実際に使ってみる」で示した実行結果と比較して半分程度になっているのが見て取れます。

また以下のように特定のCopに絞って無効化することもできます。
(Style/IfUnlessModifierを無効化する場合)
//emlist{
  # rubocop:disable Style/IfUnlessModifier 
  ***除外したいコード***
  # rubocop:disable Style/IfUnlessModifier 
//}

//listnum[rubocop_part_cop_disable][部分的に特定のCopを無効化]{
# rubocop:disable all
a=1
b = 3
c = [1, 2, 3, 4, 5]
d = []

if a > 10 then
  result = 1
else
  result = 2
end
# rubocop:emable all

### 特定のCop無効化ここから
# rubocop:disable Style/IfUnlessModifier 

if result == 1
 p result
end

for num in c do
  d << "#{num*10}"
end

p d
# rubocop:enable Style/IfUnlessModifier 
//}

//cmd{
$ bundle exec rubocop target_commentout.rb 
Inspecting 1 file
C

Offenses:

target_commentout.rb:16:1: C: Layout/IndentationWidth: Use 2 (not 1) spaces for indentation.
 p result
^
target_commentout.rb:19:1: C: Style/For: Prefer each over for.
for num in c do ...
^^^^^^^^^^^^^^^
target_commentout.rb:20:8: C: Style/UnneededInterpolation: Prefer to_s over string interpolation.
  d << "#{num*10}"
       ^^^^^^^^^^^
target_commentout.rb:20:14: C: Layout/SpaceAroundOperators: Surrounding space missing for operator *.
  d << "#{num*10}"
             ^
target_commentout.rb:23:4: C: Layout/TrailingBlankLines: Final newline missing.
p d


1 file inspected, 5 offenses detected
//}

「Style/IfUnlessModifier」に関する指摘だけ無くなったことが分かります。

基本的にあまり利用するべき機能ではありませんが、あまり厳密にRubocopを運用するのも辛いことが多いです。
こういった回避策の存在も知っておくと便利です。