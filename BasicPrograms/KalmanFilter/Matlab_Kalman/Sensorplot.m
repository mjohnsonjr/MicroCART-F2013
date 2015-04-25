function Sensorplot(data) 

%plots raw IMU data
%input data format dt,p,q,r,ax,ay,az
%dt:s, p,q,r:deg/sec, ax,ay,az, fravitational units

%   load 'dataset.txt'
%   Sensorplot(dataset)

%initialize variables
Nsamples=length(data(:,1));
prevData=0;
adjustedData=data;
integration_of_gyrox=0;
integration_of_gyroy=0;
r_temp=zeros(1,Nsamples);
p_temp=zeros(1,Nsamples);
t=zeros(1,Nsamples);
raw_roll=zeros(1,Nsamples);
raw_pitch=zeros(1,Nsamples);

%convert column from dt to t
for k=1:1:Nsamples 
    adjustedData(k,1)=data(k,1)+ prevData;
    prevData=adjustedData(k,1);
end
adjustedData(:,1)=.001*adjustedData(:,1);

%calculate accel roll and pitch in degrees   
for i=1:1:Nsamples
   [r_temp(i), p_temp(i)] = predict_roll_pitch(adjustedData(i,7), adjustedData(i,6), adjustedData(i,5)); 
   t(i)=adjustedData(i,1);
end

%calculate gyro roll and pitch
for j=1:1:Nsamples
    dt=.001*data(j,1);
    integration_of_gyrox = integration_of_gyrox + adjustedData(j,2)*dt;
    integration_of_gyroy = integration_of_gyroy + adjustedData(j,3)*dt;
    raw_roll(j) = integration_of_gyroy;
    raw_pitch(j) = integration_of_gyrox;
end

figure
plot(t,raw_pitch,'g')
hold on
plot(t,p_temp,'r')
grid on;
xlabel('time (sec)','FontSize',14);
ylabel('pitch (deg)','FontSize',14);
AX1 = legend('gyro pitch','accelor pitch','FontSize',14);
LEG1 = findobj(AX1,'type','text');
set(LEG1,'FontSize',14)

figure
plot(t,raw_roll,'g')%
hold on
plot(t,r_temp,'r')
grid on;
xlabel('time (sec)','FontSize',14);
ylabel('roll (deg)','FontSize',14);
AX2 = legend('gyro roll','accelor roll','FontSize',14);
LEG2 = findobj(AX2,'type','text');
set(LEG2,'FontSize',14)



