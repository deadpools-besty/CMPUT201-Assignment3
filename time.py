from os import system


for i in range(0, 11):
    # test 50
    system("time -f 'Time: %E' -o 50t -a ./a3 -i 50 -c")
    system("time -f 'Time: %E' -o 50t -a ./a3 -i 50 -p")
    system("time -f 'Time: %E' -o 50t -a ./a3 -i 50 -t")
    system("time -f 'Time: %E' -o 50t -a ./a3 -i 50 -cp")
    #system("time -o 50t -a ./a3 -i 50 -ct")
    # test 100
    system("time -f 'Time: %E' -o 100t -a ./a3 -i 100 -c")
    system("time -f 'Time: %E' -o 100t -a ./a3 -i 100 -p")
    system("time -f 'Time: %E' -o 100t -a ./a3 -i 100 -t")
    system("time -f 'Time: %E' -o 100t -a ./a3 -i 100 -cp")
    #system("time -o 100t -a ./a3 -i 100 -ct")
    # test 200
    system("time -f 'Time: %E' -o 200t -a ./a3 -i 200 -c")
    system("time -f 'Time: %E' -o 200t -a ./a3 -i 200 -p")
    system("time -f 'Time: %E' -o 200t -a ./a3 -i 200 -t")
    system("time -f 'Time: %E' -o 200t -a ./a3 -i 200 -cp")
    #system("time -o 200t -a ./a3 -i 200 -ct")
    