clc; clear all

DATA = load("sol1_improved_107186.txt");
DATA2 = load ("sol1_improved_108969.txt");
n = DATA(1:end,1);
t = DATA(1:end,4);
t2 = DATA2(1:end,4);
%n = 0:8000;
%% 107186
plot(n,t)
hold on
N = [ n 0*n+1];
A = pinv(N)*t;
A_2 = pinv(N)*t2;
plot(n,A(1)*n+A(2))
ax = gca;
ax.FontSize = 16;
ay.FontSize = 16;
title('Runtime da Solução 1 melhorada - 107186','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário (s)','FontSize',20)
legend('Tempo de Execução','Ajuste Linear','FontSize',12)
%% 108969
figure(2)
plot(n,t2)
hold on
plot(n,A_2(1)*n+A_2(2))
ax = gca;
ax.FontSize = 16;
ay.FontSize = 16;
legend('Tempo de Execução','Ajuste Linear','FontSize',12)
title('Runtime da solução 1 melhorada - 108969','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário(s)','FontSize',20)
