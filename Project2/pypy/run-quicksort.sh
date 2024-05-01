path="$1"
isBaseCase="$2"
cd "$(dirname "${BASH_SOURCE[0]}")"
cd ../cpython
pypy3.9 main.py quicksort $path $isBaseCase