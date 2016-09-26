%% Notes
% Tip of HEAD is (0, 0). 
% Tail is (99,0)
%
% 
% Pictorially:
%      (-10,0)  (0,0)  (10,0)
%             Head
%                ^ 
%              /  \
%             /    \
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             \    /
%              \  /
%               \/
%             Tail  
%        (-10,99)  (0,99)  (10,99)
%
%
%    y
%    ^
%    |     (axis)
%    |
%    ------------> x
%
% Note also, you can walk off the worm in y (but not in x).


clear all; close all;


% Header informatoin
filename='simple3sector.yml';
gridHeight=100;
gridWidth=21; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('Simple illumination pattern for anterior, posterior, middle, left, right, middle, anterior left right');





%Index notation
X=1; Y=2;

%Defualt Radii
dRad(X)=6;
dRad(Y)=4;

%We have to convert from the slider bar manual illumination coordinate convention
%To the protocol illumiantion convention.
annoyingXOffset=-10;



%predefine protocol
protocol=cell(0);

% Protocol = [x1, y1, x2,y2, etc..]

%Anterior
protocol{end+1}=rect(-15, 0, 15,33);

%Posterior
protocol{end+1}=rect(-15, 66, 15,99);

%Middle
protocol{end+1}=rect(-15, 33, 15,66);

%Whole
protocol{end+1}=rect(-15, 0, 15,99);

%Left
protocol{end+1}=rect(-15, 0, 0,99);

%Right
protocol{end+1}=rect(0, 0, 15,99);

%Partial Left
protocol{end+1}=rect(-15, 0, -5,99);

%Partial Right
protocol{end+1}=rect(5, 0, 15,99);

%Partial LR center
protocol{end+1}=rect(-5, 0, 5,99);


% Anterior Left
protocol{end+1}=rect(-15, 0, 0,33);

%Anterior Right
protocol{end+1}=rect(0, 0, 15,33);

%Anterior Partial Left
protocol{end+1}=rect(-15, 0, -5,33);

%Anterior Partial Right
protocol{end+1}=rect(5, 0, 15,33);

%Anterior Partial Center
protocol{end+1}=rect(-5, 0, 5,33);




writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
    disp(n)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


