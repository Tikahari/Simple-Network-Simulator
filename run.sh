make clean
make
chmod +x sim
python ./src/data.py 1000
./sim ./data/nodes.txt ./data/obstacles.txt ./data/gridval.txt
