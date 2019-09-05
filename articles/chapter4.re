= Ruby Sliverを受けてRubyの全体像を掴む
本章ではRubyの言語仕様全体を理解するための第1歩として、Ruby Silverの取得を紹介します。

RubySilver(正式名称はRuby Association Certified Ruby Programmer Silver version 2.1：)は、
Rubyアソシエーションが運営するRuby技術者認定試験のの1つです。
資格の特徴は以下の通りで、Ruby初級者が取得するのに非常に向いています。

//quote{
Rubyの文法知識、Rubyのクラスとオブジェクト、標準ライブラリの知識について、基本的な技術レベルを持つことを認定します。
//}

== Ruby Silverをオススメする理由
本章はこれまで、Rubocop＆Enumerableといった内容を紹介してきましたが、
これらは利用頻度の高く、「Rubyっぽい」コードを目指す上で欠かせませんが、ある意味偏った内容ではありました。
Ruby Sliverの取得を通して、Rubyの言語仕様の基本的な部分を満遍なく学ぶことで、
よりバランスよく「Rubyっぽい」コードが書けるようになるはず、というのがRuby Silverをオススメする理由です。

実際私もRuby Silverを2019年2月に取得しましたが、
「Rubyっぽい」コードに限らず、想像以上に仕事で役に立ったなぁと感じました。

それまで利用したことのない組込ライブラリのメソッドを自然と使いこなせるようになったり、
先輩方の書くコードを割とサクッと読めるようになる部分があったりなど、
ボディーブローのように効いてきたような実感があります。

おそらく実務経験を半年〜1年以上積んだ方は得るものが多くないかとも思いますが、
Ruby初級者であれば、十分元の取れる投資ではないかな？と思っています。

ということで本章では以降RubySilverの特徴や勉強方法、当日の注意点などを記載します。
興味のある方はぜひ参考にしてみてください。

== Ruby Sliverの特徴
最初に試験要項(詳細は以下URL)を参照しながら、RubySilverの特徴を説明していきます。
(https://www.ruby.or.jp/ja/certification/examination/)


=== 試験時間＆問題数
試験時間は90分、問題数は50問です。

//blankline

本番では間違いなく時間が余ると思いますので、この点を心配する必要はありません。
本番の試験問題は過去問や問題集(後述)とほぼ同じ内容が結構出ます。
50問中30〜35問程度(6〜7割)はそんな感じです。ある程度勉強していれば、それらは20分もあれば解けるでしょう。
そうなると残り20問を70分で解く形になるわけです。時間は十分余裕があります。焦らずやりましょう。

=== 合格ライン
合格ラインは75%です。

//blankline

前述の通り6〜7割は過去問等と同じ問題ですが、それらを仮に全て正解できても合格ラインにはちょっと届かないかな？という雰囲気がします。
学習の際は過去問丸暗記ではなく、理由や背景含めて自分なりに掘り下げていくことが求められます。

=== 試験方法
試験方法はコンピュータ試験（CBT：Computer Based Testing）です。

//blankline

試験はパソコン上で回答を選択する形になります。4つの中から1つないし複数の答えを選択する形になります。
これは特に注意することはありません。手書きじゃなくて楽だなぁというくらいです。

=== 対象バージョン
対象バージョンはRuby2.1.xです。

//blankline

この点は少し注意が必要です。本書執筆時点(2019年9月)ではRuby2.6.4が最新ですが、
試験の対象バージョンは2.1.xです。問題集の回答に違和感を感じ、調査してみたら最新バージョンのRubyでは動作が異なった、ということが起こり得ます。

個人的にはこの点で大きく悩まされたことはありませんでしたが、
過去問や問題集の内容と実際のRubyの動作が異なる、という事は起こり得ますのでご注意ください。

=== 出題範囲
出題範囲は以下の通りです。実際の試験では特に組込ライブラリに関する問題が多いため、重点的に学習する必要があります。
学習方法の詳細は後ほど説明します。

==== 文法
コメント, リテラル（数値、真偽値、文字列、文字、配列、ハッシュ等）, 変数/定数とスコープ,
演算子, 条件分岐, ループ, 例外処理, メソッド呼び出し, ブロック, メソッド定義, クラス定義
モジュール定義, 多言語対応

==== 組み込みライブラリ
よく使用されるクラス、モジュール

（Object、数値クラス、String、Array、Hash、Kernel、Enumerable、Comparable等）

==== オブジェクト指向
 ポリモルフィズム, 継承, mix-in

== 学習時間・学習期間の目安
あくまで私の場合ですが、学習時間・学習期間は以下の形でした。

 * 学習期間：約2週間
 * 学習時間：約30時間

個人差の大きい部分だと思いますが、長くても1ヶ月程度時間を確保できれば十分合格に届くはずです。

なお学習開始時点における私の経歴はおおよそ以下の通りです。
ご自身の学習期間を見積もる際の参考にしていただければ幸いです。

 * Rubyに関しては3ヶ月独学＆研修で2週間
 * Rubyの経験は無くはない、という程度
 * 他言語の経験あり
   ** 大学時代 C/Javaを履修(?)
   ** 会社員になってから5年程度、たまーに業務でコードに触れる程度
 * IT系の知識は薄く広く
   ** 基本情報は持っているとかその程度。

== 学習方法
以降私が実際にRuby Silverを取得した際に実施した学習方法を紹介します。
これは私がQiitaに投稿した記事、
「Ruby Silverに合格したので、勉強方法をまとめてみた(2019年2月版)」
(https://qiita.com/jonakp/items/7f7550eeea78973a0a7f)
をリファインしたものになっていますので、その点ご了承ください。

=== とりあえず結論
学習方法の概要を列挙すると以下のような形になります。
以降それぞれを説明していきます。

 * 合格記事をさら〜っと眺める
 * とにかく色々な問題集を解きまくる
 * 各問題集で9割以上正答＆理由も説明できるようにする
 * 仕上げに先人が残してくれた要注意情報に目を通す

=== 1. 合格記事をさら〜っと眺める
まずはRuby Silver自体の大まかな傾向を掴むために
「Ruby Silver 勉強法」あたりでググっていくつか記事を眺めてみることをおすすめします。
複数の記事を見ていると、勉強方法やら出題内容等で共通した項目がうっすらと見えてくると思います。

例えば以下のような内容です。

 * String/Array/Hashクラスのインスタンスメソッドに関する出題が多い
 * 同じ機能で別の名前を持つメソッドの記憶は必須
 * 破壊的メソッドとそうでないメソッドの見分けも重要
 * File/Dir/Timeクラスに関しての出題もそこそこ多い

この段階であまり細かく理解する必要はありません。
適当にGoogle検索結果の上から5,6個記事を直感でピックアップして、流し読みするくらいで良いと思います。

=== 2. とにかく問題集を解く
具体的な対策としては、問題集を周回するのが一番手っ取り早いでしょう。
ソシャゲのマラソンみたいなノリでひたすら走るべし。

問題集も1つだけではなく、色々な問題集を取っ替え引っ替えするのがオススメです。
複数の問題集をこなしているうちに、共通点や傾向が自然と理解できるようになるはずです。
私が実際に使った問題集は以下の3つです。
特におすすめなのはｗスマホでも簡単にできる「REx」です。
やる気が出ない時も寝っ転がりながらダラダラとこなしたりしていました。

==== 公式模擬問題集
pdfと見せかけてどこかのgithubリポジトリに飛びます。以下のURLからアクセスできます。無料です。
個人的には難易度は一番易しいかと思います。

https://www.ruby.or.jp/assets/images/ja/certification/examination/exam_prep_j
p.pdf

==== REx
個人的には一番オススメの問題集です。
以下のURLからアクセスできます。

https://www.ruby.or.jp/ja/certification/examination/rex

WEBサービスの形をとっておりスマホから簡単に取り組めます。
また受ける度に問題の内容や並びが変わるのでなかなか実践的です。
おおよそ8割が共通の問題で残りの2割が入れ替わるような形です。
もちろん以前の問題を再び受け直すことも可能です。解説もまぁまぁ書かれています。
恐らく一番使いました。
ただgithubアカウントとの連携が必要ですので、その点だけご注意ください。

==== [改訂2版］Ruby技術者認定試験合格教本（Silver/Gold対応）Ruby公式資格教科書
https://www.amazon.co.jp/dp/B0756VF9Y3/ref=dp-kindle-redirect?_encoding=
UTF8&btkr=1
これだけ普通の書籍です。大きな本屋じゃないと入手できないかもしれません。
amazon等なら確実にです。最後に紹介していますが、Ruby Silverの対策本といえばまずコレ！と言われるくらい有名な書籍です。
この手の本の常として3600円と結構なお値段がしますが、十分その価値はあると思います。
でもやっぱり高いので、借りるなり、会社にねだるなり、メルカリを使ってみるなり工夫した方が良いかもしれません。

問題集だけでなく、出題範囲に関する一通りの知識も記載されているので、試験範囲の知識に関するリファレンスとしても活用できます。
特に3,4,5章あたりは、頻出の重要な内容が丁寧に説明されているので、一通り読んでおいても良いと思います。
ただ問題集を解いた上で、不明な点に絞って読んだ方がより効率的でしょう。

=== 3. 各問題集で9割以上正答＆理由も説明できるようにする
次に2つ以上の問題集を9割以上正当できる＆理由も説明できるようします。
その際、理解するための手段は色々な方法を試す方が良いです。

 * 問題集の解答を読む
 * Ruby技術者認定試験合格教本の該当箇所を読む
 * ネットで関連情報をググる(主にRubyリファレンスなど)
 * irb/pryで実際に動作を確かめる
などなど…

この辺りを広くやればやるほど、応用の効く知識が身につき、本番で想定外の問題が出ても対応できるようになります。
正答に関係ない選択肢でも、分からなければ積極的に調査する、といった様にちょっとした寄り道をしてみるのが良いでしょう。

逆に問題集の解答を丸暗記しただけだと、本番で想定外の問題に出くわした時に足元をすくわれる可能性が高くなる、と思います。

=== 4. 仕上げに先人が残してくれた要注意問題に目を通す
本番の試験は、6,7割は問題集ほぼそのままの内容ですが、残りは妙にひねった所のある、いやらしい問題が出てきます。
試験の前日などに、先人が残したくれた情報に目を通すとその辺りの対策になるのでオススメです。

私が実際に直前に確認して助かったのは以下2つの記事です。
おそらくそのおかげで多分3問くらいは得しました。受験前にチラッと目を通しておくことをオススメします。

 * Ruby Silver試験前に見直すと幸せになれるメモ
http://tamata78.hatenablog.com/entry/2015/08/07/200454

* Ruby技術者認定試験Silver version 2.1を受けて…
https://qiita.com/motty93/items/413485469e4ec665c329

== その他の注意点
=== 申し込みについて
RubySilver申し込みの際は以下2つを注意してください。

==== 申し込みはプロメトリック社のサイトから
Ruby Silverの申し込みはプロメトリック社のサイトから行いますので注意してください。
(http://it.prometric-jp.com/reserve/index.html)

「Ruby Silver 申し込み」あたりでググると、「Ruby技術者認定試験制度| プロメトリック」のリンクが2番目か3番目に表示されますので
そこからアクセスするのが簡単です。
プロメトリック社のサイトを開いた後は、ページの下側にある「オンライン予約」から申し込みができます。
(Ruby Silver/Gold 共通の入口です。手続きを進めていただくと途中でRubSilverを選択する箇所が出てきます)

//image[Ruby_Silver_Google][Google検索結果]{

//}

//image[Ruby_Prometric][プロメトリック社のサイト]{

//}

==== 会場は早めにチェックする
どの会場で試験を受けるかのチェックは早めに行いましょう。
基本毎日試験を開催しているのですが、土日に試験を開催している所はほとんどありません。
また場所によっては月に数回程度しか開催していない会場もあります。

会場ごとの試験開催日程は、
先ほど紹介した「オンライン予約」のすぐ下にある「試験会場検索・予約状況確認」から参照できます。

//image[Place_Date_Ruby_Silver][試験会場検索・予約状況確認]{

//}

=== 当日の注意点

=== 試験後


- 身分証等は持ち込む
- 思いの外時間には余裕がある
- 合格証は直接相談すると早く出してくれる、かもしれない。
- 盾とかがもらえる
- 会場にも依るが物品の持ち込みはかなり厳しく制限される