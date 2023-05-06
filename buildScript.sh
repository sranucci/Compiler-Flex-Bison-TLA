rm -rf bin
rm ./src/frontend/lexical-analysis/flex-scanner.c
rm ./src/frontend/syntactic-analysis/bison-parser.c
rm ./src/frontend/syntactic-analysis/bison-parser.h

chmod u+x script --recursive
script/build.sh
script/test.sh
