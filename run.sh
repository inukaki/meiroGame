#!/bin/bash

# コンパイルオプション
CC=gcc
CFLAGS="-I./src/headers"
SRC=$(find ./src -name "*.c")
TARGET="meiro"

# プロジェクトのビルド
echo "Building the project..."
$CC $CFLAGS $SRC -o $TARGET

# ビルドが成功したかどうかを確認
if [ $? -eq 0 ]; then
    echo "Build successful. Running the program..."
    # プログラムを実行
    ./$TARGET
else
    echo "Build failed."
fi