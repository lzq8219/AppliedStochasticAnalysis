global epsilon;
epsilon = 1e-6;
ratiob=[];
%% binomial±Æ½üpossion
for lambda=1:10
    t=possion(lambda);
    nmin=t(1,1);
    nmax=t(end,1);
    loss=1;
    N=lambda+1;

    while(loss > 0.01)
        N=N+1;
        p=lambda/N;
        b=binomial(N,p,[nmin,nmax]);
        while(b(end,1)<nmax)
            b(end+1,:)=[b(end,1)+1;0];
        end
        loss=sum(abs(t(:,2)-b(:,2)));
    end
    ratiob(end+1)=N/lambda;
end
ratiob


%% possion ±Æ½üGuassian
lambda = 10;
gaussianpdf=@(mu,sigma,x)1/sqrt(2*pi*sigma)*exp(-(x-mu).^2/2/sigma^2);

loss=1;
while(loss > 0.05)
    lambda=lambda+1;
    t=possion(lambda);
    s=sqrt(lambda);
    x=(t(:,1)-lambda)/s;
    probg=zeros(size(x));
    parfor i=1:numel(x)
        probg(i)=integral(@(xx)gaussianpdf(0,1,xx),x(i)-1/s/2,x(i)+1/s/2);
    end
    loss=sum(abs(t(:,2)-probg));
end

lambda


%% »­Í¼
figure(10);
x=-3:0.01:3;
y=gaussianpdf(0,1,x);
plot(x,y);
for lambda = 10:10:30
    t=possion(lambda);
    s=sqrt(lambda);
    x=(t(:,1)-lambda)/s;
    y=t(:,2)*s;
    hold on;
    plot(x,y);
end
legend('N(0,1)','possion(10)','possion(20)','possion(30)');



for lambda=1:3
    figure(lambda);
    t=possion(lambda);
    nmin=t(1,1);
    nmax=t(end,1);
    plot(t(:,1),t(:,2));
    for N= (30:10:50) * lambda
        hold on;
        b=binomial(N,lambda/N,[nmin,nmax]);
        plot(b(:,1),b(:,2));
    end
    legend(['possion(',num2str(lambda),')'],['N=',num2str(30*lambda)],...
        ['N=',num2str(40*lambda)],['N=',num2str(50*lambda)])
end



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


