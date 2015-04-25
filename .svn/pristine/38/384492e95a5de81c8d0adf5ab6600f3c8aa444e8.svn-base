function [phi, theta, psi, phi_a, theta_a, phi_g, theta_g] = Kalman_2014(dt,p,q,r,ax,ay,az)
    %Set up Kalman filter.  Takes in imu data and calculates A and z
    %matrices and sends them to EulerKalman_2014 which will return Euler
    %angles.  Kalman_2014 will return the Euler angles from
    %EulerKalman_2014 along with the Euler angles predicted by the gyro 
    %and accelerometer individually

    dt=dt*.001;  %convert from ms to seconds
    p = p*pi/180;   %units in radians per second
    q = q*pi/180;   %units in radians per second
    r = r*pi/180;   %units in radians per second
    %ax, ay, az are gravitational units
    
    A = eye(4) + dt*1/2*[0 -p -q -r; p 0 r -q; q -r 0 p; r q -p 0];
 
    %accelerometer Euler angles (used in calculation of z)
    theta_a = -atan(ax./sqrt(ay.^2 + az.^2)); %output in radians
    phi_a =atan(ay./sqrt(ax.^2 + az.^2));  %outputs in radians
    psi_a=0;
    
    %gyro Euler angles (not used in calculation of z)
    persistent initializeFlag
    persistent integration_of_gyrox
    persistent integration_of_gyroy
    if isempty(initializeFlag)
        integration_of_gyrox = 0;
        integration_of_gyroy = 0; 
        initializeFlag=1;
    end
    integration_of_gyrox = integration_of_gyrox + q*dt*180/pi;
    integration_of_gyroy = integration_of_gyroy + p*dt*180/pi;
    phi_g = integration_of_gyroy;
    theta_g= integration_of_gyrox;

    %begin calculation of z
    sinPhi   = sin(phi_a/2);    cosPhi   = cos(phi_a/2);
    sinTheta = sin(theta_a/2);  cosTheta = cos(theta_a/2);
    sinPsi   = sin(psi_a/2);    cosPsi   = cos(psi_a/2);

    z = [ cosPhi*cosTheta*cosPsi + sinPhi*sinTheta*sinPsi;
      sinPhi*cosTheta*cosPsi - cosPhi*sinTheta*sinPsi;
      cosPhi*sinTheta*cosPsi + sinPhi*cosTheta*sinPsi;
      cosPhi*cosTheta*sinPsi - sinPhi*sinTheta*cosPsi;
    ];

 
 [phi, theta, psi] = EulerKalman_2014(A, z); %outputs in radians
 

  
  
  