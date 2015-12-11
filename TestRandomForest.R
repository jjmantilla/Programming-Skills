
library(R.matlab)
data<-readMat('/home/mantilla/Documents/Courses/Rcourse/RF/PtX.mat')
data2<-readMat('/home/mantilla/Documents/Courses/Rcourse/RF/PtXt.mat')
data3<-readMat('/home/mantilla/Documents/Courses/Rcourse/RF/Pty.mat')
data4<-readMat('/home/mantilla/Documents/Courses/Rcourse/RF/Ptyt.mat')

train=data$PtX[,,2,2];
test=data2$PtXt[,,2,2];
classtrain=data3$Pty[,,2,2];

dataT=data.frame(train,factor(classtrain))
classtrain=data4$Ptyt[,,2,2];
dataT1=data.frame(test,factor(classtrain))
rm(classtrain)
dataT3=list(dataT,dataT1);
names(dataT3)=c("Ttrain","Ttest")

bestmtry <- tuneRF(dataT3$Ttrain[-25],dataT3$Ttrain$factor.classtrain, ntreeTry=2,improve=0.005, trace=TRUE, plot=TRUE, dobest=FALSE)
adult.rf <-randomForest(dataT3$Ttrain$factor.classtrain~.,data=dataT3$Ttrain, mtry=5, ntree=10, keep.forest=TRUE, importance=TRUE,test=dataT3$Ttest)
adult.rf.pr = predict(adult.rf,type="prob",newdata=dataT3$Ttest)[,2]
adult.rf.pred = prediction(adult.rf.pr,dataT3$Ttest$factor.classtrain)
adult.rf.perf = performance(adult.rf.pred,"tpr","fpr")
plot(adult.rf.perf,main="ROC Curve for Random Forest",col=2,lwd=2)
abline(a=0,b=1,lwd=2,lty=2,col="gray")
importance(adult.rf)
varImpPlot(adult.rf)
