function [] = SCDQAM()
    textfile='teste.txt';
    imgfile='teste,jpg';
    
    b = file2bit( textfile);
    result=mainQAM(b);
    x = bit2file( result, textfile+'.new' );
    
    b = image2bit( imgfile);
    result=mainQAM(b);
    x = bit2image( result, imgfile+'.new' );

end