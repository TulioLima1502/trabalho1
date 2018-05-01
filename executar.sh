## compilando e executando o trabalho de maneira automatizada
g++ -std=c++11 trabalho1.cpp -o trabalho1
echo 'compilando BIN.asm'
sleep 5
./trabalho1 -p bin.asm bin
echo 'compilando TRIANGULO.asm'
sleep 5
./trabalho1 -p triangulo.asm triangulo