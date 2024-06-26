clc; clear all
DATA = load("teste1hvitor2.txt");
DATA2 = load ("teste1hrodrigo2.txt");
n = DATA(1:end,1);
t = DATA(1:end,4);
plot(n,t,'r*')
legend('Tempo de Execução','FontSize',20)
title('Runtime com escala normal - nmec 108969','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário (s)','FontSize',20)
figure(2)

% extrapolação 
n2 = DATA2(1:end,1);
t2 = DATA2(1:end,4);
T = log(t);
T2 = log(t2);
N =  [n 0*n+1];
A = pinv(N)*T;
A2 = pinv(N)*T2;
y = exp(A(1).*n).*exp(A(2)); % extrapolação pra nmec 108969
y2 = exp(A2(1).*n).*exp(A2(2)); % extrapolação para nmec 107186
semilogy(n,y,"-b.")
hold on
semilogy(n,t)
legend('Ajuste Linear','Tempo de execução','FontSize',15)
title('Runtime da solução 1','FontSize',20)
xlabel('Posição final','FontSize',20)
ylabel('Tempo necessário(s)','FontSize',20)
n = 0:800;
y = exp(A(1).*n)*exp(A(2)); % extrapolação pra nmec 108969
y2 = exp(A2(1).*n)*exp(A2(2)); % extrapolação para nmec 107186
fprintf("Tempo necessário para n = 800, nmec 108969 - %i anos \n", y(801)/3600/24/365)
fprintf("Tempo necessário para n = 800, nmec 107186 - %i anos \n", y2(801)/3600/24/365)
fprintf("Formula para cálculo de tempo aproximada  = %i * %i^n \n",exp(A(2)),exp(A(1)))
figure(3)
plot(n(1:40),y(1:40),"r*")
hold on
n = DATA(1:40,1);
t = DATA(1:40,4);
plot(n,t,"bsquare") % confirmação da formula obtida







