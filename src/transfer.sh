cd cat/compiled-code
scp s21_cat deploy@172.24.116.8:~
cd ../../grep/compiled-code
ls -la
scp s21_grep deploy@172.24.116.8:~
ssh deploy@172.24.116.8 mv /~ * /usr/local/bin 