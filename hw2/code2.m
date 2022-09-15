global epsilon;
epsilon = 1e-6;
lambda=10;
t=possion(lambda);
nmin=t(1,1);
nmax=t(end,1);
loss=1;
N=lambda+1;


while(loss > 0.05)
    N=N+1;
    p=lambda/N;
    b=binomial(N,p,[nmin,nmax]);
    while(b(end,1)<nmax)
        b(end+1,:)=[b(end,1)+1;0];
    end
    loss=sum(abs(t(:,2)-b(:,2)));
end
N

lambda = 10;

loss=1;
while(loss > 0.05)
    lambda=lambda+1;
    t=possion(lambda);
    G=gussian(lambda,lambda,[t(1,1),t(end,1)]);
    loss=sum(abs(t(:,2)-G(:,2)));
end

lambda




function mf=possion(lambda)
    global epsilon
    i=0;
    mf=[];
    p=exp(-lambda);
    while(p<epsilon)
        i=i+1;
        p=p*lambda/i;
    end
    
    while(p>=epsilon)
        mf(end+1,:)=[i;p];
        i=i+1;
        p=p*lambda/i;
    end
end


function mf=binomial(n,p,range)
    q=1-p;
    nmin=max(0,range(1));
    nmax=min(n,range(2));
    mf=zeros(nmax-nmin+1,2);
    prob=nchoosek(n,nmin)*p^nmin*q^(n-nmin);
    for i = 1:nmax-nmin+1
        mf(i,:)=[i-1+nmin;prob];
        prob=prob*p/q/(i+nmin)*(n-i+1-nmin);
    end
end

function mf=gussian(mu,sigma,range)
    mf=zeros(range(2)-range(1)+1,2);
    i=1;
    fun=@(x)1/sqrt(2*pi*sigma)*exp(-(x-mu).^2/2/sigma);
    for x = range(1):range(2)
        mf(i,:)=[x,integral(fun,x-0.5,x+0.5)];
        i=i+1;
    end
end