name="Japan"
x=read.table("data.txt",header=T);
mi=1-min(x$N);
model_r2=0;
founders=0;
vr2=mi:1000;
for(i in mi:1000){
	vr2[i-mi+1]=cor(x$T,log10(x$N+i))^2;
	if(vr2[i-mi+1]>model_r2){	model_r2=vr2[i-mi+1];	founders=i;	}
}

png("FoundersEstimation.png",width=768,height=512);
plot(mi:1000,vr2,type='l',xlab="Number of Founders", ylab="R2",	main=paste(name," Founders Estimation"),lwd=2);
abline(v=founders,col=2,lwd=2);
legend("topright", paste("Founders=",founders));
dev.off();

png("Log10Trend.png",width=768,height=512);
plot(x$T,log10(x$N+founders),pch=20,xlab="Day",ylab=paste("log10( N+",founders," )"), main=paste(name," Log10 Scaled Trend"),lwd=2,cex=2);
abline(lm(log10(x$N+founders)~x$T),col=2,lwd=2);
legend("topleft", paste("R2=",sprintf("%.4f",model_r2)));
dev.off();

t=1:(length(x$T)+7);
n=1:(length(x$N)+7);
m=lm(log10(x$N+founders)~x$T);
a=m$coefficients[2];
b=m$coefficients[1];

for(i in 1:length(t)){
	if(i<=length(x$T)){ t[i]=x$T[i]; }
	else{ t[i]=t[i-1]+1; }
	n[i]=10^(a*t[i]+b)-founders;
}
png("InfectionPrediction.png",width=768,height=512);
plot(t,n,type='l',col=2,xlab="Day",ylab="Number of Diagnoses",main=paste(name," Infection Number Prediction"),lwd=2);
points(x$T,x$N,pch=20,lwd=2,cex=2);
legend("topleft", paste("tenfold every ",sprintf("%.1f",1/a), " days"));
dev.off();
