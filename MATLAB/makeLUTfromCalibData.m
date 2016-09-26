function makeLUTfromCalibData(input_yaml_filename)
%
%
%
disp(['Reading in YAML file: ' input_yaml_filename]);
assert(exist('YAML.m','file')==2,'Error! Missing dependency YAML.m. Add to Path or download from http://www.cs.sunysb.edu/~kyamagu/software/yaml/')

%Read in the yaml textfile
yamltext = fileread(input_yaml_filename);

%Find all carriage returns
cr=find(yamltext==13);

%Delete the first line of the yaml (otherwise it seems to cause snakeyaml
%to crash)
yamltext(1:cr)=[];

%Decode the yaml
D=YAML.load(yamltext);

assert(isfield(D,'PairOfPoints')==1,['Error: missing a data object PairOfPoints in yaml file ' input_yaml_filename]);

NUM_PARIED_PTS=length(D.PairOfPoints);

assert(NUM_PARIED_PTS>1,'Error: there should be many calibrated points from which to generate the look up table.');

for k=1:NUM_PARIED_PTS

    assert(isfield(D.PairOfPoints(k),'DLP')==1,['Error: missing a DLP  point in ' num2str(k) 'th pair of points']);
    assert(isfield(D.PairOfPoints(k),'CCD')==1,['Error: missing a CCD  point in ' num2str(k) 'th pair of points']);

    DLPPoints(k,1)= D.PairOfPoints(k).DLP.x;
    DLPPoints(k,2)= D.PairOfPoints(k).DLP.y;
    CCDPoints(k,1)= D.PairOfPoints(k).CCD.x;
    CCDPoints(k,2)= D.PairOfPoints(k).CCD.y;
    
end


%Do the transform
t = cp2tform(DLPPoints,CCDPoints,'lwm',NUM_PARIED_PTS);



%Generate a mesh with one element for each pixel on the CCD
[xCCD,yCCD]=meshgrid(1:D.DLPwidth,1:D.DLPheight);



%For each element on the CCD, find the corresponding element on the DLP
% NOte that this assigns DLP elements that don't actually exist (e.g.
% negative lemetns, or elements that go beyond where the current mirrors
% are)
disp('Generated lookup table');
[xDLP,yDLP]=tforminv(t,xCCD,yCCD);

%identiy the position of the DLP 
pDLP=ones(size(xDLP));
pDLP(xDLP>D.DLPwidth)=0;
pDLP(xDLP<0)=0;
pDLP(yDLP>D.DLPheight)=0;
pDLP(yDLP<0)=0;

hFig = figure(1);
set(hFig, 'Position', [200 200 1000 600])

subplot(2,2,1);
imagesc(pDLP);
title('Position of DLP as seen from camera');



LookUp(:,:,1)=xDLP;
LookUp(:,:,2)=yDLP;
LookUp(:,:,3)=zeros(size(yDLP));



LookUp=ceil(LookUp); %Round it because we are doing integers

%Display destination and results
subplot(2,2,2);
imshow(LookUp./max(max(max(LookUp))));
title('Destination of x&y coordinates. X is red. Y is grene')

subplot(2,2,3);
imagesc(LookUp(:,:,1)); 
colorbar
title('Dimension 1');

subplot(2,2,4);
imagesc(LookUp(:,:,2));
colorbar
title('Dimension 2'); 

%Cut out the extra third channel matrix that we've been carrying around
%just for convenience
LookUp(:,:,3)=[];

size(LookUp);


% Write out the LookUp Vector as a binary file in the appropriate format

if (isfield(D,'SizeOfInt'))
    SizeOfInt=D.SizeOfInt;
else
    SizeOfInt=4; %Default int size is 4 bits
end

LookUp_Array=reshape(LookUp,1,[]);  %Make the LookUp table a long linear array
disp('Writing lookup table');
fid = fopen('calib.dat', 'w');
assert(fid~=0,'Error opening calib.dat for writing');
fwrite(fid, LookUp_Array, ['integer*' num2str(SizeOfInt)]); %Write the disk
fclose(fid);

disp('Hit enter to finsih');
pause;


end