#!/bin/bash

cd cat/compiled-code
scp s21_cat deploy@172.24.116.8:~
cd ../../grep/compiled-code
scp s21_grep deploy@172.24.116.8:~
ssh deploy@172.24.116.8 sudo mv  s21_cat s21_grep  /usr/local/bin 