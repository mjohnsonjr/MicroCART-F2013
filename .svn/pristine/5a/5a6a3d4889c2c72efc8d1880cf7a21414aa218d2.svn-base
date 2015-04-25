function TestKalman(imudata)
%This is a script that will run the Kalman filter on a given set of IMU
%data and plot the predited Euler angles along with raw gyro and accel
%angles

%to run:

%load 'mydataset.txt'
%TestKalman(mydataset);

%resets persistent variables
clear Kalman_2014;
clear EulerKalman_2014;
 
dt=imudata(:,1); %milliseconds in imu (converted to seconds in KalmanBill2.m)
p=imudata(:,2);  %degrees per second
q=imudata(:,3); %degrees per second
r=imudata(:,4); % degrees per second
ax=imudata(:,5); % gravitational units
ay=imudata(:,6); %gravitational units
az=imudata(:,7); %gravitational units
Nsamples=length(dt);

%run Kalman filter 
for i=1:Nsamples
    [phi, theta, psi, phi_a, theta_a, phi_g, theta_g]=Kalman_2014(dt(i),p(i),q(i),r(i),ax(i),ay(i),az(i)); %units in radians
    EulerSaved(i,:)=[phi, theta, psi, phi_a, theta_a, phi_g, theta_g];
end

%collection of Euler angles from Kalman filter
phisaved=EulerSaved(:,1)*180/pi; %final angle in degrees
thetasaved=EulerSaved(:,2)*180/pi; %final angle in degrees

%raw accel angles
phi_a_saved=EulerSaved(:,4)*180/pi; %final angle in degrees
theta_a_saved=EulerSaved(:,5)*180/pi; %final angle in degrees

%raw gyro angles
phi_g_saved=EulerSaved(:,6); %final angle in degrees
theta_g_saved=EulerSaved(:,7); %final angle in degrees

t=0:.001*dt:Nsamples*.001*dt-.001*dt; %units in seconds

figure;
subplot(2,1,1)
plot(t,phisaved,'b')
hold on
plot(t,phi_g_saved,'g')%
hold on
plot(t,phi_a_saved,'r')
grid on;
title('Kalman Filtered Roll','FontSize',16); 
xlabel('time (sec)','FontSize',14);
ylabel('roll (deg)','FontSize',14);
AX1 = legend('Kalman ','gyro roll','accelor roll','FontSize',14);
LEG1 = findobj(AX1,'type','text');
set(LEG1,'FontSize',14)


subplot(2,1,2)
plot(t,thetasaved,'b')
hold on
plot(t,theta_g_saved,'g')%
hold on
plot(t,theta_a_saved,'r')
grid on;
title('Kalman Filtered Pitch','FontSize',16); 
xlabel('time (sec)','FontSize',14);
ylabel('pitch (deg)','FontSize',14);
AX2 = legend('Kalman ','gyro pitch','accelor pitch','FontSize',14);
LEG2 = findobj(AX2,'type','text');
set(LEG2,'FontSize',14)


