注意点：

1. 传有destructor的class进local函数，每次函数结束后都会删除这个class，递归使用必须使用deep copy， 不然会多次删除同一个class
2. 不能用一个是指向null的指针给另一个指针赋值，只能用null直接给一个指针赋值
3. 尽量传小class进函数

