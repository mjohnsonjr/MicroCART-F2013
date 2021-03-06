function [AdjustedCameraData]= Cameraplot(data)
%input file is .txt file received from base station
%output file is same file with initial time shifted to 0;
%to run:
%load 'cameradata.txt'
%Cameraplot(cameradata.txt);

Nsamples=length(data(:,1));
AdjustedCameraData=data;

for i=1:1:Nsamples
    AdjustedCameraData(i,1)=data(i,1)-data(1,1);    %shift initial time to 0;
    t(i)=AdjustedCameraData(i,1);
    
    roll(i)=AdjustedCameraData(i,7)*180/pi;
    pitch(i)=-AdjustedCameraData(i,6)*180/pi;
    yaw(i)=AdjustedCameraData(i,5)*180/pi;
end

%accounting for an accumulating delay with the camera system. origin unknown.
for j=1:1:Nsamples    
   t(j)=t(j)-.055*t(j);
end

subplot(2,1,1)
plot(t,pitch,'k-')
grid on;
hold on;
xlabel('time (sec)','FontSize',14);
ylabel('pitch (deg)','FontSize',14);

subplot(2,1,2)
plot(t,roll,'k-');
grid on;
hold on;
xlabel('time (sec)','FontSize',14);
ylabel('roll (deg)','FontSize',14);

