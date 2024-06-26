clc; clear all
%% para nº mecanográfico 108969 - 2a versão da solução 2
dadossol2_108969 = load("solucao2boa_108969.txt");
t = dadossol2_108969(1:end,4);
n = dadossol2_108969(1:end,1);
figure(1)
plot(n,t)
hold on
N =  [n 0*n+1];
A1 = pinv(N)*t;
A1_formated = A1(1)*n+A1(2);
plot(n,A1_formated) 
legend('Tempo de execução','Aproximação com polinómio de 1º grau','FontSize',12)
title('Runtime - Solução 2 v2 - Nmec 108969','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário (s)','FontSize',20)
ax = gca;
ax.FontSize = 16;
ay.FontSize = 16;
%% para nº mecanográfico 107186 - 2a versão da solução 2
dadossol2_107186 = load("solucao2boa_107186.txt");
t = dadossol2_107186(1:end,4);
n = dadossol2_107186(1:end,1);
figure(2)
plot(n,t)
hold on
N =  [ n 0*n+1];
A2 = pinv(N)*t;
A2_formated = A2(1)*n+A2(2);
plot(n,A2_formated) 
legend('Tempo de execução','Aproximação com polinómio de 1º grau','FontSize',12)
title('Runtime - Solução 2 v2 - Nmec 107186','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário (s)','FontSize',20)
ax = gca;
ax.FontSize = 16;
ay.FontSize = 16;
fprintf("Equação para nmec 108969 : %i*n + %i \n",A1(1),A1(2))
fprintf("Equação para nmec 107186 : %i*n + %i \n",A2(1),A2(2))