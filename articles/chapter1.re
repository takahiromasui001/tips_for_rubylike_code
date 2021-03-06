= 「Rubyっぽい」について
== 「Rubyっぽい」とは？
まず「Rubyっぽい」とは何でしょうか？これは実務経験半年の私が論ずるにはあまりにも危険な話題で、実際ビクビクしながら書いています。
しかしあえて主張させていただきます。「Rubyっぽいとはこれだ！」という概念は…特にありません。

決して逃げたわけではありません。きちんと根拠があります。
Rubyはそもそも色々な書き方ができる言語です。
「同じ目的であっても様々な選択肢があり、開発者によって自分の好きなやり方を選べることで、楽しくプログラミングを行おう」
といった方針を持っています。そのため特定の書き方を「Rubyっぽい」と公式に推奨するようなことはありません。

//blankline

ただそれでも、現実的には「Rubyっぽい」という言葉は存在しています。
実際「Rubyっぽい」や「Rubyらしい」と行った表現はインターネット上の技術記事に散見されます。
それらは大きな意味での「概念」や「哲学」といったものではなく、個々の状況において多くのRuby技術者が支持する、メソッドの使い方やコーディングスタイルを示しているようです。
それを須藤 功平さんが抽象的にわかりやすく表現した内容を、RubyMagazineの記事(https://magazine.rubyist.net/articles/0043/0043-BeALibraryDeveloper.html)から引用します。

//quote{
「Ruby らしい」とはどういうことでしょうか。「○○らしい」とは「他と似ている」ということです。
「Ruby らしい」書き方だとまわりのコードと似たような記述になります。
つまり、まわりのコードと統一感がでるということです。
//}

この表現が現状最も適切に「Rubyっぽい」を表現していると、私は感じています。

== 本書における「Rubyっぽい」の定義
前節の内容を踏まえ、本書では以下を「Rubyっぽい」コードの定義とします。

 * Rubyエンジニアにとって馴染みのある表現を用いたコード

前述の通りここで言う「Rubyっぽい」というのは、個々の状況におけるベストプラクティスです。
十分に実現するのはとても大変で、特にRuby初級者には現実的ではありません。
そこで本書では、成果が得られやすい(= 効率が良い)内容をピックアップして、効率的にある程度「Rubyっぽい」コードを書くための方法を紹介します。

== 「Rubyっぽい」コードを書くメリット
「Rubyっぽい」が具体的に何を表すか？は説明しました。では「Rubyっぽい」コードにするとどんなメリットがあるのでしょうか？

前書きで少し触れましたが、「Rubyっぽい」コードを書けるようになると最終的にはプログラミング自体が楽しくなります。
そこに行き着くまでにも様々なメリットがあります。それらをRuby初級者目線でまとめてここで紹介します。

=== 読む側が見やすいコードを書けるようになる
良く言われることではありますが、コードを書く際には可読性を意識するのが重要です。
自分が書いたコードは、プロジェクトが続く限り何らかの形でメンテされ続けます。
チーム開発であれば、書いた自分がコードに触れている時間より、他の人が読む時間が長くなります。
可読性が高いコードを書けるに越したことはありません。
「Rubyっぽい」コードは前述の通り、他のRubyエンジニアから見て馴染みのある＝読みやすいコードになります。

=== 周囲の評価が上がりメンタルを守れる(かも)
上の話と関連しますがあなたにも直接的なメリットがあります。
読みやすいコードを書く人は、周囲から良い評価を受けやすくなるはずです。
特にコードのレビューをしてくれる人達(会社の上司や先輩、コミュニティーやスクールのメンター等)からは良い印象を持たれるでしょう。
プルリクエストの指摘等も少しずつ減っていくはずです。

そしてこれは精神的な負荷の軽減に繋がります。
実務に入りたての駆け出しエンジニアは、慣れない環境や技術力の不足によってメンタルを削られるイベントに遭遇しやすいです。
余りにも多くの指摘を受け、お互い悪気はないのに雰囲気が悪くなる、そういった事は頻繁に起こり得ます。
「Rubyっぽい」コードを書ければ、プルリクエスト等のコードレビュー時に上司や先輩から細かい指摘を受けにくくなり、少数のより重要なやりとりに集中できるでしょう。
メンタルのケアは本当に重要です。そんな観点でも「Rubyっぽく」書くことは役に立つはずです。

=== 他のRubyエンジニアが書くコードを読めるようになる
「Rubyっぽい」コードが書ければ、読むこともできるはずです。

Ruby初級者が読むコードは、会社の上司先輩が書いたコードや、OSSとして公開されているものなど、自分より経験のあるRubyエンジニアが書いたものである事が多いのではないでしょうか？
そういったコードは、Rubyでよく使われる表現が多く出てきたり、Rubyの様々な機能を使いこなしたコードである事が多く、
雑に言えば「Rubyっぽい」コードである可能性が高いでしょう。
あなたが「Rubyっぽい」コードを書けるようになれば、そういった他の開発者のコードを見て、パッと理解できることが増えるはずです。

=== プログラミング自体が楽しくなってくる
私の経験では「Rubyっぽい」コードが書けるようになればプログラミング自体が楽しくなってきます。

プログラミング中には、目的とは直接関係無いが必要となるちょっとした処理が割と出現します。
自分で作り込まないといけない場合は少し大変です。ライブラリで解決できることも多いですが、
それはそれで導入方法の確認やメンテナンス状況、他のライブラリとの相性問題など、面倒が増えたりもします。

Rubyはそういった「ちょっとした処理」が標準でたくさん入っています。
それらを上手く利用できれば、本来やるべきことに集中でき、心地よく楽しくプログラミングができます。
またRuby自体がコードを簡潔に書くことを信条としている言語なので、
「ちょっとした処理」を利用することも含めて「Rubyっぽい」に近づければコードはシンプルで見た目が良いものになります。

つまり「Rubyっぽい」コードを書けば、本来自分が実現したいことに集中でき、かつコードもシンプルで見た目の良いものになるわけです。
その時あなたはこう思うでしょう。「こんな面倒な処理をシンプルに見栄えよくかけちゃう自分って凄くない？」こうなればプログラミングが楽しくないはずがありません。@<fn>{sugokunai}

//footnote[sugokunai][まぁ実際にはすごいのはRubyですけれども、それを使いこなしてるあなたもすごいんです。そう思っておきましょう]
