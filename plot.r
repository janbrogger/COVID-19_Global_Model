x=read.table("plot.txt",header=F);
png("plot.png",width=512,height=384);
plot(x$V1,x$V2,pch=20,xlab="Febrary 二月日期",ylab="log10( N(t) + 40 )",main="Exponential Growth Of COVID-19 Infection Outside China\n新冠病毒在国外呈现指数增长");
abline(lm(x$V2~x$V1),col=2);
dev.off();
