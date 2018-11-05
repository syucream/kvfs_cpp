targetdir=$1
path=/tmp/kvfs/leveldb
mkdir -p $targetdir
./kvfs $targetdir --path="$path"
