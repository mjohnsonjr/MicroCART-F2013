function [p,q,r,fx,fy,fz,dt,data,t]=genData2()

%The purpose of this function is to generate artificial gyroscope data
%(p,q,r) and accelerometer data (fx,fy,fz) from given Euler angles
%(phi,theta,psi).  The kinematic relationships were found in p. 126 and
%p.133 of "Kalman Filter for Beginners" by Phil Kim

%output data file is a text document named "imudata"
%imudata: [dt,p,q,r,fx,fy,fz,magx,magy,magz]
%dt:sec, p,q,r:deg/sec, ax,ay,az, gravitational units


dt=1/1300; %desired sampling time 
t=0:dt:1; %duration of sinusoid in seconds

%initialize variables
l=length(t); 
r=zeros(1,l);
q=zeros(1,l);
p=zeros(1,l);
fx=zeros(1,l);
fy=zeros(1,l);
fz=zeros(1,l);
data=zeros(10,l);
count=0;
theta_g_prev=0;
phi_g_prev=0;
psi_g_prev=0;

%accel noise variable
for i=0:dt:1 %should be same as t        
count=count+1;
ra=.8*randn; %accel noise

%accelerometer data
theta_a=ra+15*sin(5*2*pi*i);  
phi_a=ra+15*sin(5*2*pi*i);    

fx(count)=-sin(theta_a*pi/180);     
fy(count)=-(-cos(theta_a*pi/180).*sin(phi_a*pi/180));
fz(count)=-(-cos(theta_a*pi/180).*cos(phi_a*pi/180));

%begin gyro data
theta_g=15*sin(5*2*pi*i);  %can change euler angles for gyro here is desired
phi_g=15*sin(5*2*pi*i);
psi_g=15*sin(5*2*pi*i);

theta_dot=(theta_g-theta_g_prev)/dt; %rate of change is a simple derivitive
phi_dot=(phi_g-phi_g_prev)/dt;
psi_dot=(psi_g-psi_g_prev)/dt;

p(count)=(phi_dot-psi_dot*sin(theta_g*pi/180)); 
q(count)=(theta_dot*cos(phi_g*pi/180)+psi_dot*cos(theta_g*pi/180)*sin(phi_g*pi/180));
r(count)=(-theta_dot*sin(phi_g*pi/180)+psi_dot*cos(phi_g*pi/180)*cos(theta_g*pi/180));

theta_g_prev=theta_g;
phi_g_prev=phi_g;
psi_g_prev=psi_g;

end

%begin data compilation

%Create dt column in seconds
dt2=t;
dt2(:)=dt*1000;

magzeros=zeros(1,l); %add 0 column for magnetometer values
data=horzcat(dt2',p',q',r',fx',fy',fz',magzeros',magzeros',magzeros'); %matlab data file
fid=fopen('imudata.txt','wt'); %.txt data file is named "imudata"
fprintf(fid,'%3.6f %3.6f %3.6f %3.6f %3.6f %3.6f %3.6f %3.6f %3.6f %3.6f\n',data'); %prints as text file with 6 decimals of precision
fclose(fid);
load 'imudata.txt'
Sensorplot(imudata);

figure  %plot of gyroscore and accelerometer data
subplot(3,2,1)
plot(t,fx); title('accelerometer'); ylabel('fx');
set(get(gca,'YLabel'),'Rotation',0)
subplot(3,2,3)
plot(t,fy); ylabel('fy');
set(get(gca,'YLabel'),'Rotation',0)
subplot(3,2,5)
plot(t,fz); ylabel('fz');
set(get(gca,'YLabel'),'Rotation',0)
subplot(3,2,2)
plot(t,p); title('gyroscope'); ylabel('p');
set(get(gca,'YLabel'),'Rotation',0)
subplot(3,2,4)
plot(t,q); ylabel('q');
set(get(gca,'YLabel'),'Rotation',0)
subplot(3,2,6)
plot (t,r); ylabel('r');
set(get(gca,'YLabel'),'Rotation',0)

