# cpp_06
C++

# memo 
- 独習Ｃ++ Chap11.2 p,503-
- プログラミング言語C++ 11.5.3 p310-

### 思想としては。。
できるだけ安全な初期化{}構文による構築（モダンC++） ->
それでも変換が必要ならnamed cast ->
特に危険なcastをしなければならない ->
目立つようにしとく 

### キャスト演算子について
Ｃ言語ではキャスト演算子は１つのみ(T)e形式（式eからT型の値を作成するため）、それをＣ++ではＣ形式キャスト(C-style cast)と呼び、これをＣ++で使うことはめったにない。
その理由は、(T)eでは関連性をもつ型間の可搬性のある変換も、関連性がない型間の可搬性のない変換も、ポインタ型からconst修飾子を取り去る変換も何でもできてしまうため、大規模プログラムでは危険。

**明示的型変換**
- {}構文による構築
- 名前付き変換
- C言語形式キャスト
- 関数形式


C++では名前付き変換に4つのキャスト演算子が定義されている:
```
static_cast<target-type>(expr)

const_cast<target-type>(expr)

reinterpret_cast<target-type>(expr)

dynamic-cast<target-type>(expr)
```
dynamicキャストのみC++で追加されたのでこれはＣに対応する機能はない

### const_cast :
- constと宣言されたものにかきこめるようにする

### static_cast:
- 的確に定義された暗黙の変換の逆の変換を行う

### reinterpret_cast:
- ビットパターンの意味を変えてしまう

### dynamic_cast:
- 動的なクラス階層の移動をチェックする


castの練習

今持ってる値が何型か
別の型へ変換すると何が起こるか


## ex00

**処理の順序：**

1. argvから受け取る時点では全部文字列
2. 入力されたiteralの型を判定
3. 文字列を本来の型へ変換parseする
4. 残り３種類へ明示的に他のscalar型へexplicit castする


string -> float,

float -> int
これは別物



こんな感じにすればＯＫ？

例）
```
./convert 42.0f
```
```
"42.0f"
-> float literalだと判定をする

float 42.0f
->
char   -> '*'
int    -> 42
float  -> 42.0f
double -> 42.0 
```

```
ScalarConverter.cpp

型判定
├── isChar()
├── isInt()
├── isFloat()
├── isDouble()
└── detectType()

変換
├── fromChar()
├── fromInt()
├── fromFloat()
└── fromDouble()

出力
├── printChar()
├── printInt()
├── printFloat()
└── printDouble()

public interface
└── ScalarConverter::convert()
```

特殊値について：ex00/practice.cppで確認
```
man 3 isnan
man 3 isinf
```

##ex01
`reinterpret_cast<target-type>(expr)`の練習

### reinterpret_castとは？
- `static_cast`, `const_cast`で扱うことのできない型変換を行うキャスト演算子
- ポインタ型と整数型の直接変換等
- `std::intptr_t` -> ポインタ型の値を全て表現することができることが保証された、特別な符号付き整数型
符号あり：std::intptr_t
符号なし：std::uintptr_t
