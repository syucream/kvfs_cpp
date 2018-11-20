targetdir=testdir

./scripts/mount.sh $targetdir;
echo "value1" > $targetdir/key1;
cat $targetdir/key1;
./scripts/umount.sh $targetdir;
