A = load("tempos_iniciais.txt")
n = A(:,1);
t = A(:,4);
figure
plot(n,t)
loglog(n,t)
semilogy(n,t)
figure
plot(n,log10(t))
t_log = log10(t);

N = [n(20:end) 1+0*n(20:end)]
Coefs = pinv(N)*t_log(20:end)
hold on 
Ntotal = [n n*0+1]
plot(n,Ntotal*Coefs,'r')
t800_log = [800 1]*Coefs
t800 = 10^t800_log / 3600 / 24 / 365
