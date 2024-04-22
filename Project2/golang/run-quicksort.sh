path="$1"
isBaseCase="$2"
cd "$(dirname "${BASH_SOURCE[0]}")"
cd ./goCSP
./goCSP quicksort $path $isBaseCase