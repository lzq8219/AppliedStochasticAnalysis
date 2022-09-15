

nn = 100000;
pp = 0.5;
lambda = 1;
N=100;
sigma=N*pp*(1-pp);
mu=N*pp;
A = binomial(N,pp,[nn,1]);
figure(1);
histogram(A,'Normalization','pdf');
hold on 
x=-2:0.01:2+mu;
y=1/sqrt(2*pi*sigma)*exp(-(x-mu).^2/2/sigma);
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