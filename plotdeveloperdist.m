
fileID = fopen('/Users/nurefsansertbas/Desktop/src/files/topdevelopers.txt');
%fileID = fopen('/Users/nurefsansertbas/Desktop/src/files/commitfrequencyofdevelopers.txt');
tmp = textscan(fileID,'%s',1);
x=cell2mat(tmp{1});
counter=str2num(x);

author=cell(counter,1);
commitcount=zeros(counter,1);


for i=1:counter
filedata = textscan(fileID,'%s',1);
data=cell2mat(filedata{1});
[d1,d2] = strsplit(data,':');
author{i}=d1{1,2};
commitcount(i,1)=str2num(d1{1,1});
end
fclose(fileID);

 data = transpose(commitcount(1:50,:)); %%INDEX should be changed at this line
%  barh(data,0.4,'m');
%  set(gca,'yticklabel',transpose(author(1:15,:)));

X = 1:50; 
bar(data,0.3);
set(gca,'XTick',1:50,'XTickLabel','') 
hx = get(gca,'XLabel');  % Handle to xlabel 
set(hx,'Units','data'); 
pos = get(hx,'Position'); 
y = pos(2); 
% Place the new labels 
for i = 1:50
    k=i;  %%INDEX should be changed at this line
  t(i) = text(X(i),y,author(k,:)); 
end 
set(t,'Rotation',90,'HorizontalAlignment','right') 
ylabel('Commit Frequency Rate (Num of commits per day)');
