#!/bin/bash



echo "[0%]: Copying files to dist..."

echo ">     Making distribution directory..."
mkdir "dist/YALTE"

echo ">     Copying dependency [1 of 3]..."
cp -R "dist/YALTE.out" "dist/YALTE"

echo ">     Copying dependency [2 of 3]..."
cp -R "docs" "dist/YALTE"

echo ">     Copying dependency [3 of 3]..."
cp -R "themes" "dist/YALTE"

echo

echo "[43%]: Zipping Files..."
cd dist
zip -r "YALTE.zip" "YALTE"

echo

echo "[76%]: Finished Zipping. Cleaning up..."

echo ">     Removing cloned dependency..."
rm -r "YALTE"

echo

echo "[100%]: Done. Check output."
