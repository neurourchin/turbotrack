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
filename='nerveRing.yml';
gridHeight=100;
gridWidth=21; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('Illuminate AFD and ASE in the nerve ring.');





%Index notation
X=1; Y=2;

%Defualt Radii
dRad(X)=6;
dRad(Y)=3;

%We have to convert from the slider bar manual illumination coordinate convention
%To the protocol illumiantion convention.
annoyingXOffset=-10;
%Neuron centroid & radii
AFD(X)=10+annoyingXOffset;
AFD(Y)=11;

%predefine protocol
protocol=cell(0);

% Protocol = [x1, y1, x2,y2, etc..]

%AFD
protocol{end+1}=rect(AFD(X)-dRad(X), AFD(Y)-dRad(Y), AFD(X)+dRad(X), AFD(Y)+dRad(Y) );

    
writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


