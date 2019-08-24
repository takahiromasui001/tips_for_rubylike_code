= Enumerableのメソッドで繰り返し処理をRubyっぽくする
「Rubyっぽい」コードを書くための方法として次に提案するのは、繰り返し処理におけるEnumerableのメソッドの利用です。
有名な所はmapやselectが該当します。

繰り返し処理はどんなプログラムでも用いられる頻出の処理であるため、
Enumerableのメソッドは利用頻度が高く、Rubyエンジニアも好んで用います。
使いこなせれば効率的に「Rubyっぽい」コードを書けるようになるはずです。

Enumerableのメソッドを使うなんて当たり前でしょ？
という方はすみません、この章から得られることは無いかもしれません。

ただ、map?select? なにそれ？ or 聞いたことあるけど...という方、
mapやselectは分かるがEnumerableって何よ？という方は、是非続きを読んでみてください。

== eachメソッドについて
Enumerableの話に入る前の前提知識としてeachメソッドについて説明します。

Rubyで用いられる繰り返し処理の制御構造・メソッドは数多くありますが、
その中でまず押さえておくべきなのはeachです。
eachはオブジェクトの要素の数だけブロックの中身を実行するメソッドです。
まず以下に簡単なサンプルコードを示します。
//emlist{
list = (1..5).to_a
list.each { |item| p item + 10 }
//}
//emlist{
# 出力結果
11
12
13
14
15
//}

eachメソッドに関しては意識しておいてほしい事が2点あります。

1点目はブロック引数です。
ブロック引数(上の例では |item| )には、繰り返しごとにオブジェクトの各要素が順に入ります。
ブロック内では、ブロック引数に保持されたオブジェクトの各要素を用いて何かしらの処理を行います。
上のコードであれば、itemに10を加えたものをpメソッドで出力する、といった形です。

Rubyにおける反復処理は、「オブジェクトの各要素に適用したい処理」を用意しておいて、
オブジェクトの各要素を取り出しながら1つずつ処理を適用する形が好まれます。
(この考え方自体はRuby固有の話ではなく、オブジェクト指向ベースの考え方をベースにしたもので、他の言語ににも存在します)
eachはその考えを実現できる最も基本的なメソッドです。

2点目は戻り値です。
eachの戻り値はレシーバ(上の例では list )になります。
ブロック内でどんな処理をしても戻り値は影響を受けません。

言い換えれば、eachのブロック内で行なった処理の結果は、そのままだとeachの外で用いることは出来ません。
処理結果を外で使いたい場合は、以下のようにブロック外で定義したオブジェクトを渡す必要があります。

//emlist{
list = (1..3).to_a

result = []
list.each { |item| result << item + 10 }
p result
//}
//emlist{
# 出力結果
[11, 12, 13]
//}

=== each利用時の課題
eachはRubyの反復処理には欠かせないとても重要なメソッドです。
しかし前節で説明した、

 * Rubyにおける反復処理は、「オブジェクトの各要素に適用したい処理」を利用する形が好まれる
 * eachのブロック内の処理結果を外で使いたい場合は、ブロック外で定義したオブジェクトを渡す必要がある

を考慮すると課題となる点もあります。

その課題とは一言で表すと、
eachメソッドは「オブジェクトの各要素に適用したい処理」と同時に、
「処理の結果をどう扱うか？」もブロック内に一緒に記載する必要がある、
という点です。

言葉だけだと分かりにくいので、図XXXのコードをベースに説明していきます。

このコードにおける「オブジェクトの各要素に適用したい処理」は、item + 10ですが、
実際の処理は、result << item + 10 となっており、
「result << 」＝「結果をどうまとめるかの処理」もブロック内で一緒に記載している形をとっています。

前述の通りRubyにおける反復処理は、オブジェクトの各要素にある処理を適用する形が好まれます。
繰り返し処理の中で「結果をどうまとめるかの処理」も同時に書かれているのはあまり好ましくありません。

またこの処理の実現のために、eachの外でわざわざ空のresultを用意していますが、これも冗長です。

このような書き方はRuby的には少しカッコわるく、大抵のRuby開発者は避けます。
つまり「Rubyっぽい」と言えません。

== Enumerableのメソッド
そこで登場するのがmapやselectに代表されるEnumerableのメソッドです。

EnumerableはRubyの組込ライブラリの1つで、繰り返し処理に関連する便利なメソッドを提供してくれる Mix-in(モジュール) です。
主に配列やハッシュなど集合を表すクラスに標準で組み込まれており、数え上げや検索などのメソッドを提供します。
ちなみに読み方は「エニュメラブル(発音記号: injúːmərəbl, "ニュ"のあたりにアクセント)」です。

Enumerableのメソッドを用いると、
「オブジェクト内の各要素に適用したい処理」と「処理の結果をどうまとめるか？」の切り離しが、
簡潔なコードで実現できます。
「処理の結果をどうまとめるか？」をEnumerableのメソッド側に任せて、
自分は「オブジェクト内の各要素に適用したい処理」だけをメソッドに渡せばOKというイメージです。

=== eachをEnumerableのメソッドに置き換える
実際に図XXXのコードをEnumerableのメソッドを使って書き直してみます。
ここではmapを使ってみましょう。
mapは「オブジェクトの各要素に適用した処理」の結果を「配列にして」返してくれるメソッドです。

//emlist{
list = (1..3).to_a

p list.map { |item| item + 10 }
//}
//emlist{
# 出力結果
[11, 12, 13]
//}

まずブロック内にはitem + 10の処理、つまり「オブジェクトの各要素に適用したい処理」しか記載されていません。
処理結果はブロックの戻り値としてmapに渡されます。
結果をどう扱うか？はmapの中に隠蔽されている形です。mapの場合は結果を配列にまとめています。
またresultも無くなりました。これはmap自体が戻り値として配列を返してくれるため、処理の結果を格納する変数が必要なくなったためです。

並べて比較してみます。

//emlist{
list = (1..3).to_a

# eachを使った場合
result = []
list.each { |item| result << item + 10 }
p result

# mapを使った場合
p list.map { |item| item + 10 }
//}

3行だったコードが1行で表現でき、非常にスッキリしたコードになりました。
加えてコードの構造が、
「オブジェクトの各要素に適用したい処理」をmapに渡しているだけ
となっているのがよく分かると思います。

=== Enumerableのメソッドをeachで再実装してみる
理解を深めるために、mapをrubyで再実装してみます。
Enumerableのメソッドは全てeachを用いて定義されていますので、eachを使って作成できるはずです。
(実際のmapと同じものではありませんが、果たしている役割は同じメソッドを作れるはずです)

//emlist{
module MyEnumerable
  def my_map
    array = []
    each do |n|
      array << yield(n)
    end
    array
  end
end

class Array
  include MyEnumerable
end

list = (1..3).to_a

p(list.my_map { |item| item + 10 })
//}

「オブジェクト内の各要素に適用したい処理」と「処理の結果をどうまとめるか？」が、
どのように切り離されているかがよく分かると思います。

まずmodule MyEnumerableのdef my_mapに注目してください。
図XXXの構造とほぼ一緒です。異なるのはyield(n)を使っていることくらいでしょう。しかしこの点が重要です。

def my_mapからすると、yield(n)は何をやっているかは知りません。
とにかくyield(n)の戻り値(＝ブロックの戻り値)をarrayに入れる、オブジェクトの要素だけ繰り返す、戻り値としてarrayを返す、ということだけ行っています。
この処理は「処理の結果をどうまとめるか？」に該当します。

逆にmy_map呼び出し時のブロックの中身には、
item + 10 = 「オブジェクト内の各要素に適用したい処理」
しか記載されていません。処理結果(＝ブロックの戻り値)をどう扱うかは完全にmy_mapにお任せしています。

mapを使うことでこのように、
「オブジェクト内の各要素に適用したい処理」と「処理の結果をどうまとめるか？」を分離したコードが書けます。
さらに「処理の結果をどうまとめるか？」はmapの中に隠蔽されているので、見た目上かなり簡潔なコードが書けるようになります。

== 良く使う＆知っていると便利なEnumerableのメソッド
さて以上のように、Enumerableを使うと繰り返し処理を「Rubyっぽい」形で書けます。
ただEnumerableのメソッドは「処理の結果をどう扱うか」を含んでいるため、目的に応じて適切なメソッドを使い分ける必要もあります。

ここではEnumerableのメソッドを利用頻度が高そうな順にいくつか紹介します。
「利用頻度が高そう」は完全に私の個人的な経験に基づくものです。

簡単な説明と、利用サンプル、それから一部eachで再実装した際のコードを示します。
(なおeachでの実装は、利用サンプルのコードを置き換える事が可能という範囲で作成しています。
実際のEnumerableのメソッドとは異なる可能性がありますので、ご了承ください。)

=== mapメソッド
mapメソッドは、ブロックの戻り値を配列にして返します。

mapに関してはすでに説明した通りですので説明は割愛します。
mapはEnumerableのメソッドの中で一番よく使います。
eachを利用する際には、まずはmapで置き換えられないか？を考えてみると良いです。

=== select, find_allメソッド
find_allメソッドは、ブロック内に書かれた条件式の結果がtrueになった要素だけを配列にして返します。

selectはfind_allの別名です。
(実際にはselectの方が多く見るような？)

コード例:
//emlist{
list = (1..10).to_a

p list.select { |item| item.even? }

# 下のようにも書けます
p list.select(&:even?)
//}

実行結果:
//emlist{
[2, 4, 6, 8, 10]
//}

eachを用いたselectの再実装:
//emlist{
module MyEnumerable
  def my_select
    array = []
    each { |n| array << n if yield(n) }
    array
  end
end

# Arrayへのincludeは省略

list = (1..10).to_a
p list.my_select { |item| item.even? }
//}

=== find, detectメソッド
findメソッドは、ブロック内に書かれた条件式の結果がtrueになった要素を1つ返します。
detectはfindの別名です。

//emlist{
list = (1..10).to_a

p list.find { |item| item.even? }

# 下のようにも書けます
p list.find(&:even?)
//}

//emlist{
2
//}

=== rejectメソッド
rejectメソッドは、繰り返し処理(条件式)の結果に合う要素だけ除外した結果を配列にして返します。
find_all, selectの逆の動作です。

//emlist{
list = (1..10).to_a

p list.reject { |item| item % 3 == 0 }
//}

//emlist{
[1, 2, 4, 5, 7, 8, 10]
//}

=== max, min, minmax
max, minメソッドはそれぞれ最大値、最小値を返します。
minmaxメソッドは、最小値&最大値を配列の形で返します。

//emlist{
list = (1..10).to_a

p list.max
p list.min
p list.minmax
//}

//emlist{
10
1
[1, 10]
//}

=== max_by, min_by, minmax_by
max_by, min_byメソッドはブロックの戻り値が最大, 最小になる要素を返します。
minmax_byはブロックの戻り値が最大, 最小になる要素を配列の形で返します。

最大、最小の基準を自分で設定できるところが、max, min, minmaxとの違いです。

//emlist{
list = %w(one two three four five six seven eight nine ten)

p list.max_by(&:size)
p list.min_by(&:size)
p list.minmax_by(&:size)
//}

//emlist{
"three"
"one"
["one", "three"]
//}

=== include?
include?はオブジェクトの要素に引数と同じものが含まれていればtrueを、なければfalseを返します。

分かりやすい機能で利用頻度も結構高い印象です。

//emlist{
list = (1..10).to_a

list.include?(3)
list.include?(11)
//}

//emlist{
true
false
//}

=== all?, any?, none?メソッド
all?メソッドはブロックの戻り値が全て真だった場合にtrueを返します。それ以外はfalseを返します。
any?メソッドはブロックの戻り値が1つでも真だった場合にtrueを返します。それ以外はfalseを返します。
none?メソッドはブロックの戻り値が全て偽だった場合にtrueを返します。それ以外はfalseを返します。

特にany?あたりはたまに使う印象です。

//emlist{
list = (1..10)

p list.all? { |item| item.class == Integer }
p list.any? { |item| item.to_s.size == 2 }
p list.none? { |item| item < 1 }
//}

//emlist{
true
true
true
//}

=== reverse_each
名前の通り、逆から実施するeachです。繰り返し毎にブロック引数に要素が逆から入ります。

reverse.eachと書くとちょっとカッコ悪いので、こちらを使うといいです。

//emlist{
list = (1..5)

list.reverse_each { |item| p item }
//}

//emlist{
5
4
3
2
1
//}

=== each_with_indexメソッド
eachのブロック内でオブジェクトの各要素だけでなく、繰り返しの回数に対応したindexも利用できるようにしたメソッドです。

よく使いそうで意外と使わない、ようでやっぱり使う、そんな感じのメソッドです。

//emlist{
list = %w(water coffee tea milk)

list.each_with_index { |item, i| p "No.#{i} #{item}" }
//}

//emlist{
"No.0 water"
"No.1 coffee"
"No.2 tea"
"No.3 milk"
//}

=== group_by
group_byメソッドは要素をグループ分けします。具体的にはブロックの戻り値をキーとしたハッシュを作成します。
使わないように見えてたまに欲しくなります。覚えているととても便利です。

再実装してみると何をしているかよく分かります。

//emlist{
animals = ["cat", "bat", "bear", "camel", "alpaca"]

p animals.group_by { |item| item[0].chr }
//}

//emlist{
{"c"=>["cat", "camel"], "b"=>["bat", "bear"], "a"=>["alpaca"]}
//}

//emlist{
module MyEnumerable
  def my_group_by
    hash = {}
    each do |item|
      key = yield(item)
      hash[key] ||= []
      hash[key] << item
    end
    hash
  end
end

class Array
  include MyEnumerable
end

animals = ["cat", "bat", "bear", "camel", "alpaca"]
p animals.my_group_by { |item| item[0].chr }
//}

=== partion
partitionメソッドは、ブロックの戻り値が真の要素と偽の要素でグループ分けをします。
結果は[[真の要素...], [偽の要素...]]の形で返します。

//emlist{
list = (1..10).to_a

p list.partition { |item| item.odd? }
//}

//emlist{
[[1, 3, 5, 7, 9], [2, 4, 6, 8, 10]]
//}

=== inject/reduce
injectメソッドは、オブジェクトの要素を2つずつ使用して畳み込み計算を行うメソッドです。
結構使います。

言葉で説明するよりコードをみてもらった方が早いです。
こちらもeachでの再実装を用意しました。
yieldの結果を保持しておいて、次のループでyieldの引数の1つに使うだけです。

//emlist{
list = (1..10).to_a

p list.inject { |i, j| i + j}
p list.inject(30) { |i, j| i + j}

# 以下のようにも書けます
# p list.inject(:+)
# p list.inject(30, :+)
//}

//emlist{
55
85
//}

//emlist{
module MyEnumerable
  def my_inject(init=nil)
    prev = init
    each { |item|
      if prev.nil?
        prev = item
        next
      end
      prev = yield(prev, item)
    }
    prev
  end
end

class Array
  include MyEnumerable
end

list = (1..10).to_a
p list.my_inject(30) { |i, j| i + j}
//}
