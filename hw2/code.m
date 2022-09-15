

nn = 100000;
pp = 0.1;
lambda = 10;
N=100;
sigma=N*pp*(1-pp);
mu=N*pp;
A = binomial(N,pp,[nn,1]);
figure(1);
histogram(A,'Normalization','pdf');
hold on 
x=(-4:0.01:4)*sqrt(sigma)+mu;
y=1/sqrt(2*pi*sigma)*exp(-(x-mu).^2/2/sigma);
plot(x,y);



B=binomial(N,lambda/N,[nn,1]);
figure(2);
histogram(B,'Normalization','probability');
hold on
x=0:50;
y=exp(-lambda).*lambda.^x./factorial(x);
plot(x,y)







function A = ber(p,size)
    pr = rand(size);
    A = double(pr < p);
end

function A = binomial(n,p,size)
    A = 0;
    for i = 1:n
        A=A+ber(p,size);
    end
end