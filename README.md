# 関数の戻り値について

再帰関数を内部で使うのでない限り、基本的にintを失敗か成功かの真偽値で返すことにした。

これは主に、ポインタの所有権の問題をややこしくしないために統一した方針である。

こうすることで構造体自身には外部から確保された領域を使わせ、構造体内部のメンバ変数には構造体を使用中に確保した領域を使わせることが明確にできるので、メモリリークなどのメモリの問題を防ぐことができる。