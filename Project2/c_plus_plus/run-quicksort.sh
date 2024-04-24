path="$1"
isBaseCase="$2"
cd "$(dirname "${BASH_SOURCE[0]}")"
cd src
./main $path quicksort $isBaseCase