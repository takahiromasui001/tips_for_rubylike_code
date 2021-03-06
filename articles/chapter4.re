= Ruby Sliverを受けてRubyの全体像を掴む
前章までは特定のツールやクラスの使い方に関して説明してきましたが、
本章では少し視点を変えて、Rubyの言語仕様全体を理解するための手段としてRuby Silverを紹介します。

RubySilver(正式名称はRuby Association Certified Ruby Programmer Silver version 2.1：)は、
Rubyアソシエーションが運営するRuby技術者認定試験の1つです。
資格の特徴は以下の通りで、Ruby初級者が取得するのに非常に向いています。

//quote{
Rubyの文法知識、Rubyのクラスとオブジェクト、標準ライブラリの知識について、基本的な技術レベルを持つことを認定します。
//}

== Ruby Silverをオススメする理由
本章はこれまで、Rubocop＆Enumerableといった利用頻度の高い実践的な内容を紹介してきましたが、
ある意味偏った内容ではありました。
Ruby Sliverの取得を通して、Rubyの言語仕様の基本的な部分を満遍なく学ぶことで、
よりバランスよく「Rubyっぽい」コードが書けるようになるはず、というのがRuby Silverをオススメする理由です。
「基本的」と言ってももちろん入門書よりは少し上の内容で、組込ライブラリの使い方等が主な出題内容になります。
また合格点の明確なテスト形式なので、合格さえすれば一定以上の成果が保証される、というのもミソです。

実際私もRuby Silverを2019年2月に取得しましたが、
「Rubyっぽい」コードに限らず、想像以上に仕事で役に立ったなぁと感じました。

それまで利用したことのない組込ライブラリのメソッドを自然と使いこなせるようになったり、
先輩方の書くコードを割とサクッと読めるようになったりと、
ボディーブローのように効いてきた実感があります。

もしかすると実務経験を半年〜1年以上積んだ方は、既に知っていることが多いためあまりメリットは享受できないかもしれませんが、
Ruby初級者であれば、十分元の取れる投資ではないかな？と思っています。

ということで本章ではRubySilverの特徴や勉強方法、当日の注意点などを説明します。
興味のある方はぜひ参考にしてみてください。

== Ruby Sliverの特徴
最初に試験要項(詳細は以下URL)を参照しながら、RubySilverの特徴を説明していきます。
(https://www.ruby.or.jp/ja/certification/examination/)


=== 試験時間＆問題数
試験時間は90分、問題数は50問です。

//blankline

本番では間違いなく時間が余ると思いますので、この点を心配する必要はありません。
本番の試験問題は過去問や問題集(後述)とほぼ同じ内容が結構出ます。
50問中30〜35問程度(6〜7割)はそんな感じです。そのレベルの問題なら(ちゃんと勉強していれば)20分程度で解けるでしょう。
そうなると残り20問を70分で解く形になるわけです。時間は十分余裕があります。焦らずやりましょう。

=== 合格ライン
合格ラインは75%です。

//blankline

前述の通り6〜7割は問題集とほぼ同じ内容ですが、それだけだと合格にはちょっと届かないかな？というラインです。
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

個人的にはこの点で大きく躓くことはありませんでしたが、
過去問や問題集の内容と実際のRubyの動作が異なる、という事は起こり得ますのでご注意ください。

=== 出題範囲
出題範囲は以下の通りです(Ruby Associationのサイトより)。実際の試験では特に組込ライブラリに関する問題が多いため、重点的に学習する必要があります。
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
pdfと見せかけてどこかのgithubリポジトリに飛びます。以下のURLからアクセスできます。

https://www.ruby.or.jp/assets/images/ja/certification/examination/exam_prep_j
p.pdf

問題数はテスト1回分です。個人的には難易度は一番やさしいと感じました。最初に取り組んでみると良いと思います。

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
UTF8&btkr=1(amazonのリンクです)

これだけ普通の書籍です。大きな本屋じゃないと入手できないかもしれません。
amazon等を使えば確実に入手できます。最後に紹介していますが、Ruby Silverの対策本といえばまずコレ！と言われるくらい有名な書籍です。
この手の本の常として3600円と結構なお値段がしますが、十分その価値はあると思います。
でもやっぱり高いので、借りるなり、会社にねだるなり、メルカリを使ってみるなり工夫した方が良いかもしれません。

問題集だけでなく、出題範囲に関する一通りの知識も記載されているので、試験範囲の知識に関するリファレンスとしても活用できます。
特に3,4,5章あたりは、頻出の重要な内容が丁寧に説明されているので、一通り読んでおいても良いと思います。
ただいったん問題集を解いた上で、不明な点に絞って読んだ方がより効率的でしょう。

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
Ruby Silverの申し込みはプロメトリック社のサイトから行います。
(http://it.prometric-jp.com/reserve/index.html)

「Ruby Silver 申し込み」あたりでググると、「Ruby技術者認定試験制度| プロメトリック」のリンクが2番目か3番目に表示されますので
そこからアクセスするのが簡単です。
プロメトリック社のサイトを開いた後は、ページの下側にある「オンライン予約」から申し込みができます。
(Ruby Silver/Gold 共通の入口です。手続きを進めていただくと途中でRubSilverを選択する箇所が出てきます)

//image[Ruby_Silver_Google_Prometric][Google検索結果とプロメトリック社のサイト]{

//}

==== 日程＆会場は早めにチェックする
いつどの会場で試験を受けるかのチェックは早めに行いましょう。
都市部の会場では平日ほぼ毎日試験が開催されていますが、土日の開催はかなり少なく、
会場によっては平日を含めても月に数回程度しか開催しない場合もあります。
受験日の候補がかなり限定されることも十分に考えられますので、
日程＆会場のチェックは早めに行い、ついでに申し込みもしてしまうことをオススメします。

なお会場ごとの試験開催日程は、
先ほど紹介した「オンライン予約」のすぐ下にある「試験会場検索・予約状況確認」から参照できます。

//image[Place_Date_Ruby_Silver][試験会場検索・予約状況確認]{

//}

=== 当日の注意点
当日注意して欲しいのは「本人確認書類が2つ必要なこと」です。

試験受付の際に2種類の本人確認書類を提出する必要があります。
「運転免許証」とか「パスポート」とかあればいいんじゃないの？と思っても、
もう1種類、本人確認書類が必要です。

これを忘れると本当に試験が受けられません。実際私の知り合いで本人確認書類の準備忘れで試験を受けられなかった人がいます。
その場合返金もしてくれません…
注意してください。

具体的にどんな種類の本人確認書類が必要か？はプロメトリック社のサイトをご確認ください。
(参考に該当ページの画像を貼っておきます)
//image[Identification_Document][本人確認書類]{

//}

