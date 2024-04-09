# エレベータのシミュレーター
エレベータの昇降と乗員の乗降を模擬するシミュレータ

## How to setup
以下のレポジトリをクローン
```
https://github.com/toshihironakatani/cpp-02-project-ja
```

以下のコマンドによりビルド
```
g++ -std=c++17 ./src/*.cpp -o elevator
```

エレベータの諸元、乗員データが記載された入力ファイルを引数に指定して、以下のコマンドにより実行
```
./elevator <input file name>
```
example:
```
./elevator base_input.txt
```

## How to see results
### 状態
|文字|意味|
|----|----|
|t=|時刻|
|elevator|現在のエレベータの階|
|destination|エレベータの目的階のリスト。最も左が最優先|
|passenger|現在エレベータに乗っている乗員のID|
|weight|現在エレベータに乗っている乗員の総重量|

例えば以下は、時刻1のとき、エレベータは1階にいて、15階を目指しており、ID=0の乗員を載せていて、総重量は64であることを意味する。
```
<t=1> elevator: 1, destination: 15 , passenger: 0 , weight: 64
```
### 呼び出す
呼び出しボタンが押されたときに以下を表示（乗員ID1が0階で呼んでいる）
```
** Call - id: 1, floor: 0 **
```
### 乗せる
乗員を乗せるときに以下を表示（乗員ID1が乗り、行先階は5階）
```
** Pick up - id: 1, to: 5 **
```
### 降ろす
乗員を降ろすときに以下を表示（乗員ID1を降ろす）
```
** drop off - id: 1 **
```

## Input file list
以下の入力ファイルが利用可能
|ファイル名|シナリオ|
|----|----|
|base_input|乗員1人、エレベータ1台のシンプルなシナリオ|
|base_input2|乗員1人、エレベータ1台のシンプルなシナリオ2|
|overweight_input|二人目の乗員が乗ろうとすると最大積載荷重オーバーのために乗れないシナリオ|
|reach_input|乗員2人、エレベータ1台のやや複雑なシナリオ|
|reach_input2|乗員3人、エレベータ1台のやや複雑なシナリオ2|

## Key Design
`Simulator`に加えて、主に`Building`、`Elevator`、`Passenger`の3つのクラスによってプログラムが構成される。
基本的には`Building`が、`Elevator`と`Passenger`のメソッドを用いて全エレベータと乗員を管理と制御する。

## NOTE
エレベータが2台以上のシナリオには未対応
