make all

if [ ! -e text8 ]; then
    wget http://mattmahoney.net/dc/text8.zip -O text8.gz
    tar xvzf text8.gz
fi

time ./w2c -train text8 -output vectors.bin -cbow 1 -size 200 -windows 8 -negative 25 -hs 0 -sample 1e-4 -threads 20 -binary 1 -iter 15
