# kvfs; key-value store based filesystem

A filesystem interface for KVS's. Currently supported only [LevelDB](https://github.com/google/leveldb).

## synopsis

```sh
# Mount at first
$ ./kvfs testdir --path=/tmp/kvfs/leveldb

# Read and write key-value pairs via filesystem interfaces:
$ echo "value1" > testdir/key1
$ cat testdir/key1
value1
$ gls testdir/
/key1  /key2
$ echo "value2" > testdir/key2
$ echo "value3" > testdir/key3
$ gls testdir/
/key1  /key2  /key3
```

## dependencies

- C++17
- [LevelDB](https://github.com/google/leveldb)
