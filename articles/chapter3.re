= Enumerableのメソッドで繰り返し処理をRubyっぽくする
本章で提案するのは、繰り返し処理におけるEnumerableモジュールのメソッドの利用です。
どんなプログラムでも繰り返し処理は頻繁に使います。
そのためEnumerableのメソッドは利用できる機会が多く、Rubyエンジニアも好んで用います。
使いこなせれば効率的に「Rubyっぽい」コードを書けるようになるはずです。

//blankline

本章は以下の流れでEnumerableのメソッドの利用について説明していきます。

 * Enumerableの前提知識となるeachメソッドについて説明
 * eachメソッド利用時の課題
 * Enumerableのメソッドによる課題の解決
 * よく使うEnumerableメソッドの解説

//embed[latex]{
\clearpage
//}

== eachメソッドについて
Rubyで用いられる繰り返し処理の制御構造・メソッドは数多くありますが、
その中で利用頻度が高く、まず押さえておくべきなのはeachメソッドです。
eachは配列やハッシュ等のオブジェクトの要素の数だけブロックの中身をします。
まず以下に簡単なサンプルコードを示します。

//list[each1][eachのサンプルコード1]{
list = (1..5).to_a
list.each { |item| p item + 10 }

#=> 11
#   12
#   13
#   14
#   15
//}

eachメソッドでは意識しておいてほしい事が2点あります。

==== ブロック引数とブロック内の処理
ブロック引数には繰り返しごとにオブジェクトの各要素が順に入ります。
ブロック内ではブロック引数に保持されたオブジェクトの各要素を用いて任意の処理を行います。
上のコードであればブロック引数は「|item|」です。ブロック内ではitemに10を加えたものをpメソッドで出力しています。

Rubyにおける反復処理はこのように、「オブジェクトの各要素に適用したい処理」を用意しておいて、
各要素に対して1つずつ適用する形が好まれます@<fn>{iterator}。eachはその考えを実現できる最も基本的なメソッドです。
//footnote[iterator][この考え方は一般的にはイテレータと呼ばれており他の言語にも存在しますが、Rubyでは特に好まれている印象です]

==== 戻り値
eachメソッドの戻り値はレシーバであり、ブロック内でどんな処理をしても戻り値は影響を受けません。
上のコードであればeachメソッドの戻り値は「list」です。「p item + 10」の結果はeachメソッドの戻り値には何も影響を与えません。

言い換えれば、eachメソッドのブロック内の処理結果は、そのままだとeachメソッドの外で用いることは出来ません。
処理結果を外で使いたい場合は、以下のようにブロック外で定義したオブジェクトに値を保存する必要があります。

//embed[latex]{
\clearpage
//}

//list[each2][eachのサンプルコード2]{
list = (1..3).to_a

result = []
list.each { |item| result << item + 10 }
p result

#=> [11, 12, 13]
//}

=== eachメソッド利用時の課題
eachメソッドはRubyの反復処理には欠かせないとても重要なメソッドですが、利用シーンによっては課題もあります。
eachメソッドでは「オブジェクトの各要素に適用したい処理」と、
「処理の結果をどう扱うか？」をブロック内に一緒に記載する必要があります。

例として @<list>{each2} のコードを用いて説明します。
「オブジェクトの各要素に適用したい処理」に該当するコードは@<code>{item + 10}で、
「結果をどうまとめるかの処理」に該当するコードは@<code>{result <<}です。
実際の処理は@<code>{result << item + 10}であり、ブロック内で一緒に記載されています。

前述の通りRubyにおける反復処理は、オブジェクトの各要素に対して任意の処理を適用する形が好まれます。
繰り返し処理の中で「結果をどうまとめるかの処理」も同時に書かれているのはあまり好ましくありません。
加えてこの処理の実現のために、eachの外でわざわざ空のresultを用意していますが、これも冗長です。
このような書き方はRuby的には少しカッコわるく、多くのRubyエンジニアは避けます。
つまり「Rubyっぽい」と言えません。

== Enumerableのメソッド
そこで登場するのがmapやselectに代表されるEnumerableのメソッドです。
EnumerableはRubyの組込ライブラリの1つで、繰り返し処理に関連する便利なメソッドを提供してくれる Mix-in(モジュール) です。
主に配列やハッシュなど集合を表すクラスに標準で組み込まれており、数え上げや検索などのメソッドを提供します。

Enumerableのメソッドを用いると、
「オブジェクト内の各要素に適用したい処理」と「処理の結果をどうまとめるか？」の切り離しが、
簡潔なコードで実現できます。
「処理の結果をどうまとめるか？」をEnumerableのメソッドに任せて、
自分は「オブジェクトの各要素に適用したい処理」だけをブロックとしてメソッドに渡します(@<img>{Enumerable_Image})。

//image[Enumerable_Image][Enumerableのメソッドの利用イメージ]{

//}


=== eachをEnumerableのメソッドに置き換える
実際に @<list>{each2} のコードをEnumerableのメソッドを使って書き直してみます。
ここではmapメソッドを使います。
mapは「オブジェクトの各要素に適用した処理」の結果を配列にして返します。

//list[map][mapのサンプルコード]{
list = (1..3).to_a

p list.map { |item| item + 10 }
# => [11, 12, 13]
//}

まずブロック内には@<code>{item + 10} ＝「オブジェクトの各要素に適用したい処理」しか記載されていません。
処理結果はブロックの戻り値としてmapに渡され、結果をどう扱うか？はmapの中に隠蔽されています。
またresultも無くなりました。これはmap自体が戻り値として配列を返すことから、処理の結果を格納する変数が必要なくなったためです。
each/mapのそれぞれのコードを並べて比較してみます。

//list[eachmap][eachとmapの比較]{
list = (1..3).to_a

# eachを使った場合
result = []
list.each { |item| result << item + 10 }
p result

# mapを使った場合
p list.map { |item| item + 10 }
//}

3行だったコードが1行で表現でき、非常にスッキリしたコードになりました。
加えてmapを使った処理は、「オブジェクトの各要素に適用したい処理」をmapに渡しているだけ、という構造になっていることが分かります。

=== Enumerableのメソッドをeachで再実装してみる
理解を深めるために、mapをrubyで再実装してみます。
Enumerableのメソッドは全てeachを用いて定義されていますので、eachを使って作成できます@<fn>{ruby_map}。

//footnote[ruby_map][実際のmapとは同じものではありませんが、最低限同じ役割を果たすメソッドとして作成します]


//listnum[map_by_each][eachによるmapメソッドの再実装]{
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

再実装することで「オブジェクト内の各要素に適用したい処理」と「処理の結果をどうまとめるか？」が、
どのように切り離されているかが分かると思います。

==== 「処理の結果をどうまとめるか?」
@<list>{map_by_each}の1行目、@<code>{MyEnumerable}の@<code>{def my_map}に注目してください。
@<list>{each2}の構造とほぼ一緒です。
異なるのは@<code>{def my_map}が受け取ったブロック内の処理を、@<code>{yield(n)}を使って展開していることですが、この点が重要になります。
@<code>{def my_map}から見ると、@<code>{yield(n)}が何をしているかは分かりません。
@<code>{yield(n)}の戻り値を利用しているだけです。
行なっているのは

 1. @<code>{yield(n)}の戻り値(＝ブロックの戻り値)をarrayに入れる
 2. '1.'をオブジェクトの要素だけ繰り返す
 3. 戻り値としてarrayを返す

ですが、この処理は「処理の結果をどうまとめるか？」を実現しています。

==== 「オブジェクト内の各要素に適用したい処理」 
@<list>{map_by_each}の17行目に注目してください。
ここではmy_mapを呼び出していますが、ブロックの中身には、@<code>{item + 10} ＝ 「オブジェクト内の各要素に適用したい処理」
しか記載されていません。処理結果(＝ブロックの戻り値)をどう扱うかは完全に@<code>{my_map}にお任せしています。

//blankline

mapを使うことでこのように、
「オブジェクト内の各要素に適用したい処理」と「処理の結果をどうまとめるか？」を分離したコードが書けます。
また「処理の結果をどうまとめるか？」がmapの中に隠蔽され、簡潔なコードが書けるようになります。

== 良く使う便利なEnumerableのメソッド
これまでの説明の通り、Enumerableを利用することで繰り返し処理を「Rubyっぽい」コードで書けます。
ただEnumerableのメソッドは「処理の結果をどう扱うか?」を含んでいるため、目的に応じて適切なメソッドを使い分ける必要もあります。

そこでEnumerableのメソッドを、個人的に利用頻度が高そうと思った順にいくつか紹介します。

簡単な説明と、利用サンプル、それから一部eachで再実装した際のコードを示します。
(eachでの再実装は、サンプルコード上でEnumerableのメソッドを置き換える事が可能という範囲で作成しています。
実際のメソッドとは異なりますのでご注意ください。気になる人は実際のRubyのソースコードを確認してみてください。)

=== map, collectメソッド
mapメソッドはブロックの戻り値を配列にして返します。
collectメソッドはmapメソッドの別名です。別名と言いつつcollect派の人もたくさんいらっしゃいます。
どちらが多数派なのかは不明ですが、私はmap派ですので本書ではmapで説明をしています。

mapはEnumerableのメソッドの中で最もよく使われています。だいたいこれで何とかなります。
eachを利用する際には、まずはmapで置き換えられないか？を考えてみると良いです。

以下のコードは@<list>{map}と@<list>{map_by_each_again}の再掲となります。

//list[map_again][mapのサンプルコード(再掲)]{
list = (1..3).to_a

p list.map { |item| item + 10 }
# => [11, 12, 13]
//}

//listnum[map_by_each_again][eachによるmapメソッドの再実装(再掲)]{
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

=== select, find_all, filterメソッド
find_allメソッドは、ブロック内に書かれた条件式の結果がtrueになった要素だけを配列にして返します。
select, filterはfind_allの別名です。私はselect派なので以降の説明はselectで行います。

このメソッドもよく使う印象です。配列やハッシュから条件に合う要素だけ取り出したい時などに利用できます。

//list[select_find_all][select, find_allメソッドのサンプルコード]{
list = (1..10).to_a

p list.select { |item| item.even? }

#=> [2, 4, 6, 8, 10]
//}

//list[select_by_each][eachによるselectメソッドの再実装]{
module MyEnumerable
  def my_select
    array = []
    each { |n| array << n if yield(n) }
    array
  end
end

class Array
  include MyEnumerable
end

list = (1..10).to_a
p list.my_select { |item| item.even? }
//}

=== rejectメソッド
rejectメソッドは、繰り返し処理(条件式)の結果に合う要素だけ除外した結果を配列にして返します。

select, find_allの逆の動作です。
ifに対するunlessと同じような位置付けです。
適切に使えるとちょっとだけカッコいい気がします。

//list[reject][rejectメソッドのサンプルコード]{
list = (1..10).to_a

p list.reject { |item| item % 3 == 0 }

#=> [1, 2, 4, 5, 7, 8, 10]
//}

=== find, detectメソッド
findメソッドは、ブロック内に書かれた条件式の結果がtrueになった要素を1つ返します。
detectはfindの別名です。

Ruby on Railsの環境では、Railsのfindメソッドと被るのでdetectを利用した方が良いかもしれません。

//list[find_detect][find, detectメソッドのサンプルコード]{
list = (1..10).to_a

p list.find { |item| item.even? }

# 下のようにも書けます
# p list.find(&:even?)

#=> 2
//}

=== include?メソッド
include?メソッドはオブジェクトの要素に引数と同じものが含まれていればtrueを、なければfalseを返します。

分かりやすい機能で利用頻度も結構高い印象です。

//list[include][include?メソッドのサンプルコード]{
list = (1..10).to_a

list.include?(3)
list.include?(11)

#=> true
#   false
//}

=== inject/reduceメソッド
injectメソッドは、オブジェクトの要素を2つずつ使用して畳み込み計算を行うメソッドです。
reduceメソッはinjectメソッドの別名です。
injectはパッと見何をしているか分かりにくい面がありますが、使ってみると便利で好きな人は好き！という感じのメソッドです。

可読性を気にする方もいらっしゃいますので、チーム開発の際には利用していいか確認したほうが良いかもしれません。

動作はコードをみてもらった方が早いです。
こちらはeachでの再実装も記載しましたので、併せて確認して見てください。
やっていることは案外単純です。yieldの結果を保持しておいて、次のループでyieldの引数の1つに使うだけです。

//list[inject_reduce][inject, reduceメソッドのサンプルコード]{
list = (1..10).to_a

p list.inject { |i, j| i + j}
p list.inject(30) { |i, j| i + j}

# 以下のようにも書けます
# p list.inject(:+)
# p list.inject(30, :+)

#=> 55
#   85
//}

//list[inject_by_each][eachによるinjectメソッドの再実装]{
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

=== partitionメソッド
partitionメソッドは、ブロックの戻り値が真の要素と偽の要素でグループ分けをします。
結果は[[真の要素...], [偽の要素...]]の形で返します。

たまに使うので覚えておくと便利な印象です。

//list[partion][partionメソッドのサンプルコード]{
list = (1..10).to_a

p list.partition { |item| item.odd? }

#=> [[1, 3, 5, 7, 9], [2, 4, 6, 8, 10]]
//}

=== group_byメソッド
group_byメソッドは要素をグループ分けします。具体的にはブロックの戻り値をキーとしたハッシュを作成します。
eachでの再実装も記載しました。確認してもらうと何をしているかよく分かると思います。

使わないように見えてたまに欲しくなります。これも覚えているととても便利です。


//list[group_by][group_byのサンプルコード]{
animals = ["cat", "bat", "bear", "camel", "alpaca"]

p animals.group_by { |item| item[0].chr }

#=> {"c"=>["cat", "camel"], "b"=>["bat", "bear"], "a"=>["alpaca"]}
//}

//list[group_by_by_each][eachによるgroup_byメソッドの再実装]{
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


=== max, min, minmaxメソッド
max, minメソッドはそれぞれ最大値、最小値を返します。
minmaxメソッドは、最小値&最大値を配列の形で返します。

使いそうで案外使わない気がします。

//list[max_min_minmax][max, min, minmaxメソッドのサンプルコード]{
list = (1..10).to_a

p list.max
p list.min
p list.minmax

#=> 10
#   1
#   [1, 10]
//}

=== max_by, min_by, minmax_byメソッド
max_by, min_byメソッドはブロックの戻り値が最大, 最小になる要素を返します。
minmax_byメソッドはブロックの戻り値が最大, 最小になる要素を配列の形で返します。

最大、最小の基準を自分で設定できるところが、max, min, minmaxメソッドとの違いです。

//list[max_by_min_by_minmax_by][max_by, min_by, minmax_byメソッドのサンプルコード]{
list = %w(one two three four five six seven eight nine ten)

p list.max_by { |item| item.size }
p list.min_by { |item| item.size }
p list.minmax_by { |item| item.size }

#=> "three"
#   "one"
#   ["one", "three"]
//}

=== all?, any?, none?メソッド
all?メソッドはブロックの戻り値が全て真だった場合にtrueを返します。それ以外はfalseを返します。
any?メソッドはブロックの戻り値が1つでも真だった場合にtrueを返します。それ以外はfalseを返します。
none?メソッドはブロックの戻り値が全て偽だった場合にtrueを返します。それ以外はfalseを返します。

これも使いそうで案外使わない印象です。ただany?は割と使います。

//list[all_any_none][all?, any?, none?メソッドのサンプルコード]{
list = (1..10)

p list.all? { |item| item.class == Integer }
p list.any? { |item| item.to_s.size == 2 }
p list.none? { |item| item < 1 }

#=> true
#   true
#   true
//}

=== reverse_eachメソッド
名前の通り、逆から実施するeachです。繰り返し毎にブロック引数に要素が逆から入ります。

reverse.eachと書くとちょっとカッコ悪いので、こちらを使うと「Rubyっぽい」です。

//list[reverse_each][reverse_eachメソッドのサンプルコード]{
list = (1..5)

list.reverse_each { |item| p item }

#=> 5
#   4
#   3
#   2
#   1
//}

=== each_with_indexメソッド
eachのブロック内でオブジェクトの各要素だけでなく、繰り返しの回数に対応したindexも利用できるようにしたメソッドです。

よく使いそうで意外と使わない、ようでやっぱり使う、そんな感じのメソッドです。

//list[each_with_index][each_with_indexのサンプルコード]{
list = %w(water coffee tea milk)

list.each_with_index { |item, i| p "No.#{i} #{item}" }

#=> "No.0 water"
#   "No.1 coffee"
#   "No.2 tea"
#   "No.3 milk"
//}

=== sort_byメソッド
sort_byメソッドは、ブロックを使ってオブジェクトの要素をソートした配列を返します。
オブジェクトの要素にブロック内の処理を適用し、
ブロックの戻り値を<=>演算子で比較して、小さい順に要素を並べます。

ソートの基準をこちらで指定できるので、必要な時はすごく便利です。
こういったメソッドが標準で組み込まれているあたりにRubyの特色が表れています。

//list[sort_by][sort_byのサンプルコード]{
list = %w(one two three four five six seven eight nine ten)

list.sort_by { |item| item.size }

# => ["ten", "two", "six", "one", "five", "nine", "four", "seven", "eight", "three"]
//}

=== cycleメソッド
cycleメソッドはオブジェクトの要素の分だけブロックの中身を実施し、それをcycleメソッドに渡した引数の分繰り返します。
簡単に言うと、eachを複数回繰り返すような感じです。なお引数を省略すると無限回繰り返します。

面白いメソッドなので紹介しましたが、なかなか使いどころが難しいかもしれません。

//list[cycle][cycleのサンプルコード1]{
list = (1..3).to_a
list.cycle(3) { |item| p item + 10 }

#=> 11
#   12
#   13
#   11
#   12
#   13
#   11
#   12
#   13
//}




