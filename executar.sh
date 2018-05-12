## compilando e executando o trabalho de maneira automatizada
g++ -std=c++11 trabalho1.cpp -o trabalho1
echo '
*****
Compilando bin.asm'
sleep 5
./trabalho1 -p bin bin
echo '
*****
Compilando triangulo.asm'
sleep 5
./trabalho1 -p triangulo triangulo
