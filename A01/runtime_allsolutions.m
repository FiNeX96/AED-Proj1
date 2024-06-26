dados = load ("AllSolutions.txt");
n = dados(1:end,1);
t_sol1 = dados(1:end,4);
t_sol2 = dados(1:end,7);
t_sol3 = dados(1:end,10);
t_sol4 = dados(1:end,13);
t_sol5 = dados(1:end,16);
plot(n,t_sol1,"b-")
hold on
plot(n,t_sol2,"r*")
hold on
plot(n,t_sol3,"b-.")
hold on
plot(n,t_sol4,"-go")
hold on
plot(n,t_sol5,"msquare")
grid on
legend('Solução 1 melhorada','Solução 2 melhorada','Solução 3 melhorada','Solução 4','Solução 5','FontSize',15)
title ('Runtime de todas as soluções','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário (s)','FontSize',20)