function [phi, theta] = predict_roll_pitch(a_z, a_y, a_x)
theta = -180/pi*atan(a_x./sqrt(a_y.^2 + a_z.^2));
phi =180/pi*atan(a_y./sqrt(a_x.^2 + a_z.^2));

end