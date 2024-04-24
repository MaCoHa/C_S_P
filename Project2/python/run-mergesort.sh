path="$1"
isBaseCase="$2"
cd "$(dirname "${BASH_SOURCE[0]}")"
python3 main.py mergesort $path $isBaseCase